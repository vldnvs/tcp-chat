#ifndef SERVERADDRESSWINDOW_H
#define SERVERADDRESSWINDOW_H

#include <QDialog>

class QLineEdit;
class QPushButton;

class ServerAddressWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ServerAddressWindow(QWidget *parent = nullptr);

signals:
    void accepted(const QString &host, quint16 port);

private slots:
    void onConnectClicked();

private:
    QLineEdit *ipEdit;
    QLineEdit *portEdit;
    QPushButton *connectButton;
};

#endif // SERVERADDRESSWINDOW_H