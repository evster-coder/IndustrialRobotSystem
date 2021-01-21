#ifndef QLISTWIDGETLOGGER_H
#define QLISTWIDGETLOGGER_H

#include "LoggerImpl.h"

#include <string>
#include <QString>
#include <QListWidget>

//реализация логгера для вывода в QListWidget
class QListWidgetLogger : public LoggerImpl
{
    QListWidget *outLine;
public:
    QListWidgetLogger(QListWidget *listview);

    void printLog(string text);
};

#endif // QLISTWIDGETLOGGER_H
