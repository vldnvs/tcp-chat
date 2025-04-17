#include <QApplication>
#include "../headers/windowManager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    WindowManager windowManager;
    windowManager.showServerAddressWindow();
    
    return app.exec();
}