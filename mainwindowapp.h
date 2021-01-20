#ifndef MAINWINDOWAPP_H
#define MAINWINDOWAPP_H

#include <QMainWindow>

#include "dialogaddrobot.h"
#include "FacadeSystem.h"

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

private slots:
    //вызов окна внесения нового робота в систему
    void addNewRobotDialog();

private:
    Ui::MainWindowApp *ui;
    FacadeSystem *system;
};
#endif // MAINWINDOWAPP_H
