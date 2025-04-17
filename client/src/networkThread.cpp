#include "../headers/networkThread.h"
#include <QHostAddress>

NetworkThread::NetworkThread(QObject *parent)
    : QThread(parent)
    , socket(nullptr)
    , connected(false)
    , shouldConnect(false)
    , shouldDisconnect(false)
    , hasMessageToSend(false)
{
}

NetworkThread::~NetworkThread()
{
    disconnectFromServer();
    quit();
    wait();
}

void NetworkThread::connectToServer(const QString &host, quint16 port)
{
    QMutexLocker locker(&mutex);
    this->host = host;
    this->port = port;
    shouldConnect = true;
}

void NetworkThread::disconnectFromServer()
{
    QMutexLocker locker(&mutex);
    shouldDisconnect = true;
}

void NetworkThread::sendMessage(const QString &message)
{
    QMutexLocker locker(&mutex);
    messageToSend = message;
    hasMessageToSend = true;
}

bool NetworkThread::isConnected() const
{
    QMutexLocker locker(&mutex);
    return connected;
}

void NetworkThread::run()
{
    socket = new QTcpSocket();
    socket->moveToThread(this);

    connect(socket, &QTcpSocket::connected, this, &NetworkThread::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &NetworkThread::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &NetworkThread::onReadyRead);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error),
            this, &NetworkThread::onError);

    while (!isInterruptionRequested()) {
        {
            QMutexLocker locker(&mutex);
            if (shouldConnect) {
                shouldConnect = false;
                socket->connectToHost(host, port);
            }
            if (shouldDisconnect) {
                shouldDisconnect = false;
                if (connected) {
                    socket->disconnectFromHost();
                    connected = false;
                }
            }
            if (hasMessageToSend) {
                hasMessageToSend = false;
                if (connected) {
                    QByteArray data = messageToSend.toUtf8() + "\n";
                    socket->write(data);
                }
            }
        }
        msleep(10); // Небольшая задержка для уменьшения нагрузки на CPU
    }

    delete socket;
}

void NetworkThread::onReadyRead()
{
    while (socket->canReadLine()) {
        QByteArray data = socket->readLine();
        QString message = QString::fromUtf8(data).trimmed();
        emit messageReceived(message);
    }
}

void NetworkThread::onConnected()
{
    QMutexLocker locker(&mutex);
    connected = true;
    emit connected();
}

void NetworkThread::onDisconnected()
{
    QMutexLocker locker(&mutex);
    connected = false;
    emit disconnected();
}

void NetworkThread::onError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    QString errorMessage = socket->errorString();
    emit errorOccurred(errorMessage);
    disconnectFromServer();
} 