#include "../headers/serverAddressWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRegExpValidator>
#include <QMessageBox>

ServerAddressWindow::ServerAddressWindow(QWidget *parent)
    : QDialog(parent)
    , networkManager(new NetworkManager(this))
{
    setWindowTitle("Connect to Server");
    setFixedSize(300, 200);

    // IP input
    ipEdit = new QLineEdit(this);
    ipEdit->setPlaceholderText("IP Address");
    QRegExp ipRegex("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    ipEdit->setValidator(new QRegExpValidator(ipRegex, this));

    // Port input
    portEdit = new QLineEdit(this);
    portEdit->setPlaceholderText("Port");
    portEdit->setValidator(new QIntValidator(1, 65535, this));

    // Status label
    statusLabel = new QLabel("Enter server address and port", this);
    statusLabel->setAlignment(Qt::AlignCenter);

    // Connect button
    connectButton = new QPushButton("Connect", this);
    connect(connectButton, &QPushButton::clicked, this, &ServerAddressWindow::onConnectClicked);

    // Connect network manager signals
    connect(networkManager, &NetworkManager::errorOccurred, this, &ServerAddressWindow::onConnectionError);
    connect(networkManager, &NetworkManager::connected, this, &ServerAddressWindow::onConnectionSuccess);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(ipEdit);
    layout->addWidget(portEdit);
    layout->addWidget(statusLabel);
    layout->addWidget(connectButton);
}

ServerAddressWindow::~ServerAddressWindow()
{
    networkManager->disconnectFromServer();
}

void ServerAddressWindow::onConnectClicked()
{
    QString ip = ipEdit->text();
    QString portStr = portEdit->text();

    if (ip.isEmpty() || portStr.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all fields");
        return;
    }

    bool ok;
    quint16 port = portStr.toUShort(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "Invalid port number");
        return;
    }

    statusLabel->setText("Connecting...");
    connectButton->setEnabled(false);

    if (!networkManager->connectToServer(ip, port)) {
        statusLabel->setText("Already connected");
        connectButton->setEnabled(true);
    }
}

void ServerAddressWindow::onConnectionError(const QString &error)
{
    statusLabel->setText("Connection failed");
    QMessageBox::warning(this, "Connection Error", error);
    connectButton->setEnabled(true);
}

void ServerAddressWindow::onConnectionSuccess()
{
    statusLabel->setText("Connected successfully");
    emit connectionEstablished();
    accept();
}