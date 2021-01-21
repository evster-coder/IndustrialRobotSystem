#include "ExecutiveUnitSpray.h"

ExecutiveUnitSpray::ExecutiveUnitSpray()
{
	sensor = nullptr;
	intensivity = 0;
	isActive = false;
}

string* ExecutiveUnitSpray::activeUnit(int intensivity)
{
    //результат выполнения фунцкии в виде ответа
    //[0]: 1 - success, 0 - error
    //[1]: info about error
    string* executeResult = new string[2];

	//формируем корректное значение дл¤ интенсивности исполнительного органа
	if (intensivity <= 0)
		this->intensivity = 1;
	else
		if (intensivity > 100)
			this->intensivity = 100;
		else
			this->intensivity = intensivity;

	//если сенсор был определЄн
	//то активируем устройство
	if (sensor)
	{
        //активация разбрызгивател¤
		isActive = true;

        executeResult[0] = "1";
        return executeResult;
	}
	else
		//иначе прерываем выполнение команды
        executeResult[0] = "0";
        executeResult[1] = "Sensor not set";
        return executeResult;
}

bool ExecutiveUnitSpray::deactiveUnit()
{
	//ќтпуск нажати¤ разбрызгивател¤
	intensivity = 0;
	isActive = false;
	return true;
}

void ExecutiveUnitSpray::setSensor(ISensorUnit* sensorDevice)
{
	sensor = sensorDevice;
}

string ExecutiveUnitSpray::getEUnitType()
{
    return "Executive Unit Spray";
}
