#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>
#include <QString>
#include <memory>

class ServerAddressWindow;
class UsernameWindow;
class ChatWindow;
class NetworkManager;

class WindowManager : public QObject
{
    Q_OBJECT

public:
    explicit WindowManager(QObject *parent = nullptr);
    ~WindowManager();

    void showServerAddressWindow();

private slots:
    void onServerAddressAccepted(const QString &host, quint16 port);
    void onUsernameAccepted(const QString &username);
    void onConnected();
    void onDisconnected();
    void onNetworkError(const QString &error);

private:
    std::unique_ptr<ServerAddressWindow> serverAddressWindow;
    std::unique_ptr<UsernameWindow> usernameWindow;
    std::unique_ptr<ChatWindow> chatWindow;
    std::unique_ptr<NetworkManager> networkManager;

    QString host;
    quint16 port;
    QString currentUsername;
};

#endif // WINDOWMANAGER_H