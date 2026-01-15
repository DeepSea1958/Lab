#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chatclient.h"
#include "privatechatwidget.h"
#include <QHostAddress>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>
#include <QTime>
#include <QRandomGenerator>
#include <QApplication>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_chatClient(new ChatClient(this))
    , m_msgStorage(nullptr)
    , m_userListModel(new QStringListModel(this))
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->loginPage);

    ui->userListView->setModel(m_userListModel);

    connect(m_chatClient, &ChatClient::connected, this, &MainWindow::connectedToServer);
    connect(m_chatClient, &ChatClient::jsonReceived, this, &MainWindow::jsonReceived);
    connect(ui->userListView, &QListView::doubleClicked,
            this, &MainWindow::onUserListDoubleClicked);
    m_privateTarget.clear();
    updateSendButtonText();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    QString server = ui->serverEdit->text().trimmed();
    if (server.isEmpty()) {
        QMessageBox::warning(this, "错误", "请输入服务器地址");
        return;
    }
    m_chatClient->connectToServer(QHostAddress(server), 1967);
}

void MainWindow::on_sayButton_clicked()
{
    QString text = ui->sayLineEdit->text().trimmed();
    if (text.isEmpty()) return;
    ui->sayLineEdit->clear();

    if (m_privateTarget.isEmpty()) {
        m_chatClient->sendMessage(text, "message");
        appendMessage("我", text, false);              // 公聊
    } else {
        QJsonObject obj;
        obj["type"] = "private";
        obj["text"] = text;
        obj["receiver"] = m_privateTarget;
        m_chatClient->sendJson(obj);
        /* 私聊：仅落盘，不公屏显示，传递 receiver 参数 */
        appendMessage(QString("我 → %1").arg(m_privateTarget), text, true, false, m_privateTarget);
    }
}

void MainWindow::on_logoutButton_clicked()
{
    m_chatClient->disconnectFromHost();
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
    m_userListModel->setStringList(QStringList());
    ui->roomTextEdit->clear();
    for (auto w : m_privateWindows) w->close();
    m_privateWindows.clear();
    m_privateTarget.clear();
    updateSendButtonText();

    if (m_msgStorage) {
        delete m_msgStorage;
        m_msgStorage = nullptr;
    }
}

void MainWindow::connectedToServer()
{
    ui->stackedWidget->setCurrentWidget(ui->chatPage);
    m_currentUser = ui->usernameEdit->text().trimmed();
    if (m_currentUser.isEmpty())
        m_currentUser = QString("匿名%1").arg(QRandomGenerator::global()->bounded(1000));

    m_msgStorage = new MsgStorage(m_currentUser, this);
    loadAndShowHistoryMessages();

    QJsonObject obj;
    obj["type"] = "login";
    obj["text"] = m_currentUser;
    m_chatClient->sendJson(obj);
}

void MainWindow::jsonReceived(const QJsonObject &docObj)
{
    const QJsonValue typeVal = docObj.value("type");
    if (typeVal.isNull() || !typeVal.isString()) return;
    QString type = typeVal.toString().toLower();

    if (type == "message") {
        QString sender = docObj.value("sender").toString();
        QString text   = docObj.value("text").toString();
        appendMessage(sender, text, false);                 // 公聊
    } else if (type == "private") {
        QString sender = docObj.value("sender").toString();
        QString text   = docObj.value("text").toString();
        openPrivateChat(sender);
        m_privateWindows[sender]->appendMessage(sender, text);
        /* 对方私聊：仅落盘，不公屏显示，传递 receiver 为当前用户 */
        appendMessage(sender, text, true, false, m_currentUser);
    } else if (type == "newuser") {
        userJoined(docObj.value("username").toString());
    } else if (type == "userdisconnected") {
        userLeft(docObj.value("username").toString());
    } else if (type == "userlist") {
        userListReceived(docObj.value("userlist").toVariant().toStringList());
    }
}

void MainWindow::userJoined(const QString &user)
{
    QStringList users = m_userListModel->stringList();
    users.append(user);
    m_userListModel->setStringList(users);
    appendMessage("系统", QString("%1 加入了聊天室").arg(user), false);
}

void MainWindow::userLeft(const QString &user)
{
    QStringList users = m_userListModel->stringList();
    users.removeAll(user);
    m_userListModel->setStringList(users);
    if (m_privateWindows.contains(user)) {
        m_privateWindows[user]->close();
        m_privateWindows.remove(user);
    }
}

void MainWindow::userListReceived(const QStringList &list)
{
    m_userListModel->setStringList(list);
}

