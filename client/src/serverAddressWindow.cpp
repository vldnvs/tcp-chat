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
{
    setWindowTitle("Connect to Server");
    setFixedSize(300, 150);

    // IP input
    ipEdit = new QLineEdit(this);
    ipEdit->setPlaceholderText("IP Address");
    QRegExp ipRegex("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    ipEdit->setValidator(new QRegExpValidator(ipRegex, this));

    // Port input
    portEdit = new QLineEdit(this);
    portEdit->setPlaceholderText("Port");
    portEdit->setValidator(new QIntValidator(1, 65535, this));

    // Connect button
    connectButton = new QPushButton("Connect", this);
    connect(connectButton, &QPushButton::clicked, this, &ServerAddressWindow::onConnectClicked);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(ipEdit);
    layout->addWidget(portEdit);
    layout->addWidget(connectButton);
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

    emit accepted(ip, port);
    accept();
}