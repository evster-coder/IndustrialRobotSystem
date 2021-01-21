#include "QListWidgetLogger.h"

QListWidgetLogger::QListWidgetLogger(QListWidget* logger)
{
    this->outLine = logger;
}

void QListWidgetLogger::printLog(string text)
{
    outLine->addItem(QString::fromStdString(text));
}
