#pragma once
#include "ProgramUnit.h"
#include "ExecutiveUnit.h"

// оманда остановки функции исполнительного органа
class DeactivateExecutiveUnit : public ProgramUnit
{
private:
	//исполнительный орган робота
	ExecutiveUnit* executiveDevice;

public:
	//конструктор команды:
	//executiveDevice - указатель на исполнительный орган робота
	DeactivateExecutiveUnit(ExecutiveUnit* executiveDevice);
	
	//выполнение операции
    virtual string* doWork();

	//получить информацию о команде
	virtual string printCommand();
};
