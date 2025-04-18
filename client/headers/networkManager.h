#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QString>

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();

    bool connectToServer(const QString &host, quint16 port, const QString &username);
    void disconnectFromServer();
    void sendMessage(const QString &message);
    bool isConnected() const { return socket && socket->state() == QAbstractSocket::ConnectedState; }
    QString getUsername() const { return username; }
    bool isAuthorized() const { return authorized; }

signals:
    void connected();
    void disconnected();
    void messageReceived(const QString &message);
    void errorOccurred(const QString &error);
    void authorizedSignal();

private slots:
    void onSocketConnected();
    void onSocketDisconnected();
    void onSocketError(QAbstractSocket::SocketError socketError);
    void onSocketReadyRead();

private:
    void handleIncomingData();
    void sendData(const QByteArray &data);

    QTcpSocket *socket;
    QString username;
    QByteArray buffer;
    bool authorized = false;
};

#endif // NETWORKMANAGER_H 