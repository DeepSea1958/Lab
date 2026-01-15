#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QRunnable>
#include <QMutex>

class ServerWorker : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit ServerWorker(QObject *parent = nullptr);
    ~ServerWorker();

    bool setSocketDescriptor(qintptr socketDescriptor);
    QString userName() const;
    void setUserName(const QString &user);
    qintptr socketDescriptor() const;

    void disconnectFromClient();
    void sendJson(const QJsonObject &json);
    void sendJsonData(const QByteArray &jsonData);
    void stopWorker(); // 新增：主动停止线程接口

signals:
    void logMessage(const QString &msg);
    void jsonReceived(ServerWorker *sender, const QJsonObject &docObj);
    void disconnectedFromClient();
    void errorOccurred();
    void finished(); // 新增：线程结束信号

protected:
    void run() override; // QRunnable interface

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket *m_serverSocket;
    QString m_userName;
    qintptr m_socketDescriptor;
    mutable QMutex m_mutex;
    bool m_running;
};

#endif
