#include "MoveMovingUnit.h"

using namespace std;

MoveMovingUnit::MoveMovingUnit(MovingUnit *movingDevice, double x, double y, double z, double speed)
{
	this->movingDevice = movingDevice;
	this->x = x;
	this->y = y;
	this->z = z;
	this->speed = speed;
}

string* MoveMovingUnit::doWork()
{
    //результат выполнения функции в виде ответа
    //[0]: 1 - success, 0 - error
    //[1]: info about error

    //переместить устройство в заданную точку
	return movingDevice->moveDevice(x, y, z, speed);
}


string MoveMovingUnit::printCommand()
{
    string commandText = "moveMovingUnit to " + to_string(x) + "; " + to_string(y) + "; " + to_string(z) +
        " speed " + to_string(speed);
	return commandText;
}
