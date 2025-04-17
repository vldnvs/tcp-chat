#include "../headers/networkManager.h"

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
    , networkThread(new NetworkThread(this))
{
    // Подключаем сигналы от потока к сигналам NetworkManager
    connect(networkThread, &NetworkThread::connected, this, &NetworkManager::connected);
    connect(networkThread, &NetworkThread::disconnected, this, &NetworkManager::disconnected);
    connect(networkThread, &NetworkThread::messageReceived, this, &NetworkManager::messageReceived);
    connect(networkThread, &NetworkThread::errorOccurred, this, &NetworkManager::errorOccurred);

    // Запускаем поток
    networkThread->start();
}

NetworkManager::~NetworkManager()
{
    networkThread->disconnectFromServer();
    networkThread->quit();
    networkThread->wait();
}

bool NetworkManager::connectToServer(const QString &host, quint16 port)
{
    if (networkThread->isConnected()) {
        return false;
    }

    networkThread->connectToServer(host, port);
    return true;
}

void NetworkManager::disconnectFromServer()
{
    networkThread->disconnectFromServer();
}

void NetworkManager::sendMessage(const QString &message)
{
    if (!networkThread->isConnected()) {
        emit errorOccurred("Not connected to server");
        return;
    }

    networkThread->sendMessage(message);
}

bool NetworkManager::isConnected() const
{
    return networkThread->isConnected();
} 