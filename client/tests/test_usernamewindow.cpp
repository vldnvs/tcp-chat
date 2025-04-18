#include <QtTest/QtTest>
#include "../headers/usernameWindow.h"

class TestUsernameWindow : public QObject {
    Q_OBJECT
private slots:
    void test_emptyUsername_disablesOk() {
        UsernameWindow win;
        QLineEdit *edit = win.findChild<QLineEdit*>();
        QPushButton *ok = win.findChild<QPushButton*>("okButton");
        edit->setText("");
        QTest::keyClick(edit, Qt::Key_A); // simulate typing
        QVERIFY(!ok->isEnabled());
    }
    void test_validUsername_enablesOk() {
        UsernameWindow win;
        QLineEdit *edit = win.findChild<QLineEdit*>();
        QPushButton *ok = win.findChild<QPushButton*>("okButton");
        edit->setText("user1");
        QTest::keyClick(edit, Qt::Key_A);
        QVERIFY(ok->isEnabled());
    }
};

QTEST_MAIN(TestUsernameWindow)
#include "test_usernamewindow.moc"
