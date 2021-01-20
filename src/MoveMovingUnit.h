#pragma once
#include "ProgramUnit.h"
#include "MovingUnit.h"

//Команда перемещения исполнительного органа в заданную позицию с определенной скоростью
class MoveMovingUnit : public ProgramUnit
{
private:
    //устройство перемещения робота
    MovingUnit *movingDevice;

    //параметры команды - целевая позиция (x,y,z)
    double x, y, z;

    //параметры команды - скорость перемещения
    double speed;

public:
    //конструктор команды
    //movingDevice - указатель на устройство перемещения робота
    //x, y, z - координаты конечной точки
    //speed - скорость перемещения
    MoveMovingUnit(MovingUnit *movingDevice, double x, double y, double z, double speed);


    //выполнение операции
    virtual string* doWork();

    //получить информацию о команде
    virtual string printCommand();
};
