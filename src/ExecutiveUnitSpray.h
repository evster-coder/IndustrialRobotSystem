#pragma once
#include "ExecutiveUnit.h"

class ExecutiveUnitSpray : public ExecutiveUnit
{
public:
	ExecutiveUnitSpray();

	//Начать работу исполнительного органа с заданной интенсивностью
    virtual string* activeUnit(int intensivity);

	//Завершить работу исполнительного органа
	virtual bool deactiveUnit();

	//Установить ссылку на сенсорное устройство
	virtual void setSensor(ISensorUnit* sensorDevice);

    //возвращает наименование типа устройства
    virtual string getEUnitType();
};
