#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>
#include "ServerAddressWindow.h"
#include "UsernameWindow.h"
#include "ChatWindow.h"

class WindowManager : public QObject
{
    Q_OBJECT

public:
    explicit WindowManager(QObject *parent = nullptr);
    ~WindowManager();

    void showServerAddressWindow();  // Показывает первое окно для ввода адреса сервера

private slots:
    void onServerAddressAccepted(const QString &host, quint16 port);  // Обработка данных из первого окна
    void onUsernameAccepted(const QString &username);                // Обработка данных из второго окна

private:
    ServerAddressWindow *serverWindow;  // Окно ввода адреса сервера
    UsernameWindow *usernameWindow;     // Окно ввода имени пользователя
    ChatWindow *chatWindow;             // Окно чата
};

#endif // WINDOWMANAGER_H