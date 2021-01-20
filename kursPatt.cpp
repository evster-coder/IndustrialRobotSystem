#include <iostream>
#include "IRobot.h"
#include "RobotSystem.h"
#include "ControlSystem.h"
#include "FacadeSystem.h"

#include "Logger.h"
#include "FileLogger.h"

#include "DecSensorLight.h"
#include "DecSensorRadiation.h"
#include "DecSensorWet.h"
#include "DecSensorTemperature.h"



void commandTest()
{
    //Создание системы
    FacadeSystem* sys = FacadeSystem::getInstance();

    //добавление роботов в систему
    IRobot* r1 = sys->pushRobot("1488", sys->getExecutiveUnitHand(), new DecSensorTemperature(new SensorUnit(250)),
        0, 0, 0, 22, 80, 70);
    r1->moveMovingUnit(10, 10, 10, 200);

    IRobot* r2 = sys->pushRobot("1489", sys->getExecutiveUnitSpray(), new SensorUnit(350),
        23.0, 22.0, 22.0, 72.0, 80.0, 70.0);
    r2->activateExecutiveUnit(54);
    r2->moveMovingUnit(24, 27, 7, 100);
    r2->deactivateExecutiveUnit();

    //печать информации о системе
    sys->printSystemInfo();

    r1->turnOn();
    r2->turnOn();

    sys->performAllParallel();

    sys->printSystemInfo();
}

int main()
{
    Logger::setImplementation(new FileLogger("logs.txt"));

    commandTest();

}