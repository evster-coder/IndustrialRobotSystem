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

    //соединяем слоты с элементами ui
    connect(ui->actionAddRobot, SIGNAL(triggered()), this, SLOT(addNewRobotDialog()));
}

MainWindowApp::~MainWindowApp()
{

    delete ui;
}

void MainWindowApp::addNewRobotDialog()
{
    DialogAddRobot *win = new DialogAddRobot(this);
    win->setModal(true);
    win->show();
}

