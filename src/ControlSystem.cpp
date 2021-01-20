#include "ControlSystem.h"
using namespace std;
#include <iostream>
#include <QCoreApplication>
#include "QFuture"
#include "QList"
#include "QtConcurrent/QtConcurrent"

map<string, IRobot*> ControlSystem::getRobotMap()
{
	return robots;
}

/*Добавление робота в систему*/
bool ControlSystem::addRobot(IRobot* newRobot)
{
	//Пытаемся занести нового робота в массив роботов
	if (robots.find(newRobot->getSerialNumber()) == robots.end())
	{
		robots.insert(make_pair(newRobot->getSerialNumber(), newRobot));
		return true;
	}
	else
	{
		return false;
	}
}

/*Удаление робота по заданному серийному номеру*/
bool ControlSystem::eraseRobot(string index)
{
	//Проверка на корректность индекса
	if (robots.find(index) != robots.end())
	{
		robots.erase(index);
		return true;
	}
	else
		return false;
}

/*Получение робота(группы) по заданному серийному номеру*/
IRobot* ControlSystem::getRobot(string index)
{
	//Проверка на корректность индекса
	if (robots.find(index) != robots.end())
		return robots[index];
	else
		return nullptr;
}

string* ControlSystem::executeRobotCommands(string robotNumber)
{
    return robots.find(robotNumber)->second->executeCommands();
}

string* ControlSystem::executeRobotOneCommand(string robotNumber)
{
    return robots.find(robotNumber)->second->executeOneCommand();
}

vector<string*> ControlSystem::executeParallel()
{
    //список наименований роботов
    string *robotNumbers = new string[int(robots.size())];
    int indexRobots = 0;

    //Проход по каждому роботу и выполнение каждым всех имеющихся команд
    QFutureSynchronizer<string*> future;
    for (auto curRobot = robots.begin(); curRobot != robots.end(); ++curRobot)
    {
        future.addFuture(QtConcurrent::run(this, &ControlSystem::executeRobotCommands, curRobot->first));
        robotNumbers[indexRobots++] = curRobot->first;
    }

    //ожидание выполнения всех потоков
    future.waitForFinished();

    //получение результата
    vector<string*> result;
    string* curCommandResult;
    QList<QFuture<string*>> futures = future.futures();
    for(int i = 0; i < futures.length(); i++)
    {
        curCommandResult = futures[i].result();
        if(curCommandResult[0] == "0")
        {
            curCommandResult[0] = robotNumbers[i];
            result.push_back(curCommandResult);
        }
    }
    future.clearFutures();

    return result;
}

string* ControlSystem::executeOneToAnother()
{
	//Флаг окончания выполнения команд
	bool flagIsFinish = false;

    //организация выполнения команды в другом потоке
    QFuture<string*> future;

	//Пока не все команды выполнены
	while (flagIsFinish == false)
	{
		flagIsFinish = true;

		//Проход по каждому роботу и выполнение им одной команды
		for (auto curRobot = robots.begin(); curRobot != robots.end(); ++curRobot)
		{
			if (curRobot->second->isCommandsEmpty() == false)
			{
				flagIsFinish = false;
                future = QtConcurrent::run(this, &ControlSystem::executeRobotOneCommand, curRobot->first);
                future.waitForFinished();
                if(future.result()[0] == "0")
                {
                    string* commandRequest = future.result();
                    commandRequest[0] = curRobot->first;
                    return commandRequest;
                }
            }
		}
	}
    return nullptr;
}

/*Выполнение команд последовательно*/
string* ControlSystem::executeOnebyone()
{

    QFuture<string*> future;
	//Проход по каждому роботу и выполнение каждым всех имеющихся команд
	for (auto curRobot = robots.begin(); curRobot != robots.end(); ++curRobot)
    {
        future = QtConcurrent::run(this, &ControlSystem::executeRobotCommands, curRobot->first);
        future.waitForFinished();

        if(future.result()[0] == "0")
        {
            string* commandRequest = future.result();
            commandRequest[0] = curRobot->first;
            return commandRequest;
        }

    }
    return nullptr;
}
