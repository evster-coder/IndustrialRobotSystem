#pragma once
#include "ProgramUnit.h"
#include "ISensorUnit.h"

//Команда получения сведений роботом от сенсора
class ScanSensorUnit: public ProgramUnit
{
private:
	//сенсорное устройство
	ISensorUnit* sensorDevice;
public:

	//конструктор команды
	//sensorDevice - указатель на сенсорное устройство робота
	ScanSensorUnit(ISensorUnit* sensorDevice);

	//выполнение операции
    virtual string* doWork();

	//получить информацию о команде
	virtual string printCommand();
};
