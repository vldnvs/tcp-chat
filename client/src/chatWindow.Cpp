#include "../headers/chatWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QMessageBox>

ChatWindow::ChatWindow(const QString &username, NetworkManager *networkManager, QWidget *parent)
    : QMainWindow(parent)
    , networkManager(networkManager)
    , currentUsername(username)
{
    setWindowTitle("Chat - " + username);
    setMinimumSize(600, 400);

    // Chat view
    chatView = new QTextEdit(this);
    chatView->setReadOnly(true);

    // Message input
    messageEdit = new QLineEdit(this);
    messageEdit->setPlaceholderText("Type your message...");

    // Send button
    sendButton = new QPushButton("Send", this);
    connect(sendButton, &QPushButton::clicked, this, &ChatWindow::onSendClicked);
    connect(messageEdit, &QLineEdit::returnPressed, this, &ChatWindow::onSendClicked);

    // Users list
    usersList = new QListWidget(this);
    usersList->setMaximumWidth(150);

    // Connect network manager signals
    connect(networkManager, &NetworkManager::messageReceived, this, &ChatWindow::onMessageReceived);
    connect(networkManager, &NetworkManager::errorOccurred, this, &ChatWindow::onConnectionError);
    connect(networkManager, &NetworkManager::disconnected, this, &ChatWindow::onDisconnected);

    // Layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    QVBoxLayout *chatLayout = new QVBoxLayout();

    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(messageEdit);
    inputLayout->addWidget(sendButton);

    chatLayout->addWidget(chatView);
    chatLayout->addLayout(inputLayout);

    mainLayout->addLayout(chatLayout, 1);
    mainLayout->addWidget(usersList);

    // Send initial join message
    sendChatMessage("JOIN " + username);
}

ChatWindow::~ChatWindow()
{
    if (networkManager->isConnected()) {
        sendChatMessage("LEAVE " + currentUsername);
    }
}

void ChatWindow::onSendClicked()
{
    QString message = messageEdit->text().trimmed();
    if (!message.isEmpty()) {
        sendChatMessage("MSG " + currentUsername + ": " + message);
        messageEdit->clear();
    }
}

void ChatWindow::onMessageReceived(const QString &message)
{
    if (message.startsWith("MSG ")) {
        displayMessage(message.mid(4));
    } else if (message.startsWith("JOIN ")) {
        QString username = message.mid(5);
        usersList->addItem(username);
        displayMessage(username + " joined the chat");
    } else if (message.startsWith("LEAVE ")) {
        QString username = message.mid(6);
        QList<QListWidgetItem*> items = usersList->findItems(username, Qt::MatchExactly);
        for (QListWidgetItem *item : items) {
            delete item;
        }
        displayMessage(username + " left the chat");
    }
}

void ChatWindow::onConnectionError(const QString &error)
{
    QMessageBox::critical(this, "Connection Error", error);
    close();
}

void ChatWindow::onDisconnected()
{
    QMessageBox::information(this, "Disconnected", "Connection to server lost");
    close();
}

void ChatWindow::displayMessage(const QString &message)
{
    chatView->append(message);
}

void ChatWindow::sendChatMessage(const QString &message)
{
    networkManager->sendMessage(message);
}