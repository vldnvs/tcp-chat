#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMutex>
#include <QDebug>
#include <QObject>
#include <QMutexLocker>

enum LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Logger : public QObject
{
    Q_OBJECT

public:
    static Logger& instance();
    
    void setLogFile(const QString &filename);
    void setLogLevel(LogLevel level);
    
    void debug(const QString &message);
    void info(const QString &message);
    void warning(const QString &message);
    void error(const QString &message);
    void critical(const QString &message);
    
    void log(LogLevel level, const QString &message);

private:
    explicit Logger(QObject *parent = nullptr);
    ~Logger();
    
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    QString levelToString(LogLevel level);
    
    QFile logFile;
    QTextStream logStream;
    LogLevel currentLevel;
    QMutex mutex;
    bool initialized;
};

// Convenience macros
#define LOG_DEBUG(msg) Logger::instance().debug(msg)
#define LOG_INFO(msg) Logger::instance().info(msg)
#define LOG_WARNING(msg) Logger::instance().warning(msg)
#define LOG_ERROR(msg) Logger::instance().error(msg)
#define LOG_CRITICAL(msg) Logger::instance().critical(msg)

#endif // LOGGER_H 