void MainWindow::onUserListDoubleClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;
    QString target = m_userListModel->data(index, Qt::DisplayRole).toString();
    if (target.contains("(我)")) return;
    openPrivateChat(target);
}

void MainWindow::on_backToPublicButton_clicked()
{
    for (auto w : m_privateWindows) w->hide();
    raise(); activateWindow();
}

/* -------------------- 私聊窗口管理 -------------------- */
// 手动双击时打开私聊窗口，一次性加载双方完整记录
void MainWindow::openPrivateChat(const QString &target)
{
    if (m_privateWindows.contains(target)) {
        PrivateChatWidget *w = m_privateWindows.value(target);
        if (w) {
            w->show(); w->raise(); w->activateWindow();
            return;
        }
    }
    PrivateChatWidget *w = new PrivateChatWidget(target, nullptr);
    connect(w, &PrivateChatWidget::windowClosed,
            this, [this, target](){ m_privateWindows.remove(target); });
    connect(w, &PrivateChatWidget::sendPrivateMessage,
            this, [this](const QString &rcv, const QString &txt){
                QJsonObject obj{{"type","private"},{"text",txt},{"receiver",rcv}};
                m_chatClient->sendJson(obj);
                // 私聊窗口发送的消息，主动落盘并传递 receiver
                appendMessage("我", txt, true, false, rcv);
            });
    m_privateWindows[target] = w;

    /* 关键：一次性把双方历史记录全部 append 到窗口 */
    if (m_msgStorage) {
        QList<ChatMessage> history = m_msgStorage->loadMessages();
        for (const ChatMessage &msg : history) {
            if (!msg.isPrivate) continue;
            // 只要当前用户参与，且对方就是 target，就显示
            bool isSelfToTarget = (msg.sender == m_currentUser && msg.receiver == target);
            bool isTargetToSelf = (msg.sender == target && msg.receiver == m_currentUser);
            if (isSelfToTarget || isTargetToSelf) {
                QString showSender = (msg.sender == m_currentUser) ? "我" : msg.sender;
                w->appendMessage(showSender, msg.text);
            }
        }
    }
    w->show();
}

void MainWindow::closePrivateChat(const QString &target)
{
    if (!m_privateWindows.contains(target)) return;
    m_privateWindows[target]->deleteLater();
    m_privateWindows.remove(target);
}

void MainWindow::updateSendButtonText()
{
    ui->sayButton->setText(m_privateTarget.isEmpty() ? "发送"
                                                     : QString("私聊:%1").arg(m_privateTarget));
}

/* -------------------- 统一消息处理 -------------------- */
void MainWindow::appendMessage(const QString &sender,
                               const QString &text,
                               bool isPrivate,
                               bool showInPublic,
                               const QString &receiver)
{
    // 1. 公屏显示（私聊可关闭）
    if (showInPublic) {
        QString tm = QTime::currentTime().toString("hh:mm:ss");
        QString prefix = isPrivate ? "[私聊]" : "[公聊]";
        ui->roomTextEdit->append(QString("%1 %2 %3: %4").arg(tm, prefix, sender, text));
    }

    // 2. 持久化（无论是否显示都要存）
    if (m_msgStorage) {
        ChatMessage msg;
        msg.time  = QTime::currentTime().toString("hh:mm:ss");
        msg.sender= (sender.startsWith("我")) ? m_currentUser : sender;
        msg.text  = text;
        msg.isPrivate = isPrivate;
        // 使用传入的 receiver 参数，不再猜值
        msg.receiver = receiver;
        m_msgStorage->appendMessage(msg);
    }
}

/* 供 PrivateChatWidget 调用：对方消息落盘 */
void MainWindow::appendPrivateMessage(const QString &sender,
                                      const QString &text,
                                      const QString &receiver)
{
    // 传递 receiver 参数，确保落盘时 receiver 字段正确
    appendMessage(sender, text, true, false, receiver);
}

void MainWindow::loadAndShowHistoryMessages()
{
    if (!m_msgStorage) return;

    QList<ChatMessage> history = m_msgStorage->loadMessages();
    for (const ChatMessage &msg : history) {
        if (!msg.isPrivate) {
            // 公聊：直接打印到主屏
            QString showSender = (msg.sender == m_currentUser) ? "我" : msg.sender;
            ui->roomTextEdit->append(QString("%1 [公聊] %2: %3")
                                         .arg(msg.time, showSender, msg.text));
            continue;
        }
        /* 私聊：不做任何窗口操作，仅保留在磁盘里即可 */
    }
}
