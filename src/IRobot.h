#pragma once
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

//Интерфейс робота (для класса-прокси)
class IRobot
{
public:
    virtual ~IRobot(){}

	//Включение робота
	virtual void turnOn() = 0;

	//Отключение робота
	virtual void turnOff() = 0;

    virtual bool isRobotOn() = 0;

	//получение серийного номера (идентификатора робота)
	virtual string getSerialNumber() = 0;


	//смена серийного номера
	virtual void setSerialNumber(string newSerial) = 0;

	//Установить исправность робота
	virtual void setServiceable(bool isWorkable) = 0;

	//Получение исправности робота
	virtual bool getServiceable() = 0;

    //добавление нового сенсора
    virtual void addNewSensor(string sensor) = 0;


	//Передвинуть исполнительный орган робота в позицию
	//(x; y; z) мм со скоростью speed мм / сек
	virtual void moveMovingUnit(double x, double y, double z, double speed) = 0;

	//Активировать исполнительный орган робота
	//со значением интенсивности intensivity
	virtual void activateExecutiveUnit(int intensivity) = 0;

	//Деактивировать исполнительный орган робота
	virtual void deactivateExecutiveUnit() = 0;
	
	//Проанализировать деталь и окружающую среду сенсорами робота
	virtual void analizeDetailArea() = 0;

	//Установить значение для давления исп.органа на деталь
	virtual void setPressureSensor(double press) = 0;

	//Узнать пуст ли список команд робота
	virtual bool isCommandsEmpty() = 0;
	
	//Выполнить все команды робота
    virtual string* executeCommands() = 0;
	
	//Выполнить одну команду робота
    virtual string* executeOneCommand() = 0;

	//печать всех команд робота
	virtual vector<string>* showCommands() = 0;

	//удаление команды по индексу
	virtual bool undoCommand(int index) = 0;

    //выдача информации о роботе
    virtual vector<string> getRobotInfo() = 0;

};
