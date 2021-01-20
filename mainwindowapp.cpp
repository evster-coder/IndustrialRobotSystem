#include "mainwindowapp.h"
#include "ui_mainwindowapp.h"

#include "QMessageBox"

MainWindowApp::MainWindowApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowApp)
{
    ui->setupUi(this);

    //создание и получение экземпляра фасада
    system = FacadeSystem::getInstance();

    refreshRobotsList();

    //соединяем слоты с элементами ui
    connect(ui->actionAddRobot, SIGNAL(triggered()), this, SLOT(addNewRobotDialog()));
    connect(ui->actionEraseRobot, SIGNAL(triggered()), this, SLOT(eraseRobotDialog()));
}

MainWindowApp::~MainWindowApp()
{
    delete ui;
}

void MainWindowApp::refreshRobotsList()
{
    //очистка списка
    ui->listViewAllRobots->clear();
    //получение списка имен
    ui->listViewAllRobots->addItems(system->getAllRobots());
}

void MainWindowApp::addNewRobotDialog()
{
    //добавление нового робота в систему
    DialogAddRobot *win = new DialogAddRobot(this);
    win->setModal(true);
    win->exec();
    delete win;

    //обновление списка роботов
    refreshRobotsList();
}

void MainWindowApp::eraseRobotDialog()
{
    //удаление робота из системы
    DialogDeleteRobot *win = new DialogDeleteRobot(this);
    win->setModal(true);
    win->exec();
    delete win;

    //обновление списка роботов
    refreshRobotsList();
}


