#include "../headers/networkManager.h"
#include "../headers/logger.h"
#include <QHostAddress>
#include <QDataStream>
#include <QRegularExpression>

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
    , socket(new QTcpSocket(this))
    , username()
    , authorized(false)
{
    LOG_DEBUG("NetworkManager initialized");
    
    // Connect socket signals
    connect(socket, &QTcpSocket::connected, this, &NetworkManager::onSocketConnected);
    connect(socket, &QTcpSocket::disconnected, this, &NetworkManager::onSocketDisconnected);
    connect(socket, &QTcpSocket::errorOccurred, this, &NetworkManager::onSocketError);
    connect(socket, &QTcpSocket::readyRead, this, &NetworkManager::onSocketReadyRead);
    
    LOG_DEBUG("NetworkManager signals connected");
}

NetworkManager::~NetworkManager()
{
    LOG_DEBUG("NetworkManager destructor called");
    disconnectFromServer();
    delete socket;
}

bool NetworkManager::connectToServer(const QString &host, quint16 port, const QString &username)
{
    this->username = username;
    authorized = false;
    
    // Convert localhost to 127.0.0.1
    QString connectIp = host;
    if (host == "localhost" || host == "0.0.0.0") {
        connectIp = "127.0.0.1";
        LOG_DEBUG(QString("Converted host from %1 to %2").arg(host).arg(connectIp));
    }

    LOG_INFO(QString("Connecting to %1:%2 as '%3'").arg(connectIp).arg(port).arg(username));
    socket->connectToHost(connectIp, port);
    
    return true;
}

void NetworkManager::disconnectFromServer()
{
    if (socket->state() != QAbstractSocket::UnconnectedState) {
        LOG_INFO("Disconnecting from server");
        socket->disconnectFromHost();
    }
}

void NetworkManager::sendMessage(const QString &message)
{
    if (!isConnected()) {
        LOG_WARNING("Cannot send message - not connected");
        return;
    }

    // Просто отправляем сообщение как есть
    QByteArray data = message.toUtf8() + "\n";
    LOG_DEBUG(QString("Sending message: %1").arg(message));
    sendData(data);
}

void NetworkManager::onSocketConnected()
{
    LOG_INFO("Connected to server");
    emit connected();
}

void NetworkManager::onSocketDisconnected()
{
    LOG_INFO("Disconnected from server");
    authorized = false;
    emit disconnected();
}

void NetworkManager::onSocketError(QAbstractSocket::SocketError socketError)
{
    QString errorMessage = socket->errorString();
    QString errorCode = QString::number(static_cast<int>(socketError));
    LOG_ERROR(QString("Socket error [%1]: %2").arg(errorCode).arg(errorMessage));
    emit errorOccurred(errorMessage);
}

void NetworkManager::onSocketReadyRead()
{
    QByteArray newData = socket->readAll();
    buffer.append(newData);
    LOG_DEBUG(QString("Received raw data (%1 bytes)").arg(newData.size()));
    handleIncomingData();
}

void NetworkManager::handleIncomingData()
{
    while (!buffer.isEmpty()) {
        int newlinePos = buffer.indexOf('\n');
        if (newlinePos == -1) {
            newlinePos = buffer.indexOf('\r');
            if (newlinePos == -1) {
                LOG_DEBUG(QString("Incomplete message in buffer (%1 bytes), waiting for more data").arg(buffer.size()));
                return;
            }
        }

        // Extract the message
        QByteArray messageData = buffer.left(newlinePos);
        buffer.remove(0, newlinePos + 1); // Remove the message and the line ending

        // Convert to string and clean the message
        QString message = QString::fromUtf8(messageData).trimmed();
        
        // Skip empty messages
        if (message.isEmpty()) {
            LOG_DEBUG("Skipping empty message");
            continue;
        }
        
        // Clean binary data from the message
        QString originalMessage = message;
        message = message.replace(QRegularExpression("[\\x00-\\x1F\\x7F-\\xFF]"), "");
        if (originalMessage != message) {
            LOG_WARNING("Message contained binary data, cleaned it");
        }
        
        // Skip if message is empty after cleaning
        if (message.isEmpty()) {
            LOG_DEBUG("Message is empty after cleaning, skipping");
            continue;
        }
        
        LOG_INFO(QString("Received message: %1").arg(message));
        
        // Проверка на авторизацию - пользователь считается авторизованным после первого сообщения
        // от сервера, которое содержит "USERS"
        if (!authorized && message.startsWith("USERS ")) {
            authorized = true;
            LOG_INFO("User authorized successfully");
            emit authorizedSignal();
        }
        
        emit messageReceived(message);
    }
}

void NetworkManager::sendData(const QByteArray &data)
{
    qint64 bytesSent = socket->write(data);
    
    if (bytesSent != data.size()) {
        LOG_WARNING(QString("Not all data was sent: %1/%2 bytes").arg(bytesSent).arg(data.size()));
    } else {
        LOG_DEBUG(QString("Sent %1 bytes of data").arg(bytesSent));
    }
}