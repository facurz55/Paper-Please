#ifndef LOGS_H
#define LOGS_H
#include <QString>
#include <QDateTime>
#include <QDebug>
#include <QFile>
class Logs
{
public:
    Logs();
    ~Logs();
    void setText(QString texto);
};

#endif // LOGS_H
