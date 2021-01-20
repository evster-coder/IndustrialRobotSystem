#pragma once
#include "IRobot.h"
#include <map>

using namespace std;

//Система управления роботами
class ControlSystem
{
private:
	//Ассоциативный массив из всех роботов в системе
	//Ключ - серийный номер робота
	//Значение - робот
	map<string, IRobot*> robots;

public:
	//Добавление робота newRobot в вектор Роботов
	bool addRobot(IRobot* newRobot);

	//Удаление робота с номером index из вектора Роботов
	bool eraseRobot(string index);

	//Получение робота с номером index из вектора Роботов
	IRobot* getRobot(string index);

    //Выполнение команды одним роботом, затем другим, пока команды не кончатся
    string* executeOneToAnother();

	//Выполнение команд роботов последовательно
    string* executeOnebyone();

    //Выполнение команд роботов параллельно
    vector<string*> executeParallel();

	//возвращает весь массив роботов для фасада
	map<string, IRobot*> getRobotMap();

private:
    //выполнить все команды для робота с заданным номером
    string* executeRobotCommands(string robotNumber);

    //выполнить одну команду для робота с заданным номером
    string* executeRobotOneCommand(string robotNumber);
};
