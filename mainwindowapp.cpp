#include "mainwindowapp.h"
#include "ui_mainwindowapp.h"



MainWindowApp::MainWindowApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowApp)
{
    ui->setupUi(this);

    //создание и получение экземпляра фасада
    system = FacadeSystem::getInstance();

    Logger::setImplementation(new QListWidgetLogger(ui->listWidgetResult));

    refreshRobotsList();

    //соединяем слоты с элементами ui
    connect(ui->actionAddRobot, SIGNAL(triggered()), this, SLOT(addNewRobotDialog()));
    connect(ui->actionEraseRobot, SIGNAL(triggered()), this, SLOT(eraseRobotDialog()));
    connect(ui->listViewAllRobots, SIGNAL(itemSelectionChanged()), this, SLOT(showRobotInfo()), Qt::QueuedConnection);
    connect(ui->buttonTurnOn, SIGNAL(clicked()), this, SLOT(turnRobotOn()));
    connect(ui->buttonTurnOff, SIGNAL(clicked()), this, SLOT(turnRobotOff()));
    connect(ui->buttonEraseCommand, SIGNAL(clicked()), this, SLOT(eraseCommand()));
    connect(ui->buttonAddCommand, SIGNAL(clicked()), this, SLOT(addNewCommand()));

    connect(ui->buttonMakeCommandsOnetoanother, SIGNAL(clicked()), this, SLOT(makeCommandsOneToAnother()));
    connect(ui->buttonMakeCommandsConsistently, SIGNAL(clicked()), this, SLOT(makeCommandsConsistently()));
    connect(ui->buttonMakeCommandsParallel, SIGNAL(clicked()), this, SLOT(makeCommandsParallel()));
}

MainWindowApp::~MainWindowApp()
{
    delete ui;
}


void MainWindowApp::makeCommandsOneToAnother()
{
    QMessageBox::information(this, "Система", "Началась обработка команд одна за одной");

    QEventLoop loop;
    QFutureWatcher<QStringList> watcher;
    connect(&watcher, &QFutureWatcher<QStringList>::finished,  &loop, &QEventLoop::quit);

    QFuture<QStringList> future = QtConcurrent::run(system, &FacadeSystem::performAllOneToAnother);
    watcher.setFuture(future);

    turnOffButtons();

    //выполнение цикла
    loop.exec();
    //получение результата
    auto resultOut = watcher.result();

    QMessageBox::information(this, "Система", "Обработка завершена");

    turnOnButtons();

    ui->listWidgetResult->addItems(resultOut);

}

void MainWindowApp::makeCommandsConsistently()
{
    QMessageBox::information(this, "Система", "Началась обработка команд последовательно");

    QEventLoop loop;
    QFutureWatcher<QStringList> watcher;
    connect(&watcher, &QFutureWatcher<QStringList>::finished,  &loop, &QEventLoop::quit);

    QFuture<QStringList> future = QtConcurrent::run(system, &FacadeSystem::performAllConsistently);
    watcher.setFuture(future);

    turnOffButtons();

    //выполнение цикла
    loop.exec();
    //получение результата
    auto resultOut = watcher.result();

    QMessageBox::information(this, "Система", "Обработка завершена");

    turnOnButtons();

    ui->listWidgetResult->addItems(resultOut);

}

void MainWindowApp::makeCommandsParallel()
{
    QMessageBox::information(this, "Система", "Началась обработка команд параллельно");

    QEventLoop loop;
    QFutureWatcher<QStringList> watcher;
    connect(&watcher, &QFutureWatcher<QStringList>::finished,  &loop, &QEventLoop::quit);

    QFuture<QStringList> future = QtConcurrent::run(system, &FacadeSystem::performAllParallel);
    watcher.setFuture(future);

    turnOffButtons();

    //выполнение цикла
    loop.exec();
    //получение результата
    auto resultOut = watcher.result();

    QMessageBox::information(this, "Система", "Обработка завершена");

    turnOnButtons();

    ui->listWidgetResult->addItems(resultOut);
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

        showRobotInfo();
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

        showRobotInfo();
    }
}

