#include <QtTest/QtTest>
#include "../headers/serverAddressWindow.h"

class TestServerAddressWindow : public QObject {
    Q_OBJECT
private slots:
    void test_invalidAddress_disablesOk() {
        ServerAddressWindow win;
        QLineEdit *edit = win.findChild<QLineEdit*>();
        QPushButton *ok = win.findChild<QPushButton*>("okButton");
        edit->setText("not-an-ip");
        QTest::keyClick(edit, Qt::Key_A);
        QVERIFY(!ok->isEnabled());
    }
    void test_validAddress_enablesOk() {
        ServerAddressWindow win;
        QLineEdit *edit = win.findChild<QLineEdit*>();
        QPushButton *ok = win.findChild<QPushButton*>("okButton");
        edit->setText("127.0.0.1");
        QTest::keyClick(edit, Qt::Key_A);
        QVERIFY(ok->isEnabled());
    }
};

QTEST_MAIN(TestServerAddressWindow)
#include "test_serveraddresswindow.moc"
