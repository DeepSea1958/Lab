#include "chatclient.h"
#include <QDataStream>

ChatClient::ChatClient(QObject *parent)
    : QObject(parent), m_clientSocket(new QTcpSocket(this))
{
    connect(m_clientSocket, &QTcpSocket::connected, this, &ChatClient::connected);
    connect(m_clientSocket, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
}

void ChatClient::connectToServer(const QHostAddress &address, quint16 port)
{
    m_clientSocket->connectToHost(address, port);
}

void ChatClient::disconnectFromHost()
{
    m_clientSocket->disconnectFromHost();
}

void ChatClient::sendMessage(const QString &text, const QString &type)
{
    if (m_clientSocket->state() != QAbstractSocket::ConnectedState)
        return;

    QJsonObject message;
    message["type"] = type;
    message["text"] = text;

    sendJson(message);
}

void ChatClient::sendJson(const QJsonObject &json)
{
    sendJsonData(QJsonDocument(json).toJson(QJsonDocument::Compact));
}

void ChatClient::sendJsonData(const QByteArray &jsonData)
{
    if (m_clientSocket->state() != QAbstractSocket::ConnectedState)
        return;

    QDataStream serverStream(m_clientSocket);
    serverStream.setVersion(QDataStream::Qt_6_9);
    serverStream << jsonData;
}

void ChatClient::onReadyRead()
{
    QByteArray jsonData;
    QDataStream socketStream(m_clientSocket);
    socketStream.setVersion(QDataStream::Qt_6_9);

    while (m_clientSocket->bytesAvailable()) {
        socketStream.startTransaction();
        socketStream >> jsonData;

        if (socketStream.commitTransaction()) {
            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

            if (parseError.error == QJsonParseError::NoError && jsonDoc.isObject()) {
                emit jsonReceived(jsonDoc.object());
            }
        } else {
            break;
        }
    }
}
