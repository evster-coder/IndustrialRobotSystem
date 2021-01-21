#ifndef MAINWINDOWAPP_H
#define MAINWINDOWAPP_H

#include <QMainWindow>
#include <QVector>

#include "dialogaddrobot.h"
#include "dialogdeleterobot.h"

#include "src/FacadeSystem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowApp; }
QT_END_NAMESPACE

/*Интерфейс приложения - основное окно*/
class MainWindowApp : public QMainWindow
{
    Q_OBJECT

public:
    MainWindowApp(QWidget *parent = nullptr);
    ~MainWindowApp();

    //обновление списка роботов
    void refreshRobotsList();

private slots:
    //вызов окна внесения нового робота в систему
    void addNewRobotDialog();

    //вызов окна удаления робота из системы
    void eraseRobotDialog();

    //печать информации о роботе и его команды
    void showRobotInfo();

    //включение выделенного робота
    void turnRobotOn();

    //отключение выделенного робота
    void turnRobotOff();

    //удаление выделенной команды
    void eraseCommand();

private:
    Ui::MainWindowApp *ui;
    FacadeSystem *system;
    const QString emptyCommands = "Команды отсутствуют";
};
#endif // MAINWINDOWAPP_H
