#pragma once
#include <QStringList>
#include "ControlSystem.h"
#include "ExecutiveUnit.h"
#include "Logger.h"
#include "RobotSystem.h"
#include "EUnitCreator.h"
#include "EUnitHandCreator.h"
#include "EUnitSprayCreator.h"


//фасад для системы управления роботами
class FacadeSystem {
private:
	//объект, обращающийся непосредственно к роботам
	ControlSystem systemObj;

	//фабричный метод создания исполнительного органа
	EUnitCreator* factory;

	//единственный статический объект
	static FacadeSystem* instance;

	//приватные конструктор  и деструктор
	FacadeSystem();

	~FacadeSystem();

public:
	//получение объекта
	static FacadeSystem* getInstance();

	//создание органа-захвата
	ExecutiveUnit* getExecutiveUnitHand();

	//создание органа-пульверизатора
	ExecutiveUnit* getExecutiveUnitSpray();

	//добавление робота по его параметрам
	IRobot* pushRobot(string serialNumb, ExecutiveUnit* executiveDevice, ISensorUnit* sensorDevice, 
		double xSystemCoord, double ySystemCoord, double zSystemCoord, double xRange, double yRange, double zRange);

	//добавление готового робота
	bool pushRobot(IRobot* newRobot);

	//удаление робота по его серийному номеру
	bool eraseRobot(string serialNumb);

	//выполнение работы системы последовательно
    QStringList performAllConsistently();

    //выполнение работы системы шаг за шагом
    QStringList performAllOneToAnother();

	//выполнение работы системы параллельно
    QStringList performAllParallel();

	//получение робота по его серийному номеру
	IRobot* getRobot(string serialNumb);

	//печать информации о системе
	void printSystemInfo();

    //получение имен всех роботов системы
    QStringList getAllRobots();

};
