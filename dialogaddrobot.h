#ifndef DIALOGADDROBOT_H
#define DIALOGADDROBOT_H

#include <QDialog>
#include <QMessageBox>
#include "src/FacadeSystem.h"

namespace Ui {
class DialogAddRobot;
}

class DialogAddRobot : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddRobot(QWidget *parent = nullptr);
    ~DialogAddRobot();

private slots:
    //Добавить робота
    void addRobot();

    //закрыть окно
    void closeWindow();

private:
    Ui::DialogAddRobot *ui;
};

#endif // DIALOGADDROBOT_H
