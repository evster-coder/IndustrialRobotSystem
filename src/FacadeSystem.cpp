#include "FacadeSystem.h"

#include <iostream>
using namespace std;

//для линкера
FacadeSystem* FacadeSystem::instance = nullptr;

FacadeSystem::FacadeSystem()
{
	factory = nullptr;
}

FacadeSystem::~FacadeSystem()
{
	delete factory;
}

FacadeSystem* FacadeSystem::getInstance()
{
	//если объект еще не был создан, то создаем новый и возвращаем его
	//иначе возвращаем уже созданный
	if (instance == nullptr)
		instance = new FacadeSystem();
	return instance;
}

ExecutiveUnit* FacadeSystem::getExecutiveUnitHand()
{
	factory = new EUnitHandCreator();
	return factory->createUnit();
}

ExecutiveUnit* FacadeSystem::getExecutiveUnitSpray()
{
	factory = new EUnitSprayCreator();
	return factory->createUnit();
}

IRobot* FacadeSystem::pushRobot(string serialNumb, ExecutiveUnit* executiveDevice, ISensorUnit* sensorDevice,
	double xSystemCoord, double ySystemCoord, double zSystemCoord, double xRange, double yRange, double zRange)
{

	//создание робота с указанными параметрами и добавление его в систему
	IRobot* newComponent = new RobotSystem(serialNumb, executiveDevice, xSystemCoord, ySystemCoord, zSystemCoord, 
		new MovingUnit(xRange, yRange, zRange), sensorDevice);

	string printText;
	if (systemObj.addRobot(newComponent) == true)
	{
        printText = "Robot " + serialNumb + " was added successfully";
        Logger::printText(printText);
        return newComponent;
	}
	else
	{
		printText = "Robot " + serialNumb + " wasn't added to system";
        Logger::printText(printText);
        return nullptr;
	}
}

bool FacadeSystem::pushRobot(IRobot* newRobot)
{
	string printText;
	if (systemObj.addRobot(newRobot) == true)
	{
		printText = "Robot " + newRobot->getSerialNumber() + " was added successfully";
        Logger::printText(printText);
        return true;
	}
	else
	{
		printText = "Robot " + newRobot->getSerialNumber() + " wasn't added to system";
        Logger::printText(printText);
		return false;
	}
}

bool FacadeSystem::eraseRobot(string serialNumb)
{
    string printText = "Robot " + serialNumb + " was erased";
    Logger::printText(printText);
    return systemObj.eraseRobot(serialNumb);
}

QStringList FacadeSystem::performAllConsistently()
{
    QStringList outInfo;

    //выполнение всех команд роботов системы последовательно
    string* systemResult = systemObj.executeOnebyone();
    if(systemResult == nullptr)
	{
        outInfo.push_back("All operations performed in series completed successfully");
	}
	else
	{
        outInfo.push_back("Failed to complete all operations in series");
        outInfo.push_back("Errors on:");
        outInfo.push_back("Robot num. " + QString::fromStdString(systemResult[0])
                + ": message: " + QString::fromStdString(systemResult[1]));
	}

    return outInfo;
}

QStringList FacadeSystem::performAllOneToAnother()
{
    QStringList outInfo;

    //выполнение всех команд роботов одна зи одной между роботами
    string* systemResult = systemObj.executeOneToAnother();
    if(systemResult == nullptr)
    {
        outInfo.push_back("All operations performed one to another completed successfully");
    }
    else
    {
        outInfo.push_back("Failed to complete all operations one to another");
        outInfo.push_back("Errors on:");
        outInfo.push_back("Robot num. " + QString::fromStdString(systemResult[0])
                + ": message: " + QString::fromStdString(systemResult[1]));
    }

    return outInfo;
}

QStringList FacadeSystem::performAllParallel()
{
    QStringList outInfo;

    //выполнение всех команд роботов параллельно
    vector<string*> commandsOutput = systemObj.executeParallel();
    if (int(commandsOutput.size()) == 0)
	{
        outInfo.push_back("All operations performed parallel completed successfully");
	}
	else
	{
        outInfo.push_back("Failed to complete all operations parallel");
        outInfo.push_back("Errors on:");
        for(int i = 0; i < int(commandsOutput.size()); i++)
        {
            outInfo.push_back("Robot num. " + QString::fromStdString(commandsOutput[i][0])
                    + ": message: " + QString::fromStdString(commandsOutput[i][1]));
        }
	}

    return outInfo;
}

IRobot* FacadeSystem::getRobot(string serialNumb)
{

	IRobot* returnRobot = systemObj.getRobot(serialNumb);
	return returnRobot;
}

void FacadeSystem::printSystemInfo()
{
	//печать информации о роботах в системе
    Logger::printText("\n");
    Logger::printText("##################");
    Logger::printText("System consist of:");

	//получаем всех роботов
	map<string, IRobot*> robots = systemObj.getRobotMap();

	//печать номеров всех роботов и наличия у них команд
	for (auto curRobot = robots.begin(); curRobot != robots.end(); ++curRobot)
	{
        Logger::printText("Robot num. " + curRobot->second->getSerialNumber());

		vector<string>* mass = curRobot->second->showCommands();
		if (mass == nullptr)
            Logger::printText("Robot have no command");
		else
		{
			for (int i = 0; i < int(mass->size()); i++)
                Logger::printText(mass->at(i));
		}

	}
    Logger::printText("\n");
    Logger::printText("##################");
    Logger::printText("\n");
}

QStringList FacadeSystem::getAllRobots()
{
    QStringList robotNames;
    //получаем всех роботов
    map<string, IRobot*> robots = systemObj.getRobotMap();

    //получаем их серийные номера
    for(auto curRobot = robots.begin(); curRobot != robots.end(); ++curRobot)
        robotNames.push_back(QString::fromStdString(curRobot->first));
    return robotNames;
}
