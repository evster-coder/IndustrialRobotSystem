#pragma once
#include <string>

using namespace std;

//Устройство передвижения робота
class MovingUnit 
{
private:
	//диапазон перемещения устройства
	double xMoveRange, yMoveRange, zMoveRange;

	//находится ли устройство в движении
	bool isMove;

	//текущее положение головки исполнительного органа
	double positionX, positionY, positionZ;

public:
	//конструктор устройства передвижения
	//XRange, yRange, zRange - границы перемещения устройства
	MovingUnit(double xRange, double yRange, double zRange);
    MovingUnit();

	//переместить устройство в позицию
	//(x; y; z) мм со скоростью speed мм/сек
    string* moveDevice(double x, double y, double z, double speed);

    double getPositionX();
    double getPositionY();
    double getPositionZ();

    double getXMoveRange();
    double getYMoveRange();
    double getZMoveRange();

};
