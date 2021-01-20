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
	string printText;
	if (systemObj.eraseRobot(serialNumb) == true)
	{
		printText = "Robot " + serialNumb + " was successfuly erased from system";
		cout << printText << endl;
		return true;
	}
	else
	{
		printText = "Robot " + serialNumb + " wasn't erased from system";
		cout << printText << endl;
		return false;
	}
}

void FacadeSystem::performAllConsistently()
{
    string* systemResult = systemObj.executeOnebyone();
    if(systemResult == nullptr)
	{
		cout << "All operations performed in series completed successfully" << endl;
	}
	else
	{
		cout << "Failed to complete all operations in series" << endl;
        cout << "Errors on:" << endl;
        cout << "Robot num. " << systemResult[0] << ": message: " << systemResult[1] << endl;
	}
}

void FacadeSystem::performAllOneToAnother()
{
    string* systemResult = systemObj.executeOneToAnother();
    if(systemResult == nullptr)
    {
        cout << "All operations performed one to another completed successfully" << endl;
    }
    else
    {
        cout << "Failed to complete all operations one to another" << endl;
        cout << "Errors on:" << endl;
        cout << "Robot num. " << systemResult[0] << ": message: " << systemResult[1] << endl;
    }
}

void FacadeSystem::performAllParallel()
{
    vector<string*> commandsOutput = systemObj.executeParallel();
    if (int(commandsOutput.size()) == 0)
	{
		cout << "All operations performed parallel completed successfully" << endl;
	}
	else
	{
		cout << "Failed to complete all operations parallel" << endl;
        cout << "Errors on:" << endl;
        for(int i = 0; i < int(commandsOutput.size()); i++)
        {
            cout << "Robot num. " << commandsOutput[i][0] << ": message: " << commandsOutput[i][1] << endl;
        }
	}
}

IRobot* FacadeSystem::getRobot(string serialNumb)
{
	string printText;

	IRobot* returnRobot = systemObj.getRobot(serialNumb);
	if (returnRobot != nullptr)
	{
		printText = "Robot " + serialNumb + " was successfuly transfered to user";
		cout << printText << endl;
	}
	else
	{
		printText = "Robot " + serialNumb + " wasn't found";
		cout << printText << endl;
	}
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
