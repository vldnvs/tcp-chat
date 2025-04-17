#ifndef USERNAMEWINDOW_H
#define USERNAMEWINDOW_H

#include <QDialog>

class QLineEdit;
class QPushButton;

class UsernameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UsernameWindow(QWidget *parent = nullptr);

signals:
    void accepted(const QString &username);

private slots:
    void onContinueClicked();

private:
    QLineEdit *nameEdit;
    QPushButton *continueButton;
};

#endif // USERNAMEWINDOW_H