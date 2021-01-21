#include "ScanSensorUnit.h"

using namespace std;

ScanSensorUnit::ScanSensorUnit(ISensorUnit* sensorDevice)
{
	this->sensorDevice = sensorDevice;
}

string* ScanSensorUnit::doWork()
{
    //результат выполнения функции в виде ответа
    //[0]: 1 - success, 0 - error
    //[1]: info about error
    string* executeResult = new string[2];

    //получение сведений об окружающей среде и детали от сенсоров
	bool result = sensorDevice->scanConditions();
	result = result && sensorDevice->scanDetail();
    if(result == true)
        executeResult[0] = "1";
    else
    {
        executeResult[0] = "0";
        executeResult[1] = "Sensor Error";
    }

    return executeResult;
}

string ScanSensorUnit::printCommand()
{
    string commandText = "analizeDetailArea";
	return commandText;
}
