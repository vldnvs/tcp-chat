#include "../headers/usernameWindow.h"
#include <QVBoxLayout>
#include <QRegularExpressionValidator>
#include <QLabel>
#include <QPushButton>

UsernameWindow::UsernameWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Enter Username");
    setFixedSize(300, 150);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QLabel *label = new QLabel("Enter your username:", this);
    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("Username");

    // Валидатор для имени пользователя (буквы, цифры, подчеркивания)
    QRegularExpression regex("^[a-zA-Z0-9_]{3,16}$");
    usernameEdit->setValidator(new QRegularExpressionValidator(regex, this));

    QPushButton *okButton = new QPushButton("OK", this);
    connect(okButton, &QPushButton::clicked, this, &UsernameWindow::onOkClicked);

    mainLayout->addWidget(label);
    mainLayout->addWidget(usernameEdit);
    mainLayout->addWidget(okButton);
}

void UsernameWindow::onOkClicked()
{
    QString username = usernameEdit->text();
    if (!username.isEmpty()) {
        emit usernameAccepted(username);
    }
}