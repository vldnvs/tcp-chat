#include "../headers/chatWindow.h"
#include "../headers/logger.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QMessageBox>
#include <QThread>
#include <iostream>
#include <memory>

ChatWindow::ChatWindow(const QString &username, NetworkManager *networkManager, QWidget *parent)
    : QMainWindow(parent)
    , networkManager(networkManager)
    , currentUsername(username)
    , networkThread(nullptr)
{
    LOG_INFO(QString("Initializing chat window for user: %1").arg(username));

    networkThread = std::make_unique<QThread>(this);
    networkManager->moveToThread(networkThread.get());
    connect(networkThread.get(), &QThread::finished, networkManager, &QObject::deleteLater);
    networkThread->start();

    setupUI();
    setupConnections();
    setWindowTitle("Chat - " + username);
    setMinimumSize(600, 400);
    LOG_DEBUG("Chat window initialized");
}

void ChatWindow::setupUI()
{
    LOG_DEBUG("Setting up chat window UI");
    
    // Chat view
    chatView = new QTextEdit(this);
    chatView->setReadOnly(true);
    LOG_DEBUG("Chat view created");

    // Message input
    messageEdit = new QLineEdit(this);
    messageEdit->setPlaceholderText("Type your message...");
    LOG_DEBUG("Message input created");

    // Send button
    sendButton = new QPushButton("Send", this);
    connect(sendButton, &QPushButton::clicked, this, &ChatWindow::onSendClicked);
    connect(messageEdit, &QLineEdit::returnPressed, this, &ChatWindow::onSendClicked);
    LOG_DEBUG("Send button and connections created");

    // Users list
    usersList = new QListWidget(this);
    usersList->setMaximumWidth(150);
    LOG_DEBUG("Users list created");

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
    LOG_DEBUG("UI layout completed");

    // Disable input until connected
    messageEdit->setEnabled(false);
    sendButton->setEnabled(false);
    LOG_DEBUG("Input disabled until connection confirmed");
}

void ChatWindow::setupConnections()
{
    LOG_DEBUG("Setting up network connections");
    // Все соединения через QueuedConnection для потокобезопасности
    connect(networkManager, &NetworkManager::messageReceived, this, &ChatWindow::onMessageReceived, Qt::QueuedConnection);
    connect(networkManager, &NetworkManager::errorOccurred, this, &ChatWindow::onConnectionError, Qt::QueuedConnection);
    connect(networkManager, &NetworkManager::disconnected, this, &ChatWindow::onDisconnected, Qt::QueuedConnection);
    connect(networkManager, &NetworkManager::connected, this, &ChatWindow::onConnected, Qt::QueuedConnection);
    connect(networkManager, &NetworkManager::authorizedSignal, this, &ChatWindow::onAuthorized, Qt::QueuedConnection);
    LOG_DEBUG("Network connections setup completed");
}

ChatWindow::~ChatWindow()
{
    LOG_INFO("Chat window destructor called");
    if (networkManager && networkManager->isConnected()) {
        LOG_DEBUG(QString("Sending LEAVE command for user: %1").arg(currentUsername));
        sendChatMessage("LEAVE " + currentUsername);
    }
    if (networkThread) {
        networkThread->quit();
        networkThread->wait();
        networkThread.reset();
    }
}

void ChatWindow::onConnected()
{
    LOG_INFO("Connection to server established, enabling chat UI");
    messageEdit->setEnabled(true);
    sendButton->setEnabled(true);
    
    // Отображаем системное сообщение о подключении
    displayMessage(QString("Вы подключились к чату как %1").arg(currentUsername));
}

void ChatWindow::onAuthorized()
{
    LOG_INFO("User authorized successfully");
    // Теперь сервер подтвердил авторизацию пользователя
}

void ChatWindow::onSendClicked()
{
    QString message = messageEdit->text().trimmed();
    if (!message.isEmpty()) {
        LOG_DEBUG(QString("Sending message: %1").arg(message));
        
        // Всегда добавляем префикс MSG для текстовых сообщений
        QString fullMessage = "MSG " + message;
        
        // Отображаем сообщение в собственном чате сразу после отправки
        QString selfMessage = currentUsername + ": " + message;
        displayMessage(selfMessage);
        
        networkManager->sendMessage(fullMessage);
        messageEdit->clear();
    } else {
        LOG_DEBUG("Attempted to send empty message, ignoring");
    }
}

