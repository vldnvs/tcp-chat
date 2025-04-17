#include <QApplication>
#include <QFile>
#include "../headers/WindowManager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile styleFile(":/styles.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        app.setStyleSheet(styleFile.readAll());
        styleFile.close();
    }

    WindowManager windowManager;
    windowManager.showServerAddressWindow();

    return app.exec();
}