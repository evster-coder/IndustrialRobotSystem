#pragma once

#include "ProgramUnit.h"
#include "MoveMovingUnit.h"
#include "ActivateExecutiveUnit.h"
#include "DeactivateExecutiveUnit.h"
#include "ScanSensorUnit.h"
#include "SetPressureSensor.h"

#include "ExecutiveUnit.h"
#include "ISensorUnit.h"
#include "IRobot.h"

#include <string>
#include <vector>

using namespace std;

//Промышленный робот - realSubject
class Robot : public IRobot
{
private:
	//Серийный номер робота
	string serialNumber;
	
	//Исправность
	bool isServiceable;

	//Включен / отключен
	bool isOn;

	//Устройство передвижения исполнительного органа
	MovingUnit *movingDevice;

	//Исполнительное устройство
	ExecutiveUnit* executiveDevice;

	//Сенсорное устройство
	ISensorUnit* sensorDevice;

	//Вектор из команд робота
	vector<ProgramUnit*> commands;

public:
	//Конструктор робота
	//serialNum - серийный номер; 
	//capacity - грузоподъемость
	//executiveU - исполнительный орган
	//movingU - объект - легковес устройства перемещения
	//sensorDevice - сенсорный орган робота
	Robot(string serialNumb, ExecutiveUnit* executiveU, MovingUnit* movingU, ISensorUnit* sensorDevice);

    ~Robot();

    //добавление нового сенсора
    virtual void addNewSensor(string sensor);

	//Включение робота
	virtual void turnOn();

	//Отключение робота
	virtual void turnOff();

    //включен ли робот
    virtual bool isRobotOn();

	//получение серийного номера (идентификатора робота)
	virtual string getSerialNumber();

	//смена серийного номера
	virtual void setSerialNumber(string newSerial);

	//Установить исправность робота
	virtual void setServiceable(bool isWorkable);

	//Получение исправности робота
	virtual bool getServiceable();

    //получение координат робота
    double* getCurrentPos();


	//Передвинуть исполнительный орган робота в позицию
	//(x; y; z) мм со скоростью speed мм / сек
	virtual void moveMovingUnit(double x, double y, double z, double speed);

	//Активировать исполнительный орган робота
	//со значением интенсивности intensivity
	virtual void activateExecutiveUnit(int intensivity);

	//Деактивировать исполнительный орган робота
	virtual void deactivateExecutiveUnit();

	//Проанализировать деталь и окружающую среду сенсорами робота
	virtual void analizeDetailArea();

	//Установить значение для давления исп.органа на деталь
	virtual void setPressureSensor(double press);


	//Узнать пуст ли список команд робота
	virtual bool isCommandsEmpty();


	//Выполнить все команды робота
    virtual string* executeCommands();

	//Выполнить одну команду робота
    virtual string* executeOneCommand();

	//печать информации о командах
	virtual vector<string>* showCommands();

	//удаление комманды по индексу
	virtual bool undoCommand(int index);

    //выдача информации о роботе
    virtual vector<string> getRobotInfo();

};
