#ifndef DIALOGDELETEROBOT_H
#define DIALOGDELETEROBOT_H

#include <QDialog>
#include <QMessageBox>

#include "src/FacadeSystem.h"

namespace Ui {
class DialogDeleteRobot;
}

class DialogDeleteRobot : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDeleteRobot(QWidget *parent = nullptr);
    ~DialogDeleteRobot();

private slots:
    //Удалить робота
    void eraseRobot();

    //закрыть окно
    void closeWindow();

private:
    Ui::DialogDeleteRobot *ui;
};

#endif // DIALOGDELETEROBOT_H
