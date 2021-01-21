#pragma once

#include "IRobot.h"
#include "Robot.h"
#include "MovingUnit.h"

class RobotSystem : public IRobot
{
private:
	//Указатель на реальный объект робота
    Robot* robot;
	
	//Координаты робота в системе
	double xSystemCoord, ySystemCoord, zSystemCoord;

public:
	//Конструктор робота
	//serialNum - серийный номер; 
	//capacity - грузоподъемость
	//executiveU - исполнительный орган
	//XSystemCoord, ySystemCoord, zSystemCoord - координаты робота в системе
	//movingU - объект - легковес устройства перемещения
	//SensorU - сканирующее устройство
	RobotSystem(string serialNum, ExecutiveUnit* executiveU, 
		double xSystemCoord, double ySystemCoord, double zSystemCoord, MovingUnit* movingU, ISensorUnit* sensorU);
	
	~RobotSystem();

    //добавление нового сенсора роботу
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
