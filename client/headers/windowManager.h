#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>
#include "serverAddressWindow.h"
#include "usernameWindow.h"
#include "chatWindow.h"
#include "networkManager.h"

class WindowManager : public QObject
{
    Q_OBJECT

public:
    explicit WindowManager(QObject *parent = nullptr);
    ~WindowManager();

    void showServerAddressWindow();  // Показывает первое окно для ввода адреса сервера

private slots:
    void onServerAddressAccepted();
    void onUsernameAccepted(const QString &username);                // Обработка данных из второго окна

private:
    ServerAddressWindow *serverWindow;  // Окно ввода адреса сервера
    UsernameWindow *usernameWindow;     // Окно ввода имени пользователя
    ChatWindow *chatWindow;             // Окно чата
    NetworkManager *networkManager;
};

#endif // WINDOWMANAGER_H