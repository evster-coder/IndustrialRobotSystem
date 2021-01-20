#include "RobotSystem.h"

using namespace std;

RobotSystem::RobotSystem(string serialNum, ExecutiveUnit* executiveU,
	double xSystemCoord, double ySystemCoord, double zSystemCoord, MovingUnit* movingU, ISensorUnit* sensorU)
{
	//инициализация реального объекта
	robot = new Robot(serialNum, executiveU, movingU, sensorU);

	this->xSystemCoord = xSystemCoord;
	this->ySystemCoord = ySystemCoord;
	this->zSystemCoord = zSystemCoord;
}

RobotSystem::~RobotSystem()
{
	delete robot;
}

void RobotSystem::addNewSensor(string sensor)
{
    robot->addNewSensor(sensor);
}

void RobotSystem::turnOn()
{
	robot->turnOn();
}

void RobotSystem::turnOff()
{
	robot->turnOff();
}


void RobotSystem::setServiceable(bool isWorkable)
{
	robot->setServiceable(isWorkable);
}

bool RobotSystem::getServiceable()
{
	return robot->getServiceable();
}


void RobotSystem::moveMovingUnit(double xTarget, double yTarget, double zTarget, double speed)
{
	//перевод системных координат в координаты робота
	xTarget -= xSystemCoord;
	yTarget -= ySystemCoord;
	zTarget -= zSystemCoord;

	//вызов функции устройства перемещения
	robot->moveMovingUnit(xTarget, yTarget, zTarget, speed);
}

void RobotSystem::activateExecutiveUnit(int intensivity)
{
	robot->activateExecutiveUnit(intensivity);
}

void RobotSystem::deactivateExecutiveUnit()
{
	robot->deactivateExecutiveUnit();
}

void RobotSystem::analizeDetailArea()
{
	robot->analizeDetailArea();
}

void RobotSystem::setPressureSensor(double press)
{
	robot->setPressureSensor(press);
}

bool RobotSystem::isCommandsEmpty()
{
	return robot->isCommandsEmpty();
}

string* RobotSystem::executeCommands()
{
	return robot->executeCommands();
}

string* RobotSystem::executeOneCommand()
{
	return robot->executeOneCommand();
}

string RobotSystem::getSerialNumber()
{
	return robot->getSerialNumber();
}

void RobotSystem::setSerialNumber(string newSerial)
{
	robot->setSerialNumber(newSerial);
}

vector<string>* RobotSystem::showCommands()
{
	return robot->showCommands();
}

bool RobotSystem::undoCommand(int index)
{
	return robot->undoCommand(index);
}
