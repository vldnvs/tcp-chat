#include "../headers/UsernameWindow.h"
#include <QVBoxLayout>
#include <QRegExpValidator>
#include <QMessageBox>

UsernameWindow::UsernameWindow(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Enter Your Name");
    setFixedSize(300, 100);

    // Name input
    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Your name");
    nameEdit->setMaxLength(20);
    nameEdit->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9_]+"), this));

    // Continue button
    continueButton = new QPushButton("Continue", this);
    connect(continueButton, &QPushButton::clicked, this, &UsernameWindow::onContinueClicked);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(nameEdit);
    layout->addWidget(continueButton);
}

void UsernameWindow::onContinueClicked()
{
    QString username = nameEdit->text().trimmed();
    if (username.isEmpty()) {
        QMessageBox::warning(this, "Error", "Name cannot be empty");
        return;
    }

    emit accepted(username);
    accept();
}