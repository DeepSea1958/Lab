// msgstorage.h
#ifndef MSGSTORAGE_H
#define MSGSTORAGE_H

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QList>

struct ChatMessage {
    QString time;      // 消息时间
    QString sender;    // 发送者
    QString text;      // 消息内容
    bool isPrivate;    // 是否私聊
    QString receiver;  // 私聊接收者（仅私聊有效）

    // 转换为JSON对象
    QJsonObject toJson() const;
    // 从JSON对象解析
    static ChatMessage fromJson(const QJsonObject &obj);
};

class MsgStorage : public QObject
{
    Q_OBJECT
public:
    explicit MsgStorage(const QString &userName, QObject *parent = nullptr);

    // 加载本地存储的消息
    QList<ChatMessage> loadMessages();
    // 追加单条消息到本地存储
    void appendMessage(const ChatMessage &msg);
    // 清空消息记录
    void clearMessages();

private:
    QString m_storagePath;  // 本地存储文件路径
    const QString m_fileName = "chat_history.json"; // 存储文件名
};

#endif // MSGSTORAGE_H
