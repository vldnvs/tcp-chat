#include "../headers/windowManager.h"
#include <QApplication>

WindowManager::WindowManager(QObject *parent)
    : QObject(parent)
    , serverWindow(nullptr)
    , usernameWindow(nullptr)
    , chatWindow(nullptr)
    , networkManager(new NetworkManager(this))
{
}

WindowManager::~WindowManager()
{
    delete serverWindow;
    delete usernameWindow;
    delete chatWindow;
}

void WindowManager::showServerAddressWindow()
{
    serverWindow = new ServerAddressWindow();
    connect(serverWindow, &ServerAddressWindow::connectionEstablished, this, &WindowManager::onServerAddressAccepted);
    serverWindow->show();
}

void WindowManager::onServerAddressAccepted()
{
    serverWindow->deleteLater();
    serverWindow = nullptr;

    usernameWindow = new UsernameWindow();
    connect(usernameWindow, &UsernameWindow::accepted, this, &WindowManager::onUsernameAccepted);
    usernameWindow->show();
}

void WindowManager::onUsernameAccepted(const QString &username)
{
    usernameWindow->deleteLater();
    usernameWindow = nullptr;

    chatWindow = new ChatWindow(username, networkManager);
    chatWindow->show();
}