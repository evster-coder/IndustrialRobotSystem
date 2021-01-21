#include "Robot.h"
#include "DecSensorLight.h"
#include "DecSensorRadiation.h"
#include "DecSensorTemperature.h"
#include "DecSensorWet.h"

#include <vector>

using namespace std;

Robot::Robot(string serialNumb, ExecutiveUnit* executiveU, MovingUnit *movingU, ISensorUnit* sensorDevice)
{
	this->serialNumber = serialNumb;
	this->executiveDevice = executiveU;

	this->isServiceable = true;
	this->isOn = false;
	this->movingDevice = movingU;
	this->sensorDevice = sensorDevice;

	this->executiveDevice->setSensor(sensorDevice);
}

Robot::~Robot()
{
	delete movingDevice;
	delete executiveDevice;
	delete sensorDevice;
	for (int i = 0; i < int(commands.size()); i++)
		delete commands[i];
}

void Robot::addNewSensor(string sensor)
{
    ISensorUnit* sensorC = sensorDevice;
    if (sensor == "Light")
        sensorC = new DecSensorLight(sensorDevice);
    else if (sensor == "Wet")
        sensorC = new DecSensorWet(sensorDevice);
    else if (sensor == "Radiation")
        sensorC = new DecSensorRadiation(sensorDevice);
    else if (sensor == "Temperature")
        sensorC = new DecSensorTemperature(sensorDevice);
    sensorDevice = sensorC;
}

void Robot::turnOn()
{
	//включение робота
	if (isOn == false)
	{
		isOn = true;
	}
}

void Robot::turnOff()
{
	//отключение робота
	if (isOn == true)
	{
		isOn = false;
	}
}

bool Robot::isRobotOn()
{
    return isOn;
}


void Robot::setServiceable(bool isWorkable)
{
	isServiceable = isWorkable;
}

bool Robot::getServiceable()
{
	return isServiceable;
}


string* Robot::executeCommands()
{
    //ответ на запрос на выполнение функции
    //[0]: 1 - success, 0 - error
    //[1]: error info
    string* commandRequest = new string[2];
    commandRequest[0] = "1";

    //если робот включен и исправен
    if (isOn == true && isServiceable == true)
    {
        //выполняем все команды робота
        while (commands.size() > 0)
        {
            commandRequest = executeOneCommand();

            if (commandRequest[0] == "0")
                break;
        }
    }
    return commandRequest;
}

string* Robot::executeOneCommand()
{   
    //ответ на запрос на выполнение функции
    //[0]: 1 - success, 0 - error
    //[1]: error info
    string* commandRequest = new string[2];
    commandRequest[0] = "1";

    //Если робот включен и исправен
    if (isOn == true && isServiceable == true)
    {
        //и ещё есть доступные команды
        if (commands.size() > 0)
        {
            string* commandRequest = commands[0]->doWork();
            //выполняем одну команду, при неудаче завершаем работу
            if (commandRequest[0] == "0")
                return commandRequest;

            //и удаляем эту команду из списка
            commands.erase(commands.begin());
            return commandRequest;
        }
        else
            isOn = false;
    }
    return commandRequest;
}


bool Robot::isCommandsEmpty()
{
	if (commands.size() == 0)
		return true;
	else
		return false;
}

void Robot::moveMovingUnit(double x, double y, double z, double speed)
{
	//создание команды перемещения
	ProgramUnit* command = new MoveMovingUnit(movingDevice, x, y, z, speed);

	//добавление её в список
	commands.push_back(command);
}

void Robot::activateExecutiveUnit(int intensivity)
{
	//создание команды активации исп. органа
	ProgramUnit* command = new ActivateExecutiveUnit(executiveDevice, intensivity);

	//добавление её в список
	commands.push_back(command);
}

void Robot::deactivateExecutiveUnit()
{
	//создание команды деактивации исп. органа
	ProgramUnit* command = new DeactivateExecutiveUnit(executiveDevice);

	//добавление её в список
	commands.push_back(command);
}

void Robot::analizeDetailArea()
{
	//создание команды сканирования информации о среде и детали
	ProgramUnit* command = new ScanSensorUnit(sensorDevice);

	//добавление её в список
	commands.push_back(command);
}

void Robot::setPressureSensor(double press)
{
	//создание команды установки значения давления сжатия
	ProgramUnit* command = new SetPressureSensor(sensorDevice, press);

	//добавление её в список
	commands.push_back(command);
}

string Robot::getSerialNumber()
{
	return serialNumber;
}

void Robot::setSerialNumber(string newSerial)
{
	serialNumber = newSerial;
}

vector<string>* Robot::showCommands()
{

	//если команды отсутствуют - возвращаем пустой массив
	if ((int)commands.size() < 1)
		return nullptr;

	//иначе массив описаний команд
	vector<string>* commandsShow = new vector<string>;
	for (int i = 0; i < (int)commands.size(); i++)
		commandsShow->push_back(commands[i]->printCommand());
	return commandsShow;
}

bool Robot::undoCommand(int index)
{
	if ((int)commands.size() > index)
		commands.erase(commands.begin() + index);
	else
		return false;
	return true;
}

vector<string> Robot::getRobotInfo()
{
    vector<string> info;
    //форматирование double
    std::ostringstream streamObjX;
    streamObjX << std::fixed;
    streamObjX << std::setprecision(3);
    streamObjX << movingDevice->getXMoveRange();

    std::ostringstream streamObjY;
    streamObjY << std::fixed;
    streamObjY << std::setprecision(3);
    streamObjY << movingDevice->getYMoveRange();

    std::ostringstream streamObjZ;
    streamObjZ << std::fixed;
    streamObjZ << std::setprecision(3);
    streamObjZ << movingDevice->getZMoveRange();

    info.push_back("Serial Number: " + getSerialNumber());
    info.push_back("Is Robot on: " + string((isOn ? "true" : "false")));
    info.push_back("Serviceable status: "+ string((isServiceable ? "true" : "false")));
    info.push_back("Robot capacity: " + to_string(sensorDevice->getCapacity()));
    info.push_back("Executive unit type: " + executiveDevice->getEUnitType());
    info.push_back("Ex. unit move Range:" + streamObjX.str() + "; "
                                          + streamObjY.str() + "; "
                                          + streamObjZ.str() );
    return info;
}

double* Robot::getCurrentPos()
{
    //x y и z текущий координаты робота
    double* position = new double[3];
    position[0] = movingDevice->getPositionX();
    position[1] = movingDevice->getPositionY();
    position[2] = movingDevice->getPositionZ();
    return position;
}