void ChatWindow::onMessageReceived(const QString &message)
{
    LOG_DEBUG(QString("Processing received message: %1").arg(message));
    
    // Skip welcome and nickname prompt messages
    if (message.contains("Welcome to the chat server") || 
        message.contains("Please enter your nickname")) {
        LOG_DEBUG("Skipping server welcome message");
        return;
    }
    
    // Handle server responses (messages without username prefix)
    if (!message.contains(": ")) {
        LOG_DEBUG("Handling server response message");
        handleServerResponse(message);
        return;
    }
    
    // Handle chat messages and notifications
    LOG_DEBUG("Handling chat or notification message");
    displayMessage(message);
    updateUserList(message);
}

void ChatWindow::handleServerResponse(const QString &message)
{
    if (message.startsWith("USERS ")) {
        LOG_INFO("Received users list from server");
        updateUsersList(message.mid(6));
    }
    else if (message.startsWith("HISTORY ")) {
        LOG_INFO("Received chat history from server");
        displayHistory(message.mid(8));
    } else {
        LOG_WARNING(QString("Received unknown server response: %1").arg(message));
    }
}

void ChatWindow::updateUsersList(const QString &usersList)
{
    LOG_DEBUG(QString("Updating users list with: %1").arg(usersList));
    QStringList users = usersList.split(',', Qt::SkipEmptyParts);
    this->usersList->clear();
    LOG_DEBUG(QString("Found %1 users in list").arg(users.size()));
    
    for (const QString &user : users) {
        QString cleanUser = user.trimmed();
        if (!cleanUser.isEmpty()) {
            this->usersList->addItem(cleanUser);
            LOG_DEBUG(QString("Added user to list: %1").arg(cleanUser));
        }
    }
}

void ChatWindow::displayHistory(const QString &history)
{
    LOG_DEBUG("Processing chat history");
    chatView->clear();
    QStringList messages = history.split("|", Qt::SkipEmptyParts);
    LOG_DEBUG(QString("History contains %1 messages").arg(messages.size()));
    
    for (const QString &msg : messages) {
        QString trimmedMsg = msg.trimmed();
        if (!trimmedMsg.isEmpty()) {
            LOG_DEBUG(QString("Adding history message: %1").arg(trimmedMsg));
            displayMessage(trimmedMsg);
        }
    }
}

void ChatWindow::updateUserList(const QString &message)
{
    LOG_DEBUG(QString("Checking message for user update: %1").arg(message));
    if (message.contains(": JOIN ")) {
        int colonPos = message.indexOf(':');
        if (colonPos > 0) {
            QString username = message.mid(colonPos + 6).trimmed();
            if (!username.isEmpty()) {
                LOG_INFO(QString("User joined: %1").arg(username));
                QList<QListWidgetItem*> existing = usersList->findItems(username, Qt::MatchExactly);
                if (existing.isEmpty()) {
                    usersList->addItem(username);
                    LOG_DEBUG(QString("Added %1 to users list").arg(username));
                } else {
                    LOG_WARNING(QString("User %1, tried to join but already in list").arg(username));
                }
            }
        }
    }
    else if (message.contains(": LEAVE ")) {
        int colonPos = message.indexOf(':');
        if (colonPos > 0) {
            QString username = message.mid(colonPos + 7).trimmed();
            LOG_INFO(QString("User left: %1").arg(username));
            QList<QListWidgetItem*> items = usersList->findItems(username, Qt::MatchExactly);
            LOG_DEBUG(QString("Found %1 entries to remove for user %2").arg(items.size()).arg(username));
            for (QListWidgetItem *item : items) {
                delete item;
            }
        }
    }
}

void ChatWindow::onConnectionError(const QString &error)
{
    LOG_ERROR(QString("Connection error: %1").arg(error));
    QMessageBox::critical(this, "Connection Error", error);
    close();
}

void ChatWindow::onDisconnected()
{
    LOG_WARNING("Disconnected from server");
    QMessageBox::information(this, "Disconnected", "Connection to server lost");
    close();
}

void ChatWindow::displayMessage(const QString &message)
{
    LOG_DEBUG(QString("Displaying message in chat view: %1").arg(message));
    chatView->append(message);
}

void ChatWindow::sendChatMessage(const QString &message)
{
    if (!networkManager->isConnected()) {
        LOG_ERROR(QString("Cannot send message - not connected: %1").arg(message));
        return;
    }
    LOG_DEBUG(QString("Sending chat message: %1").arg(message));
    networkManager->sendMessage(message);
}