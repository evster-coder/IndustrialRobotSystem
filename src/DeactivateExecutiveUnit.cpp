#include "DeactivateExecutiveUnit.h"
#include <sstream>

using namespace std;

DeactivateExecutiveUnit::DeactivateExecutiveUnit(ExecutiveUnit* executiveDevice)
{
	this->executiveDevice = executiveDevice;
}

string* DeactivateExecutiveUnit::doWork()
{
	//остановить функцию исполнительного органа
    //результат выполнения функции в виде ответа
    //[0]: 1 - success, 0 - error
    //[1]: info about error
    string* executeResult = new string[2];
    if(executiveDevice->deactiveUnit())
    {
        executeResult[0] = "1";
    }
    else
    {
        executeResult[0] = "0";
        executeResult[1] = "Error Deactivate executive unit";
    }
    return executeResult;
}

string DeactivateExecutiveUnit::printCommand()
{
    string commandText = "deactivateExecutiveUnit";
	return commandText;
}
