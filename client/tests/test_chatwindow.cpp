#include <QtTest/QtTest>
#include "../headers/chatWindow.h"
#include "../headers/networkManager.h"

// Мок-объект для NetworkManager
class MockNetworkManager : public NetworkManager {
    Q_OBJECT
public:
    MockNetworkManager(QObject *parent = nullptr) : NetworkManager(parent), sentMessage("") {}
    QString sentMessage;
    bool connected = false;

    void sendMessage(const QString &msg) override {
        sentMessage = msg;
    }
    bool isConnected() const override { return connected; }
signals:
    void messageReceived(const QString &msg);
    void errorOccurred(const QString &err);
    void disconnected();
    void connected();
    void authorizedSignal();
};

class TestChatWindow : public QObject {
    Q_OBJECT
private slots:
    void test_onConnected_enablesInput() {
        MockNetworkManager net;
        ChatWindow win("user", &net);
        win.onConnected();
        QVERIFY(win.findChild<QLineEdit*>()->isEnabled());
        QVERIFY(win.findChild<QPushButton*>()->isEnabled());
    }

    void test_sendMessage_callsNetworkManager() {
        MockNetworkManager net;
        net.connected = true;
        ChatWindow win("user", &net);
        win.onConnected();
        QLineEdit *edit = win.findChild<QLineEdit*>();
        edit->setText("hello");
        win.onSendClicked();
        QCOMPARE(net.sentMessage, QString("MSG user: hello"));
    }

    void test_onMessageReceived_displaysMessage() {
        MockNetworkManager net;
        ChatWindow win("user", &net);
        win.show();
        emit net.messageReceived("MSG user2: hi!");
        QTextEdit *view = win.findChild<QTextEdit*>();
        QVERIFY(view->toPlainText().contains("user2: hi!"));
    }
};

QTEST_MAIN(TestChatWindow)
#include "test_chatwindow.moc"
