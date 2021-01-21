#include "ActivateExecutiveUnit.h"
#include <sstream>

using namespace std;

ActivateExecutiveUnit::ActivateExecutiveUnit(ExecutiveUnit *executiveDevice, int intensivity)
{
	this->executiveDevice = executiveDevice;
	this->intensivity = intensivity;
}

string* ActivateExecutiveUnit::doWork()
{
    //результат выполнения функции в виде ответа
    //[0]: 1 - success, 0 - error
    //[1]: info about error

    //запустить функцию исполнительного органа
	return executiveDevice->activeUnit(intensivity);
}

string ActivateExecutiveUnit::printCommand()
{
    string commandText = "activateExecutiveUnit intense: " + to_string(intensivity);
	return commandText;
}
