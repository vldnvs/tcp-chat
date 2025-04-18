#include "../headers/windowManager.h"
#include "../headers/serverAddressWindow.h"
#include "../headers/usernameWindow.h"
#include "../headers/chatWindow.h"
#include "../headers/networkManager.h"
#include "../headers/logger.h"
#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include <memory>

WindowManager::WindowManager(QObject *parent)
    : QObject(parent)
    , serverAddressWindow(nullptr)
    , usernameWindow(nullptr)
    , chatWindow(nullptr)
    , networkManager(nullptr)
{
    std::cout << "WindowManager constructor called" << std::endl;
    LOG_DEBUG("WindowManager initialized");
}

WindowManager::~WindowManager()
{
    std::cout << "WindowManager destructor called" << std::endl;
    LOG_DEBUG("WindowManager destructor called");

}

void WindowManager::showServerAddressWindow()
{
    std::cout << "WindowManager::showServerAddressWindow() called" << std::endl;
    LOG_DEBUG("Showing server address window");
    if (!serverAddressWindow) {
        std::cout << "Creating new server address window" << std::endl;
        LOG_DEBUG("Creating new server address window");
        serverAddressWindow = std::make_unique<ServerAddressWindow>();
        
        std::cout << "Connecting serverAddressAccepted signal" << std::endl;
        connect(serverAddressWindow.get(), &ServerAddressWindow::serverAddressAccepted,
                this, &WindowManager::onServerAddressAccepted);
    }
    
    std::cout << "Showing server address window" << std::endl;
    serverAddressWindow->show();
    serverAddressWindow->raise();
    serverAddressWindow->activateWindow();
    std::cout << "Server address window should be visible now" << std::endl;
}

void WindowManager::onServerAddressAccepted(const QString &host, quint16 port)
{
    std::cout << "Server address accepted: " << host.toStdString() << ":" << port << std::endl;
    LOG_INFO(QString("Server address accepted: %1:%2").arg(host).arg(port));
    this->host = host;
    this->port = port;
    serverAddressWindow->hide();
    
    if (!usernameWindow) {
        std::cout << "Creating new username window" << std::endl;
        LOG_DEBUG("Creating new username window");
        usernameWindow = std::make_unique<UsernameWindow>();
        connect(usernameWindow.get(), &UsernameWindow::usernameAccepted,
                this, &WindowManager::onUsernameAccepted);
    }
    usernameWindow->show();
    usernameWindow->raise();
    usernameWindow->activateWindow();
    LOG_DEBUG("Username window displayed");
}

void WindowManager::onUsernameAccepted(const QString &username)
{
    std::cout << "Username accepted: " << username.toStdString() << std::endl;
    LOG_INFO(QString("Username accepted: %1").arg(username));
    usernameWindow->hide();
    currentUsername = username;
    
    if (!networkManager) {
        std::cout << "Creating network manager" << std::endl;
        LOG_DEBUG("Creating network manager");
        networkManager = std::make_unique<NetworkManager>();
        connect(networkManager.get(), &NetworkManager::connected,
                this, &WindowManager::onConnected);
        connect(networkManager.get(), &NetworkManager::disconnected,
                this, &WindowManager::onDisconnected);
        connect(networkManager.get(), &NetworkManager::errorOccurred,
                this, &WindowManager::onNetworkError);
        LOG_DEBUG("Network manager connections established");
    }
    
    if (!chatWindow) {
        std::cout << "Creating chat window" << std::endl;
        LOG_DEBUG("Creating chat window");
        chatWindow = std::make_unique<ChatWindow>(username, networkManager.get());
    }
    
    std::cout << "Showing chat window" << std::endl;
    chatWindow->show();
    chatWindow->raise();
    chatWindow->activateWindow();
    LOG_DEBUG("Chat window displayed");
    
    std::cout << "Connecting to server: " << host.toStdString() << ":" << port 
             << " as " << username.toStdString() << std::endl;
    LOG_INFO(QString("Attempting to connect to %1:%2 as %3").arg(host).arg(port).arg(username));
    QMetaObject::invokeMethod(networkManager.get(), [=](){
        networkManager->connectToServer(host, port, username);
    }, Qt::QueuedConnection);
}

void WindowManager::onConnected()
{
    std::cout << "Connection successful" << std::endl;
    LOG_INFO("Connection successful");
    if (chatWindow) {
        LOG_DEBUG("Connection status updated in chat window");
    }
}

void WindowManager::onDisconnected()
{
    std::cout << "Connection to server lost" << std::endl;
    LOG_WARNING("Connection to server lost");
    if (chatWindow) {
        LOG_DEBUG("Disconnection status updated in chat window");
    }
}

void WindowManager::onNetworkError(const QString &error)
{
    std::cerr << "Network error: " << error.toStdString() << std::endl;
    LOG_ERROR(QString("Network error occurred: %1").arg(error));
    QMessageBox::critical(nullptr, "Network Error", error);
    if (chatWindow) {
        LOG_DEBUG("Network error forwarded to chat window");
    }
}