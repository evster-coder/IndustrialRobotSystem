#include "mainwindowapp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowApp w;
	//показываем форму
    w.show();
    return a.exec();
}
