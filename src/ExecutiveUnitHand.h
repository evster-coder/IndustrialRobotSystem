#pragma once
#include "ExecutiveUnit.h"

//Захват - исполнительный орган
class ExecutiveUnitHand : public ExecutiveUnit
{
private:
	//давление, с которым устройство держит деталь
	double holdPressure;

public:
	ExecutiveUnitHand();

	//Начать работу исполнительного органа с заданной интенсивностью
    virtual string* activeUnit(int intensivity);

	//Завершить работу исполнительного органа
	virtual bool deactiveUnit();

	//Установить ссылку на сенсорное устройство
	virtual void setSensor(ISensorUnit* sensorDevice);

    //возвращает наименование типа устройства
    virtual string getEUnitType();
};
