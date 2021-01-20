#pragma once
#include "ProgramUnit.h"
#include "ExecutiveUnit.h"

//Команда запуска функции исполнительного органа
class ActivateExecutiveUnit : public ProgramUnit
{
private:
	//исполнительный орган робота
	ExecutiveUnit *executiveDevice;

	//параметр команды - интенсивность функции
	int intensivity;

public:
	//конструктор команды:
	//executiveDevice - указатель на исполнительный орган робота
	//intensivity - параметр интенсивности
	ActivateExecutiveUnit(ExecutiveUnit* executiveDevice, int intensivity);

	//выполнение операции
    virtual string* doWork();

	//получить информацию о команде
	virtual string printCommand();
};