void MainWindowApp::addNewCommand()
{
    if(ui->listViewAllRobots->currentItem() == nullptr)
        return;

    //получение робота из системы
    IRobot *selectedRobot = system->getRobot(ui->listViewAllRobots->currentItem()->text().toStdString());
    if(selectedRobot == nullptr)
        return;

    if(ui->lineEditNewCommand->text() != "")
    {
        QString commandText = ui->lineEditNewCommand->text();

        //формирование регулярных выражений
        int pos = 0;
        QRegExp expAct  ("^" + activateExecutiveUnitCommand );
        QRegExp expDeact("^" + deactivateExecutiveUnitCommand);
        QRegExp expMove ("^" + moveMovingUnitCommand);
        QRegExp expAnali("^" + analizeDetailAreaCommand);
        QRegExp expSetp ("^" + setPressureSensorCommand);

        //совпадает команде активации рабочего органа
        if ((pos = expAct.indexIn(commandText)) != -1)
        {
            commandText.remove(0, activateExecutiveUnitCommand.length() + 1);
            QRegExp expInt ("^[0-9]+");

            if(expInt.exactMatch(commandText))
                selectedRobot->activateExecutiveUnit(commandText.toInt());
            else
                QMessageBox::warning(this, "Ошибка формата", "Неверный формат " + activateExecutiveUnitCommand);
        }

        //совпадает команде деактивации рабочего органа
        else if ((pos = expDeact.indexIn(commandText)) != -1)
        {
            if(commandText == deactivateExecutiveUnitCommand)
                selectedRobot->deactivateExecutiveUnit();
            else
                QMessageBox::warning(this, "Ошибка формата", "Неверный формат " + deactivateExecutiveUnitCommand);
        }

        //совпадает команде перемещения рабочего органа
        else if ((pos = expMove.indexIn(commandText)) != -1)
        {
            //удаляем название команды и оставляем параметры
            commandText.remove(0, moveMovingUnitCommand.length() + 1);

            //параметры функции-  числа double
            QStringList mass = commandText.split(QRegExp("\\s"));
            QRegExp expDouble ("^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$");
            if(mass.length() == 4
                    && expDouble.exactMatch(mass[0])
                    && expDouble.exactMatch(mass[1])
                    && expDouble.exactMatch(mass[2])
                    && expDouble.exactMatch(mass[3]))
            {
                    selectedRobot->moveMovingUnit(mass[0].toDouble(),
                            mass[1].toDouble(),
                            mass[2].toDouble(),
                            mass[3].toDouble());
            }
            else
                QMessageBox::warning(this, "Ошибка формата", "Неверный формат " + moveMovingUnitCommand);
        }

        //совпадает команде работы сенсоров
        else if ((pos = expAnali.indexIn(commandText)) != -1)
        {
            if(commandText == analizeDetailAreaCommand)
                selectedRobot->analizeDetailArea();
            else
                QMessageBox::warning(this, "Ошибка формата", "Неверный формат " + analizeDetailAreaCommand);
        }

        //совпадает команде установки давления захвата
        else if ((pos = expSetp.indexIn(commandText)) != -1)
        {
            //удаляем назнвание команды и оставляем параметры
            commandText.remove(0, setPressureSensorCommand.length() + 1);

            //вычленяем параметры
            QRegExp expDouble ("^(0|([1-9][0-9]*))(\\.[0-9]+)?$");

            if(expDouble.exactMatch(commandText))
                selectedRobot->setPressureSensor(commandText.toDouble());
            else
                QMessageBox::warning(this, "Ошибка формата", "Неверный формат " + setPressureSensorCommand);
        }
        else
        {
            QString availableCommands = "Доступные команды: \n" + activateExecutiveUnitCommand + "<intensivity>\n"
                    + deactivateExecutiveUnitCommand + "\n"
                    + moveMovingUnitCommand + " <x> <y> <z> <speed>\n"
                    + analizeDetailAreaCommand + "\n"
                    + setPressureSensorCommand + " <pressure>\n";
            QMessageBox::warning(this, "Ошибка синтаксиса", "Команда " + commandText + " не опознана. \n" + availableCommands);
        }

        showRobotInfo();
    }
    else
        QMessageBox::warning(this, "Информация о команде", "Поле ввода пустое");
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


void MainWindowApp::turnOffButtons()
{
    ui->buttonTurnOn->setEnabled(false);
    ui->buttonTurnOff->setEnabled(false);
    ui->buttonAddCommand->setEnabled(false);
    ui->buttonEraseCommand->setEnabled(false);
    ui->buttonMakeCommandsParallel->setEnabled(false);
    ui->buttonMakeCommandsConsistently->setEnabled(false);
    ui->buttonMakeCommandsOnetoanother->setEnabled(false);
}

void MainWindowApp::turnOnButtons()
{
    ui->buttonTurnOn->setEnabled(true);
    ui->buttonTurnOff->setEnabled(true);
    ui->buttonAddCommand->setEnabled(true);
    ui->buttonEraseCommand->setEnabled(true);
    ui->buttonMakeCommandsParallel->setEnabled(true);
    ui->buttonMakeCommandsConsistently->setEnabled(true);
    ui->buttonMakeCommandsOnetoanother->setEnabled(true);
}

