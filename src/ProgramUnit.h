#pragma once
#include <string>

using namespace std;

//интерфейс команды
class ProgramUnit
{
public:

    virtual ~ProgramUnit(){}
	//выполнить операцию
    virtual string* doWork() = 0;

	//получить информацию о команде
	virtual string printCommand() = 0;
};
