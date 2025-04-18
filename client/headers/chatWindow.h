#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <memory>
#include "networkManager.h"

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(const QString &username, NetworkManager *networkManager, QWidget *parent = nullptr);
    ~ChatWindow();

private slots:
    void onSendClicked();
    void onMessageReceived(const QString &message);
    void onConnectionError(const QString &error);
    void onDisconnected();
    void onConnected();
    void onAuthorized();

private:
    void setupUI();
    void setupConnections();
    void displayMessage(const QString &message);
    void sendChatMessage(const QString &message);
    void handleServerResponse(const QString &message);
    void updateUsersList(const QString &usersList);
    void displayHistory(const QString &history);
    void updateUserList(const QString &message);

    NetworkManager *networkManager;
    QString currentUsername;
    QTextEdit *chatView;
    QLineEdit *messageEdit;
    QPushButton *sendButton;
    QListWidget *usersList;
    std::unique_ptr<QThread> networkThread;
};

#endif // CHATWINDOW_H