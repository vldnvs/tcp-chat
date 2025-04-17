#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include "networkManager.h"

class QTextEdit;
class QLineEdit;
class QPushButton;
class QListWidget;

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

private:
    void displayMessage(const QString &message);
    void sendChatMessage(const QString &message);

    NetworkManager *networkManager;
    QTextEdit *chatView;
    QLineEdit *messageEdit;
    QPushButton *sendButton;
    QListWidget *usersList;

    QString currentUsername;
};

#endif // CHATWINDOW_H