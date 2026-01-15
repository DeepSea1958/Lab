#include "serverworker.h"
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QHostAddress>
#include <QEventLoop>
#include <QCoreApplication>

ServerWorker::ServerWorker(QObject *parent)
    : QObject(parent), m_serverSocket(nullptr), m_socketDescriptor(0), m_running(false)
{
    setAutoDelete(true);
}

ServerWorker::~ServerWorker()
{
    QMutexLocker locker(&m_mutex);
    if (m_serverSocket) {
        m_serverSocket->abort();
        m_serverSocket->deleteLater();
    }
    m_running = false;
}

bool ServerWorker::setSocketDescriptor(qintptr socketDescriptor)
{
    QMutexLocker locker(&m_mutex);
    m_socketDescriptor = socketDescriptor;
    return true;
}

qintptr ServerWorker::socketDescriptor() const
{
    QMutexLocker locker(&m_mutex);
    return m_socketDescriptor;
}

QString ServerWorker::userName() const
{
    QMutexLocker locker(&m_mutex);
    return m_userName;
}

void ServerWorker::setUserName(const QString &user)
{
    QMutexLocker locker(&m_mutex);
    m_userName = user;
}

void ServerWorker::run()
{
    m_serverSocket = new QTcpSocket;
    if (!m_serverSocket->setSocketDescriptor(m_socketDescriptor)) {
        emit errorOccurred();
        return;
    }

    connect(m_serverSocket, &QTcpSocket::readyRead,
            this, &ServerWorker::onReadyRead, Qt::QueuedConnection);
    connect(m_serverSocket, &QTcpSocket::disconnected,
            this, &ServerWorker::onDisconnected, Qt::QueuedConnection);

    m_running = true;
    emit logMessage(QString("Worker started for socket %1").arg(m_socketDescriptor));

    // 使用QEventLoop实现优雅退出
    QEventLoop loop;
    connect(this, &ServerWorker::finished, &loop, &QEventLoop::quit);
    connect(m_serverSocket, &QTcpSocket::disconnected, &loop, &QEventLoop::quit);

    while (m_running && m_serverSocket->state() == QTcpSocket::ConnectedState) {
        if (m_serverSocket->bytesAvailable() == 0) {
            m_serverSocket->waitForReadyRead(100);
        } else {
            QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
        }
    }

    // 主动清理socket
    m_serverSocket->disconnectFromHost();
    if (m_serverSocket->state() != QTcpSocket::UnconnectedState) {
        m_serverSocket->waitForDisconnected(1000);
    }

    emit finished();
    loop.exec();

    m_running = false;
}

void ServerWorker::onReadyRead()
{
    QByteArray jsonData;
    QDataStream socketStream(m_serverSocket);
    socketStream.setVersion(QDataStream::Qt_6_9);

    while (m_serverSocket->bytesAvailable()) {
        socketStream.startTransaction();
        socketStream >> jsonData;

        if (socketStream.commitTransaction()) {
            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

            if (parseError.error == QJsonParseError::NoError && jsonDoc.isObject()) {
                emit jsonReceived(this, jsonDoc.object());
            }
        } else {
            break;
        }
    }
}

void ServerWorker::sendJson(const QJsonObject &json)
{
    sendJsonData(QJsonDocument(json).toJson(QJsonDocument::Compact));
}

void ServerWorker::sendJsonData(const QByteArray &jsonData)
{
    QMutexLocker locker(&m_mutex);
    if (m_serverSocket && m_serverSocket->state() == QTcpSocket::ConnectedState) {
        QDataStream socketStream(m_serverSocket);
        socketStream.setVersion(QDataStream::Qt_6_9);
        socketStream << jsonData;
    }
}

void ServerWorker::disconnectFromClient()
{
    QMutexLocker locker(&m_mutex);
    m_running = false;
}

void ServerWorker::onDisconnected()
{
    m_running = false;
    emit disconnectedFromClient();
}

// 新增：停止worker线程
void ServerWorker::stopWorker()
{
    QMutexLocker locker(&m_mutex);
    m_running = false;
    if (m_serverSocket) {
        m_serverSocket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
        m_serverSocket->abort();
    }
    emit finished();
}
