#include "ExecutiveUnitHand.h"
#include <iostream>

ExecutiveUnitHand::ExecutiveUnitHand()
{
	sensor = nullptr;
	intensivity = 0;
	holdPressure = 0;
	isActive = false;
}


void ExecutiveUnitHand::setSensor(ISensorUnit* sensorDevice)
{
	sensor = sensorDevice;
}

string* ExecutiveUnitHand::activeUnit(int intensivity)
{
    //результат выполнения функции в виде ответа
    //[0]: 1 - success, 0 - error
    //[1]: info about error
    string* executeResult = new string[2];

	//формируем корректное значение для интенсивности исполнительного органа
    if (intensivity <= 0)
        this->intensivity = 1;
    else
        if (intensivity > 100)
            this->intensivity = 100;
        else
            this->intensivity = intensivity;

    //Если сенсор был определён
    //то активируем захват
    if (sensor)
    {
        //Получение массы детали
        Detail* curDetail = sensor->getDetail();
        double mass = curDetail->getMass();

        if(mass < 0)
        {
            executeResult[0] = "0";
            executeResult[1] = "Start ScanSensorUnit to set Detail params";
            return executeResult;
        }

        if (mass > sensor->getCapacity())
        {
            executeResult[0] = "0";
            executeResult[1] = "Detail is too heavy";
            return executeResult;
        }

        //Получение необходимого давления
        double pressure = sensor->getPressure();
        if (pressure == 0)
        {
            executeResult[0] = "0";
            executeResult[1] = "Pressure not set";
            return executeResult;
        }
        else
            holdPressure = pressure * (intensivity / 100);

        //Активация захвата
        isActive = true;
        executeResult[0] = "1";
        return executeResult;
    }
    else
    {
        //иначе прерываем операцию
        executeResult[0] = "0";
        executeResult[1] = "Sensor not set";
        return executeResult;
    }
}

bool ExecutiveUnitHand::deactiveUnit()
{
	//Сброс давления
	holdPressure = 0;

	//Отпуск детали
	intensivity = 0;
	isActive = false;
	return true;
}

string ExecutiveUnitHand::getEUnitType()
{
    return "Executive Unit Hand";
}
