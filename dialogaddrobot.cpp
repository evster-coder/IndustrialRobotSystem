#include "dialogaddrobot.h"
#include "ui_dialogaddrobot.h"

DialogAddRobot::DialogAddRobot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddRobot)
{
    ui->setupUi(this);
    QRegExp expDouble ("^(0|([1-9][0-9]*))(\\.[0-9]+)?$");
    ui->lineRobotCapacity->setValidator(new QRegExpValidator(expDouble, this));

    //постоянный размер окна
    this->setFixedSize(this->size());

    //установка имеющихся рабочих органов в combo box
    ui->comboBoxExecutiveUnit->addItem("Захват");
    ui->comboBoxExecutiveUnit->addItem("Разбрызгиватель");

    //соединяем слоты с элементами ui
    connect(ui->buttonAdd, SIGNAL(clicked()), this, SLOT(addRobot()));
    connect(ui->buttonClose, SIGNAL(clicked()), this, SLOT(closeWindow()));

}

DialogAddRobot::~DialogAddRobot()
{
    delete ui;
}


void DialogAddRobot::closeWindow()
{
    this->close();
}

void DialogAddRobot::addRobot()
{
    //проверка введенных данных
    if(ui->comboBoxExecutiveUnit->currentIndex() > 1)
    {
        QMessageBox::warning(this, "Предупреждение", "Неверно выбран рабочий орган");
        return;
    }

    if(ui->lineSerialNumber->text().length() < 3)
    {
        QMessageBox::warning(this, "Предупреждение", "Серийный номер слишком короткий");
        return;
    }

    if(FacadeSystem::getInstance()->getRobot(ui->lineSerialNumber->text().toStdString()) != nullptr)
    {
        QMessageBox::warning(this, "Предупреждение", "Робот с таким серийным номером уже присутствует в системе");
        return;
    }

    if(ui->lineRobotCapacity->text().toDouble() < 0)
    {
        QMessageBox::warning(this, "Предупреждение", "Отрицательная грузоподъемность недопустима");
        return;
    }

    //создание рабочего органа робота
    ExecutiveUnit* item;
    switch(ui->comboBoxExecutiveUnit->currentIndex())
    {
    case 0:
        item = FacadeSystem::getInstance()->getExecutiveUnitHand();
        break;
    case 1:
        item = FacadeSystem::getInstance()->getExecutiveUnitSpray();
        break;
    default:
        item = FacadeSystem::getInstance()->getExecutiveUnitHand();
        break;
    }

    //создание робота в системе
    IRobot* robot = FacadeSystem::getInstance()
          ->pushRobot(ui->lineSerialNumber->text().toStdString(),
                     item, new SensorUnit(ui->lineRobotCapacity->text().toDouble()),
                     ui->doubleSpinBoxPosX->value(), ui->doubleSpinBoxPosY->value(), ui->doubleSpinBoxPosZ->value(),
                     ui->doubleSpinBoxRangeX->value(), ui->doubleSpinBoxRangeY->value(), ui->doubleSpinBoxRangeZ->value()
                     );

    //установка дополнительных сенсоров
    if(ui->checkBoxWet->isChecked())
        robot->addNewSensor("Wet");
    if(ui->checkBoxLight->isChecked())
        robot->addNewSensor("Light");
    if(ui->checkBoxRadiation->isChecked())
        robot->addNewSensor("Radiation");
    if(ui->checkBoxTemperature->isChecked())
        robot->addNewSensor("Temperature");

    //закрытие окна
    this->close();
}

