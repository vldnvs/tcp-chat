#include "../headers/WindowManager.h"
#include <QDebug>

WindowManager::WindowManager(QObject *parent)
    : QObject(parent), serverWindow(new ServerAddressWindow),
      usernameWindow(new UsernameWindow), chatWindow(nullptr)
{
    // Подключаем сигналы первого окна к слоту обработки адреса сервера
    connect(serverWindow, &ServerAddressWindow::accepted, this, &WindowManager::onServerAddressAccepted);

    // Подключаем сигналы второго окна к слоту обработки имени пользователя
    connect(usernameWindow, &UsernameWindow::accepted, this, &WindowManager::onUsernameAccepted);
}

WindowManager::~WindowManager()
{
    // Освобождаем ресурсы
    delete serverWindow;
    delete usernameWindow;
    if (chatWindow) {
        delete chatWindow;
    }
}

void WindowManager::showServerAddressWindow()
{
    // Показываем первое окно (ввод адреса сервера)
    serverWindow->exec();
}

void WindowManager::onServerAddressAccepted(const QString &host, quint16 port)
{
    qDebug() << "Server address accepted:" << host << ":" << port;

    // Передаем данные в окно ввода имени через свойства
    usernameWindow->setProperty("host", host);
    usernameWindow->setProperty("port", port);

    // Показываем второе окно (ввод имени пользователя)
    usernameWindow->exec();
}

void WindowManager::onUsernameAccepted(const QString &username)
{
    qDebug() << "Username accepted:" << username;

    // Получаем ранее сохраненные данные о сервере
    QString host = usernameWindow->property("host").toString();
    quint16 port = usernameWindow->property("port").toUInt();

    // Создаем и показываем окно чата
    chatWindow = new ChatWindow(username, host, port);

    // Показываем окно чата
    chatWindow->show();
}