#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QThreadPool>
#include <QVector>
#include <QMutex>
#include <QFile>
#include <QTextStream>

class ServerWorker;

class ChatServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ChatServer(QObject *parent = nullptr);
    ~ChatServer();

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    QThreadPool *m_threadPool;
    QVector<ServerWorker*> m_clients;
    QMutex m_clientsMutex;
    QFile m_logFile;
    QTextStream m_logStream;
    qint64 m_connSeq = 0;
    void broadcast(const QJsonObject &message, ServerWorker *exclude = nullptr);
    void sendPrivateMessage(const QJsonObject &message, const QString &receiver);
    void saveMessageToLog(const QString &message);

signals:
    void logMessage(const QString &msg);

public slots:
    void stopServer();
    void jsonReceived(ServerWorker *sender, const QJsonObject &docObj);
    void userDisconnected(ServerWorker *sender);
    void handleClientError(ServerWorker *sender);
};

#endif
