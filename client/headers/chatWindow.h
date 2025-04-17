#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

class QTextEdit;
class QLineEdit;
class QPushButton;
class QListWidget;

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(const QString &username, const QString &host, quint16 port, QWidget *parent = nullptr);
    ~ChatWindow();

signals:
    void sendMessage(const QString &message);

private slots:
    void onSendClicked();
    void onMessageReceived();
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);

private:
    void connectToServer();
    void displayMessage(const QString &message);

    QTcpSocket *socket;
    QTextEdit *chatView;
    QLineEdit *messageEdit;
    QPushButton *sendButton;
    QListWidget *usersList;

    QString currentUsername;
    QString serverHost;
    quint16 serverPort;
};

#endif // CHATWINDOW_H