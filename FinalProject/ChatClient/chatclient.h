#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDataStream>

class ChatClient : public QObject
{
    Q_OBJECT
public:
    explicit ChatClient(QObject *parent = nullptr);

signals:
    void connected();
    void messageReceived(const QString &text);
    void jsonReceived(const QJsonObject &docObj);

public slots:
    void connectToServer(const QHostAddress &address, quint16 port);
    void disconnectFromHost();
    void sendMessage(const QString &text, const QString &type = "message");
    void sendJson(const QJsonObject &json);
    void sendJsonData(const QByteArray &jsonData);

private slots:
    void onReadyRead();

private:
    QTcpSocket *m_clientSocket;
};

#endif
