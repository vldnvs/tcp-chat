#include "../headers/chatWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QMessageBox>

ChatWindow::ChatWindow(const QString &username, const QString &host, quint16 port, QWidget *parent)
    : QMainWindow(parent), currentUsername(username), serverHost(host), serverPort(port)
{
    setWindowTitle("Chat Room - " + username);
    setMinimumSize(800, 600);

    // Создаем виджеты
    chatView = new QTextEdit(this);
    chatView->setReadOnly(true);
    chatView->setStyleSheet("background: #4a3a3a; border-radius: 8px; padding: 10px;");

    messageEdit = new QLineEdit(this);
    messageEdit->setPlaceholderText("Type your message...");
    messageEdit->setStyleSheet("background: #4a3a3a; border-radius: 8px; padding: 8px; margin: 5px 0;");

    sendButton = new QPushButton("Send", this);
    sendButton->setStyleSheet("padding: 8px 16px;");

    usersList = new QListWidget(this);
    usersList->setStyleSheet("background: #4a3a3a; border-radius: 8px;");

    // Левая панель (чат)
    QWidget *leftPanel = new QWidget(this);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->addWidget(chatView);
    leftLayout->addWidget(messageEdit);
    leftLayout->addWidget(sendButton);
    leftLayout->setSpacing(5);
    leftLayout->setContentsMargins(10, 10, 10, 10);

    // Разделитель
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(leftPanel);
    splitter->addWidget(usersList);
    splitter->setSizes({600, 200});
    splitter->setStyleSheet("QSplitter::handle { background: #5c4b4b; }");

    // Основной layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(splitter);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Подключаем события
    connect(sendButton, &QPushButton::clicked, this, &ChatWindow::onSendClicked);
    connect(messageEdit, &QLineEdit::returnPressed, this, &ChatWindow::onSendClicked);

    // Инициализация сокета
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &ChatWindow::onMessageReceived);
    connect(socket, &QTcpSocket::connected, this, &ChatWindow::onConnected);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
            this, &ChatWindow::onError);

    // Подключение к серверу
    connectToServer();
}

ChatWindow::~ChatWindow()
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->disconnectFromHost();
    }
}

void ChatWindow::connectToServer()
{
    socket->connectToHost(serverHost, serverPort);
    displayMessage("Connecting to server...");
}

void ChatWindow::onSendClicked()
{
    QString message = messageEdit->text().trimmed();
    if (!message.isEmpty()) {
        socket->write(QString("%1: %2\n").arg(currentUsername, message).toUtf8());
        messageEdit->clear();
    }
}

void ChatWindow::onMessageReceived()
{
    while (socket->canReadLine()) {
        QString message = QString::fromUtf8(socket->readLine()).trimmed();
        displayMessage(message);
    }
}

void ChatWindow::onConnected()
{
    displayMessage("Connected to server!");
    socket->write(QString("USERNAME:%1\n").arg(currentUsername).toUtf8()); // Отправляем имя пользователя
}

void ChatWindow::onDisconnected()
{
    displayMessage("Disconnected from server.");
}

void ChatWindow::onError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    QMessageBox::critical(this, "Error", socket->errorString());
}

void ChatWindow::displayMessage(const QString &message)
{
    chatView->append(message);
    chatView->verticalScrollBar()->setValue(chatView->verticalScrollBar()->maximum());
}