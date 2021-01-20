#include "Robot.h"
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
