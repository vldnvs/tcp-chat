#ifndef USERNAMEWINDOW_H
#define USERNAMEWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

class UsernameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UsernameWindow(QWidget *parent = nullptr);

signals:
    void usernameAccepted(const QString &username);

private slots:
    void onOkClicked();

private:
    QLineEdit *usernameEdit;
};

#endif // USERNAMEWINDOW_H