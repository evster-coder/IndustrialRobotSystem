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

    void turnOffButtons();

    void turnOnButtons();

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

    //добавление новой команды из lineEdit
    void addNewCommand();

    //выполнение команд шаг за шагом (по одной у каждого робота, пока все не выполнятся)
    void makeCommandsOneToAnother();

    //выполнение команд параллельно
    void makeCommandsParallel();

    //выполнение команд последовательно
    void makeCommandsConsistently();

private:
    Ui::MainWindowApp *ui;
    FacadeSystem *system;
    const QString emptyCommands = "Команды отсутствуют";

    //наименование имеющихся в системе команд
    const QString moveMovingUnitCommand = "moveMovingUnit";
    const QString activateExecutiveUnitCommand = "activateExecutiveUnit";
    const QString deactivateExecutiveUnitCommand = "deactivateExecutiveUnit";
    const QString analizeDetailAreaCommand = "analizeDetailArea";
    const QString setPressureSensorCommand = "setPressureSensor";
};
#endif // MAINWINDOWAPP_H
