#include "dialogdeleterobot.h"
#include "ui_dialogdeleterobot.h"

DialogDeleteRobot::DialogDeleteRobot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDeleteRobot)
{
    ui->setupUi(this);

    ui->ComboboxRobots->addItems(FacadeSystem::getInstance()->getAllRobots());

    //соединяем слоты с элементами ui
    connect(ui->buttonErase, SIGNAL(clicked()), this, SLOT(eraseRobot()));
    connect(ui->buttonCancel, SIGNAL(clicked()), this, SLOT(closeWindow()));

}

DialogDeleteRobot::~DialogDeleteRobot()
{
    delete ui;
}

void DialogDeleteRobot::closeWindow()
{
    this->close();
}

void DialogDeleteRobot::eraseRobot()
{
    //удаление робота по его серийному номеру
    if(ui->ComboboxRobots->currentIndex() != -1)
    {
        if(FacadeSystem::getInstance()->eraseRobot(ui->ComboboxRobots->currentText().toStdString()) == false)
            QMessageBox::warning(this, "Удаление" , "Удаление не удалось, робот не найден");
        else
            QMessageBox::information(this, "Удаление" , "Робот успешно удален из системы");
        this->close();
    }
}
