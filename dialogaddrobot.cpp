#include "dialogaddrobot.h"
#include "ui_dialogaddrobot.h"

DialogAddRobot::DialogAddRobot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddRobot)
{
    ui->setupUi(this);
}

DialogAddRobot::~DialogAddRobot()
{
    delete ui;
}
