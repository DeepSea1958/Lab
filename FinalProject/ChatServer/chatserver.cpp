// chatserver.cpp
#include "chatserver.h"
#include "serverworker.h"
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDateTime>
#include <QRandomGenerator>
#include <QPointer>

ChatServer::ChatServer(QObject *parent)
    : QTcpServer(parent)
{

    m_threadPool = new QThreadPool(this);
    m_threadPool->setMaxThreadCount(50);

    QString logFileName = QString("chat_log_%1.txt")
                              .arg(QDate::currentDate().toString("yyyyMMdd"));
    m_logFile.setFileName(logFileName);
    if (m_logFile.open(QIODevice::Append | QIODevice::Text)) {
        m_logStream.setDevice(&m_logFile);
        m_logStream << "\n========== 服务器启动于 "
                    << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
                    << " ==========\n";
        m_logStream.flush();
    }
}

ChatServer::~ChatServer()
{
    if (m_logFile.isOpen()) {
        m_logStream << "========== 服务器关闭于 "
                    << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
                    << " ==========\n";
        m_logFile.close();
    }
}

/* -------------------- 新连接 -------------------- */
void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    ServerWorker *worker = new ServerWorker;
    worker->setAutoDelete(false);               // 关键①：自己管理生命周期

    if (!worker->setSocketDescriptor(socketDescriptor)) {
        worker->deleteLater();
        return;
    }

    worker->setProperty("_seq", ++m_connSeq);   // 调试用序号

    // 关键②：用 QPointer 防止野指针
    connect(worker, &ServerWorker::disconnectedFromClient,
            this, [this, wp = QPointer<ServerWorker>(worker)]() {
                if (wp) userDisconnected(wp.data());
            }, Qt::QueuedConnection);

    connect(worker, &ServerWorker::jsonReceived,
            this, &ChatServer::jsonReceived, Qt::QueuedConnection);

    connect(worker, &ServerWorker::logMessage,
            this, &ChatServer::logMessage, Qt::QueuedConnection);

    connect(worker, &ServerWorker::errorOccurred,
            this, [this, wp = QPointer<ServerWorker>(worker)]() {
                if (wp) handleClientError(wp.data());
            }, Qt::QueuedConnection);

    {
        QMutexLocker locker(&m_clientsMutex);
        m_clients.append(worker);
    }

    m_threadPool->start(worker);
    emit logMessage(QString("新连接 %1，当前在线 %2")
                        .arg(worker->property("_seq").toInt())
                        .arg(m_clients.size()));
}

/* -------------------- 广播 -------------------- */
void ChatServer::broadcast(const QJsonObject &message, ServerWorker *exclude)
{
    const QByteArray jsonData =
        QJsonDocument(message).toJson(QJsonDocument::Compact);

    QMutexLocker locker(&m_clientsMutex);
    for (ServerWorker *w : m_clients) {
        if (w == exclude) continue;
        w->sendJsonData(jsonData);
    }
}

/* -------------------- 私聊 -------------------- */
void ChatServer::sendPrivateMessage(const QJsonObject &message,
                                    const QString &receiver)
{
    const QByteArray jsonData =
        QJsonDocument(message).toJson(QJsonDocument::Compact);

    QMutexLocker locker(&m_clientsMutex);
    for (ServerWorker *w : m_clients) {
        if (w->userName() == receiver) {
            w->sendJsonData(jsonData);
            break;
        }
    }
}

/* -------------------- 日志 -------------------- */
void ChatServer::saveMessageToLog(const QString &message)
{
    if (m_logFile.isOpen()) {
        m_logStream << QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss] ")
        << message << '\n';
        m_logStream.flush();
    }
}

/* -------------------- 停服 -------------------- */
void ChatServer::stopServer()
{
    close();
    QMutexLocker locker(&m_clientsMutex);
    for (ServerWorker *w : m_clients) {
        w->stopWorker();
        w->deleteLater();
    }
    m_clients.clear();
}

