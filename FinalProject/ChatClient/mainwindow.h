#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "msgstorage.h"
#include <QModelIndex>

class QStringListModel;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ChatClient;
class PrivateChatWidget;
class QListWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void appendPrivateMessage(const QString &sender,
                              const QString &text,
                              const QString &receiver);

private slots:
    void on_loginButton_clicked();
    void on_sayButton_clicked();
    void on_logoutButton_clicked();
    void connectedToServer();
    void jsonReceived(const QJsonObject &docObj);
    void userJoined(const QString &user);
    void userLeft(const QString &user);
    void userListReceived(const QStringList &list);
    void onUserListDoubleClicked(const QModelIndex &index);
    void on_backToPublicButton_clicked();

private:
    Ui::MainWindow *ui;
    ChatClient *m_chatClient;
    QString m_currentUser;
    QString m_privateTarget;   // 当前在主界面私聊对象（可选）
    QMap<QString, PrivateChatWidget*> m_privateWindows;
    MsgStorage *m_msgStorage;  // 消息存储对象
    QStringListModel *m_userListModel;

    void openPrivateChat(const QString &target);
    void closePrivateChat(const QString &target);
    void updateSendButtonText();
    /* 增加 receiver 参数，默认空字符串 */
    void appendMessage(const QString &sender,
                       const QString &text,
                       bool isPrivate = false,
                       bool showInPublic = true,
                       const QString &receiver = "");
    void loadAndShowHistoryMessages();
};

#endif // MAINWINDOW_H
