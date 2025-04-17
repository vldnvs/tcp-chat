#ifndef SERVERADDRESSWINDOW_H
#define SERVERADDRESSWINDOW_H

#include <QDialog>
#include "networkManager.h"

class QLineEdit;
class QPushButton;
class QLabel;

class ServerAddressWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ServerAddressWindow(QWidget *parent = nullptr);
    ~ServerAddressWindow();

signals:
    void connectionEstablished();

private slots:
    void onConnectClicked();
    void onConnectionError(const QString &error);
    void onConnectionSuccess();

private:
    QLineEdit *ipEdit;
    QLineEdit *portEdit;
    QPushButton *connectButton;
    QLabel *statusLabel;
    NetworkManager *networkManager;
};

#endif // SERVERADDRESSWINDOW_H