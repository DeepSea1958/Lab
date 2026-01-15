// msgstorage.cpp
#include "msgstorage.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDir>
#include <QStandardPaths>

QJsonObject ChatMessage::toJson() const
{
    QJsonObject obj;
    obj["time"] = time;
    obj["sender"] = sender;
    obj["text"] = text;
    obj["isPrivate"] = isPrivate;
    obj["receiver"] = receiver;
    return obj;
}

ChatMessage ChatMessage::fromJson(const QJsonObject &obj)
{
    ChatMessage msg;
    msg.time = obj["time"].toString();
    msg.sender = obj["sender"].toString();
    msg.text = obj["text"].toString();
    msg.isPrivate = obj["isPrivate"].toBool();
    msg.receiver = obj["receiver"].toString();
    return msg;
}

MsgStorage::MsgStorage(const QString &userName, QObject *parent)
    : QObject(parent)
{
    // 存储路径：用户目录/chat_history/用户名/chat_history.json
    QString basePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    basePath += "/chat_history/" + userName;
    QDir dir(basePath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    m_storagePath = dir.filePath(m_fileName);
}

QList<ChatMessage> MsgStorage::loadMessages()
{
    QList<ChatMessage> messages;
    QFile file(m_storagePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return messages; // 文件不存在则返回空列表
    }

    QByteArray data = file.readAll();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    if (error.error != QJsonParseError::NoError || !doc.isArray()) {
        file.close();
        return messages;
    }

    QJsonArray arr = doc.array();
    for (const QJsonValue &val : arr) {
        if (val.isObject()) {
            messages.append(ChatMessage::fromJson(val.toObject()));
        }
    }
    file.close();
    return messages;
}

void MsgStorage::appendMessage(const ChatMessage &msg)
{
    QList<ChatMessage> messages = loadMessages();
    messages.append(msg);

    // 写入文件
    QJsonArray arr;
    for (const ChatMessage &m : messages) {
        arr.append(m.toJson());
    }

    QFile file(m_storagePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QJsonDocument doc(arr);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
}

void MsgStorage::clearMessages()
{
    QFile file(m_storagePath);
    if (file.exists()) {
        file.remove();
    }
}
