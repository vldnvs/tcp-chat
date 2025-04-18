#include "../headers/logger.h"
#include <QDir>
#include <QStandardPaths>
#include <QApplication>
#include <iostream>

Logger::Logger(QObject *parent)
    : QObject(parent)
    , currentLevel(DEBUG)
    , initialized(false)
{
    std::cout << "Logger constructor called - simplified version" << std::endl;
}

Logger::~Logger()
{
    std::cout << "Logger destructor called" << std::endl;
    if (logFile.isOpen()) {
        logStream.flush();
        logFile.close();
    }
}

Logger& Logger::instance()
{
    static Logger instance;
    return instance;
}

void Logger::setLogFile(const QString &filename)
{
    std::cout << "Logger::setLogFile called with: " << filename.toStdString() 
              << " (file operations disabled)" << std::endl;
    initialized = true;
}

void Logger::setLogLevel(LogLevel level)
{
    std::cout << "Logger::setLogLevel called with level: " << static_cast<int>(level) << std::endl;
    QMutexLocker locker(&mutex);
    currentLevel = level;
    initialized = true;
}

void Logger::debug(const QString &message)
{
    log(DEBUG, message);
}

void Logger::info(const QString &message)
{
    log(INFO, message);
}

void Logger::warning(const QString &message)
{
    log(WARNING, message);
}

void Logger::error(const QString &message)
{
    log(ERROR, message);
}

void Logger::critical(const QString &message)
{
    log(CRITICAL, message);
}

void Logger::log(LogLevel level, const QString &message)
{
    if (level < currentLevel) {
        return;
    }
    
    QMutexLocker locker(&mutex);
    
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString logEntry = QString("[%1] [%2] %3")
                       .arg(timestamp)
                       .arg(levelToString(level))
                       .arg(message);
    
    // Только вывод в консоль
    std::cout << logEntry.toStdString() << std::endl;
}

QString Logger::levelToString(LogLevel level)
{
    switch (level) {
        case DEBUG:    return "DEBUG";
        case INFO:     return "INFO";
        case WARNING:  return "WARNING";
        case ERROR:    return "ERROR";
        case CRITICAL: return "CRITICAL";
        default:       return "UNKNOWN";
    }
} 