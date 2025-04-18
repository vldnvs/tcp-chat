#include "../headers/serverAddressWindow.h"
#include "../headers/logger.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <iostream>

ServerAddressWindow::ServerAddressWindow(QWidget *parent)
    : QMainWindow(parent)
{
    std::cout << "Initializing ServerAddressWindow..." << std::endl;
    
    setWindowTitle("Enter Server Address");
    setFixedSize(400, 150);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // IP address input
    QHBoxLayout *ipLayout = new QHBoxLayout();
    QLabel *ipLabel = new QLabel("IP Address:", this);
    ipEdit = new QLineEdit(this);
    ipEdit->setPlaceholderText("Enter IP address or hostname");
    QRegularExpression ipRegex("^(localhost|(?:[0-9]{1,3}\\.){3}[0-9]{1,3})$");
    ipEdit->setValidator(new QRegularExpressionValidator(ipRegex, this));
    ipLayout->addWidget(ipLabel);
    ipLayout->addWidget(ipEdit);
    
    // Устанавливаем значение по умолчанию
    ipEdit->setText("localhost");

    // Port input
    QHBoxLayout *portLayout = new QHBoxLayout();
    QLabel *portLabel = new QLabel("Port:", this);
    portEdit = new QLineEdit(this);
    portEdit->setPlaceholderText("Enter port number");
    QRegularExpression portRegex("^[0-9]{1,5}$");
    portEdit->setValidator(new QRegularExpressionValidator(portRegex, this));
    portLayout->addWidget(portLabel);
    portLayout->addWidget(portEdit);
    
    // Устанавливаем значение по умолчанию
    portEdit->setText("13");

    // Connect button
    QPushButton *connectButton = new QPushButton("Connect", this);
    connect(connectButton, &QPushButton::clicked, this, &ServerAddressWindow::onConnectClicked);

    mainLayout->addLayout(ipLayout);
    mainLayout->addLayout(portLayout);
    mainLayout->addWidget(connectButton);
    
    std::cout << "ServerAddressWindow initialization complete" << std::endl;
    
    // Делаем активным поле IP-адреса при запуске
    ipEdit->setFocus();
}

void ServerAddressWindow::onConnectClicked()
{
    std::cout << "Connect button clicked" << std::endl;
    
    QString ip = ipEdit->text();
    QString portStr = portEdit->text();

    if (ip.isEmpty() || portStr.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter both IP address and port");
        return;
    }

    bool ok;
    quint16 port = portStr.toUShort(&ok);
    if (!ok || port == 0) {
        QMessageBox::warning(this, "Error", "Invalid port number");
        return;
    }

    std::cout << "Emitting serverAddressAccepted signal with IP: " 
              << ip.toStdString() << " and port: " << port << std::endl;
    
    emit serverAddressAccepted(ip, port);
}