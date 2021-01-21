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
		cout <<  printText << endl;
		return newComponent;
	}
	else
	{
		printText = "Robot " + serialNumb + " wasn't added to system";
		cout << printText << endl;
		return nullptr;
	}
}

bool FacadeSystem::pushRobot(IRobot* newRobot)
{
	string printText;
	if (systemObj.addRobot(newRobot) == true)
	{
		printText = "Robot " + newRobot->getSerialNumber() + " was added successfully";
		cout << printText << endl;
		return true;
	}
	else
	{
		printText = "Robot " + newRobot->getSerialNumber() + " wasn't added to system";
		cout << printText << endl;
		return false;
	}
}

bool FacadeSystem::eraseRobot(string serialNumb)
{
    return systemObj.eraseRobot(serialNumb);
}

QStringList FacadeSystem::performAllConsistently()
{
    QStringList outInfo;
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
	cout << endl;
	cout << "##################" << endl;
	cout << "System consist of:" << endl;

	//получаем всех роботов
	map<string, IRobot*> robots = systemObj.getRobotMap();

	//печать номеров всех роботов и наличия у них команд
	for (auto curRobot = robots.begin(); curRobot != robots.end(); ++curRobot)
	{
		cout << "Robot num. " << curRobot->second->getSerialNumber() << endl;

		vector<string>* mass = curRobot->second->showCommands();
		if (mass == nullptr)
			cout << "Robot have no command" << endl;
		else
		{
			for (int i = 0; i < int(mass->size()); i++)
				cout << mass->at(i) << endl;
		}

	}
	cout << endl;
	cout << "##################" << endl;
	cout << endl;
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
