#include "SetPressureSensor.h"
#include <sstream>

using namespace std;

SetPressureSensor::SetPressureSensor(ISensorUnit* sensorDevice, double press)
{
	this->sensorDevice = sensorDevice;
	this->pressure = press;
}

string* SetPressureSensor::doWork()
{
    //результат выполнения функции в виде ответа
    //[0]: 1 - success, 0 - error
    //[1]: info about error
    string* executeResult = new string[2];

	if (sensorDevice)
	{
		//установление величины давления в систему от пользователя
		sensorDevice->setPressure(pressure);
        executeResult[0] = "1";
        return executeResult;
	}
	else
    {
        executeResult[0] = "0";
        executeResult[1] = "Sensor error";
        return executeResult;
    }
}

string SetPressureSensor::printCommand()
{
    string commandText = "setPressureSensor: " + to_string(pressure);
	return commandText;
}
