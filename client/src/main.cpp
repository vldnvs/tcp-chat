#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include "../headers/windowManager.h"
#include "../headers/logger.h"

int main(int argc, char *argv[])
{
    try {
        QApplication app(argc, argv);
        
        std::cout << "Приложение запущено" << std::endl;
        
        try {
            Logger::instance().setLogLevel(DEBUG);
            LOG_INFO("TCP-Chat Client starting...");
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при инициализации логгера: " << e.what() << std::endl;
            QMessageBox::critical(nullptr, "Ошибка", QString("Ошибка при инициализации логгера: %1").arg(e.what()));
        }
        
        WindowManager windowManager;
        LOG_INFO("Opening server address window");
        windowManager.showServerAddressWindow();
        
        std::cout << "Запускаем цикл событий" << std::endl;
        
        return app.exec();
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << std::endl;
        QMessageBox::critical(nullptr, "Критическая ошибка", QString("Произошла критическая ошибка: %1").arg(e.what()));
        return 1;
    }
}