/* -------------------- 收到 JSON -------------------- */
void ChatServer::jsonReceived(ServerWorker *sender, const QJsonObject &docObj)
{
    const QJsonValue typeVal = docObj.value("type");
    if (typeVal.isNull() || !typeVal.isString()) return;
    const QString type = typeVal.toString().toLower();

    if (type == "message") {
        const QString text = docObj.value("text").toString().trimmed();
        if (text.isEmpty()) return;

        saveMessageToLog(QString("%1: %2").arg(sender->userName(), text));

        QJsonObject msg;
        msg["type"] = "message";
        msg["text"] = text;
        msg["sender"] = sender->userName();
        broadcast(msg, sender);

    } else if (type == "private") {
        const QString text      = docObj.value("text").toString().trimmed();
        const QString receiver  = docObj.value("receiver").toString().trimmed();
        if (text.isEmpty() || receiver.isEmpty()) return;

        saveMessageToLog(QString("[私聊] %1 -> %2: %3")
                             .arg(sender->userName(), receiver, text));

        QJsonObject msg;
        msg["type"] = "private";
        msg["text"] = text;
        msg["sender"] = sender->userName();
        msg["receiver"] = receiver;
        sendPrivateMessage(msg, receiver);

    } else if (type == "login") {
        QString username = docObj.value("text").toString().trimmed();
        if (username.isEmpty())
            username = QString("匿名%1").arg(sender->socketDescriptor() % 1000);

        bool nameExists = false;
        {
            QMutexLocker locker(&m_clientsMutex);
            for (ServerWorker *w : m_clients)
                if (w != sender && w->userName() == username) {
                    nameExists = true;
                    break;
                }
        }
        if (nameExists)
            username = QString("%1_%2").arg(username).arg(QRandomGenerator::global()->bounded(100));

        sender->setUserName(username);
        emit logMessage(QString("用户登录: %1").arg(username));

        QJsonObject newUserMsg;
        newUserMsg["type"]     = "newuser";
        newUserMsg["username"] = username;
        broadcast(newUserMsg, sender);

        QJsonObject userListMsg;
        userListMsg["type"] = "userlist";
        QJsonArray userArray;
        {
            QMutexLocker locker(&m_clientsMutex);
            for (ServerWorker *w : m_clients)
                userArray.append(w == sender ? username + " (我)" : w->userName());
        }
        userListMsg["userlist"] = userArray;
        sender->sendJson(userListMsg);
    }
}

/* -------------------- 用户断开 -------------------- */
void ChatServer::userDisconnected(ServerWorker *worker)
{
    QString userName;
    {
        QMutexLocker locker(&m_clientsMutex);
        if (!m_clients.removeOne(worker))          // 关键③：先摘除
            return;
        userName = worker->userName();
    }

    QJsonObject leftMsg;
    leftMsg["type"]   = "message";
    leftMsg["sender"] = "系统";
    leftMsg["text"]   = QString("%1 离开了聊天室").arg(userName);
    broadcast(leftMsg, nullptr);

    QJsonObject disMsg;
    disMsg["type"]     = "userdisconnected";
    disMsg["username"] = userName;
    broadcast(disMsg, nullptr);

    saveMessageToLog(QString("用户离开: %1").arg(userName));
    emit logMessage(QString("%1(%2) 已断开，剩余 %3 人")
                        .arg(userName, worker->property("_seq").toString())
                        .arg(m_clients.size()));

    worker->stopWorker();
    // 关键④：延迟 delete，确保所有槽都返回
    QMetaObject::invokeMethod(worker, &QObject::deleteLater, Qt::QueuedConnection);
}

/* -------------------- 异常出错 -------------------- */
void ChatServer::handleClientError(ServerWorker *worker)
{
    userDisconnected(worker);   // 统一走安全清理流程
}
