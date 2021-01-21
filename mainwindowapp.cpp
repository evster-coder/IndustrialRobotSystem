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
    connect(ui->listViewAllRobots, SIGNAL(itemSelectionChanged()), this, SLOT(showRobotInfo()), Qt::QueuedConnection);
    connect(ui->buttonTurnOn, SIGNAL(clicked()), this, SLOT(turnRobotOn()));
    connect(ui->buttonTurnOff, SIGNAL(clicked()), this, SLOT(turnRobotOff()));
    connect(ui->buttonEraseCommand, SIGNAL(clicked()), this, SLOT(eraseCommand));
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

void MainWindowApp::showRobotInfo()
{
    ui->textRobotStat->clear();
    ui->commandsList->clear();
    //если что-то выбрано
    if(ui->listViewAllRobots->currentItem())
    {
        //получаем робота с выделенным номером
        IRobot* curSelect = system->getRobot(ui->listViewAllRobots->currentItem()->text().toStdString());

        //печать информации о роботе
        vector<string> info = curSelect->getRobotInfo();
        QString outputText = "";
        for(int i = 0; i < int(info.size()); i++)
            outputText += QString::fromStdString(info[i]) + "\n";
        ui->textRobotStat->setText(outputText);

        //печать списка команд робота
        vector<string> *commands = curSelect->showCommands();
        if(commands != nullptr)
        {
            int amountCommand = commands->size();
            for(int i = 0; i < amountCommand; i++)
            {
                ui->commandsList->addItem(QString::fromStdString(commands->at(i)));
            }
        }
        else
            ui->commandsList->addItem(emptyCommands);
    }
}

void MainWindowApp::turnRobotOn()
{
    if(ui->listViewAllRobots->currentItem())
    {
        //получаем робота
        IRobot* curRobot = system->getRobot(ui->listViewAllRobots->currentItem()->text().toStdString());
        if(curRobot == nullptr)
            return;

        //включаем его
        curRobot->turnOn();
        QMessageBox::information(this, "Информация о роботе", "Робот успешно включен");
        ui->listViewAllRobots->clearSelection();
    }
}

void MainWindowApp::turnRobotOff()
{
    if(ui->listViewAllRobots->currentItem())
    {
        //получаем робота
        IRobot* curRobot = system->getRobot(ui->listViewAllRobots->currentItem()->text().toStdString());
        if(curRobot == nullptr)
            return;

        //выключаем его
        curRobot->turnOff();
        QMessageBox::information(this, "Информация о роботе", "Робот успешно отключен");
        ui->listViewAllRobots->clearSelection();
    }
}

void MainWindowApp::eraseCommand()
{
    //если в списке команд есть команды и единственная запись - не о пустоте команд
    if(ui->commandsList->count() > 0 && ui->commandsList->item(0)->text() != emptyCommands)
    {
        if(ui->commandsList->currentItem() == nullptr)
        {
            QMessageBox::warning(this, "Предупреждение", "Ни одна из команд не была выделена");
            return;
        }

        if(ui->listViewAllRobots->currentItem() == nullptr)
            return;

        //удаление выбранной команды
        IRobot* selectedRobot = system->getRobot(ui->listViewAllRobots->currentItem()->text().toStdString());
        if(selectedRobot)
        {
            if(selectedRobot->undoCommand(ui->commandsList->currentRow()))
                QMessageBox::information(this, "Информация о команде", "Команда успешно удалена");
            else
                QMessageBox::warning(this, "Информация о команде", "Ошибка удаления команды");

            showRobotInfo();
        }
    }
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


