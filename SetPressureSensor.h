#pragma once
#include "ProgramUnit.h"
#include "ISensorUnit.h"

//Команда установки давления пользователем
class SetPressureSensor : public ProgramUnit
{
private:

	//сенсорное устройство
	ISensorUnit* sensorDevice;

	//параметр - давление сжатия
	double pressure;
public:

	//конструктор команды
	//sensorDevice - указатель на сенсорное устройство робота
	//press - параметр давления
	SetPressureSensor(ISensorUnit* sensorDevice, double press);

	//выполнение операции
    virtual string* doWork();

	//получить информацию о команде
	virtual string printCommand();
};
