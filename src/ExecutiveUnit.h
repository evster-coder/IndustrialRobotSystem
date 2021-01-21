#pragma once
#include "SensorUnit.h"
#include <string>

using namespace std;

//Абстрактный исполнительный орган робота
class ExecutiveUnit
{
protected:
	//интенсивность работы устройства
	int intensivity;

	//включена / выключена функция органа
	bool isActive;

	//сенсорное устройство
	ISensorUnit* sensor;
public:

    virtual ~ExecutiveUnit(){}

	//Начать работу исполнительного органа с заданной интенсивностью
    virtual string* activeUnit(int intensivity) = 0;

	//Завершить работу исполнительного органа
	virtual bool deactiveUnit() = 0;

	//Установить ссылку на сенсорное устройство
	virtual void setSensor(ISensorUnit* sensorDevice) = 0;

    //возвращает наименование типа устройства
    virtual string getEUnitType() = 0;
};
