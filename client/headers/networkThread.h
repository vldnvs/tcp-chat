#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H

#include <QThread>
#include <QObject>
#include <QTcpSocket>
#include <QMutex>

class NetworkThread : public QThread
{
    Q_OBJECT

public:
    explicit NetworkThread(QObject *parent = nullptr);
    ~NetworkThread();

    void connectToServer(const QString &host, quint16 port);
    void disconnectFromServer();
    void sendMessage(const QString &message);
    bool isConnected() const;

signals:
    void connected();
    void disconnected();
    void messageReceived(const QString &message);
    void errorOccurred(const QString &error);

protected:
    void run() override;

private slots:
    void onReadyRead();
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket *socket;
    bool connected;
    QMutex mutex;
    QString host;
    quint16 port;
    bool shouldConnect;
    bool shouldDisconnect;
    QString messageToSend;
    bool hasMessageToSend;
};

#endif // NETWORKTHREAD_H 