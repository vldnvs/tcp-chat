#ifndef SERVERADDRESSWINDOW_H
#define SERVERADDRESSWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>

class ServerAddressWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerAddressWindow(QWidget *parent = nullptr);

signals:
    void serverAddressAccepted(const QString &ip, quint16 port);

private slots:
    void onConnectClicked();

private:
    QLineEdit *ipEdit;
    QLineEdit *portEdit;
};

#endif // SERVERADDRESSWINDOW_H