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

bool RobotSystem::isRobotOn()
{
    return robot->isRobotOn();
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

vector<string> RobotSystem::getRobotInfo()
{
    vector<string> info = robot->getRobotInfo();

    double *pos = robot->getCurrentPos();
    std::ostringstream streamObjPX;
    streamObjPX << std::fixed;
    streamObjPX << std::setprecision(3);
    streamObjPX << pos[0];

    std::ostringstream streamObjPY;
    streamObjPY << std::fixed;
    streamObjPY << std::setprecision(3);
    streamObjPY << pos[1];

    std::ostringstream streamObjPZ;
    streamObjPZ << std::fixed;
    streamObjPZ << std::setprecision(3);
    streamObjPZ << pos[2];

    info.push_back("Local position ExecutiveUnit: "
                   + streamObjPX.str() + "; "
                   + streamObjPY.str() + "; "
                   + streamObjPZ.str());

    //форматирование double
    std::ostringstream streamObjX;
    streamObjX << std::fixed;
    streamObjX << std::setprecision(3);
    streamObjX << xSystemCoord;

    std::ostringstream streamObjY;
    streamObjY << std::fixed;
    streamObjY << std::setprecision(3);
    streamObjY << ySystemCoord;

    std::ostringstream streamObjZ;
    streamObjZ << std::fixed;
    streamObjZ << std::setprecision(3);
    streamObjZ << zSystemCoord;

    //добавление позиции робота
    info.push_back("Position: "
                   + streamObjX.str() + "; "
                   + streamObjY.str() + "; "
                   + streamObjZ.str());
    return info;
}
