#include "dialogaddrobot.h"
#include "ui_dialogaddrobot.h"

DialogAddRobot::DialogAddRobot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddRobot)
{
    ui->setupUi(this);

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
    //занесение робота в систему
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

    IRobot* robot = FacadeSystem::getInstance()
            ->pushRobot(ui->lineSerialNumber->text().toStdString(),
                        item, new SensorUnit(ui->lineRobotCapacity->text().toDouble()),
                        ui->doubleSpinBoxPosX->value(), ui->doubleSpinBoxPosY->value(), ui->doubleSpinBoxPosZ->value(),
                        ui->doubleSpinBoxRangeX->value(), ui->doubleSpinBoxRangeY->value(), ui->doubleSpinBoxRangeZ->value()
                        );
    //закрытие окна
    this->close();
}

