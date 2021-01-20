#include "MovingUnit.h"
#include <cmath>
#include <windows.h>
#include <iostream>
#include "QThread"

using namespace std;

#define minTime 0.1			//шаг изменения времени в движении


MovingUnit::MovingUnit(double xRange, double yRange, double zRange)
{
	xMoveRange = xRange;
	yMoveRange = yRange;
	zMoveRange = zRange;
	positionX = 0;
	positionY = 0;
	positionZ = 0;

	isMove = false;
}

string* MovingUnit::moveDevice(double x, double y, double z, double speed)
{
    //результат выполнения функции в виде ответа
    //[0]: 1 - success, 0 - error
    //[1]: info about error
    string* executeResult = new string[2];
    executeResult[0] = "1";

	//Корректирование конечной точки в соответствии
	//с диапазоном устройства перемещения
	if (x > xMoveRange)
    {
		x = xMoveRange;
        executeResult[0] = "0";
    }
	if (y > yMoveRange)
    {
		y = yMoveRange;
        executeResult[0] = "0";
    }
	if (z > zMoveRange)
    {
		z = zMoveRange;
        executeResult[0] = "0";
    }


	if (x < -xMoveRange)
    {
		x = -xMoveRange;
        executeResult[0] = "0";
    }
	if (y < -yMoveRange)
    {
		y = -yMoveRange;
        executeResult[0] = "0";
    }
	if (z < -zMoveRange)
    {
		z = -zMoveRange;
        executeResult[0] = "0";
    }

    if(executeResult[0] == "0")
    {
        executeResult[1] = "Destination point is out of range";
    }

	//начинается движение
	isMove = true;

	//длина вектора перемещения
	double len = sqrt((positionX - x) * (positionX - x) + (positionY - y) * (positionY - y) +
		(positionZ - z) * (positionZ - z));

	//определение времени перемещения в точку
	double time;
	if (speed > 0)
        time = len / speed;
	else
		time = 0;

	if (time > 0)
	{
		//Смещение по каждой из осей за 100 мс
		double moveX = (x - positionX) / (time * 10);
		double moveY = (y - positionY) / (time * 10);
		double moveZ = (z - positionZ) / (time * 10);


		double currTime = 0;
		//пока не закончен промежуток времени перемещения
		while (time > currTime)
		{
			//Если оставшееся время меньше 100 мс
			if (time - currTime < minTime)
			{
				//то устанавливаем конечные координаты
				positionX = x;
				positionY = y;
				positionZ = z;
				break;
			}
			currTime += 0.1;

			//увеличиваем смещение по каждой из осей
			positionX += moveX;
			positionY += moveY;
			positionZ += moveZ;

            QThread::msleep(100);
        }

		//присваиваем конечные координаты точки
		positionX = x;
		positionY = y;
		positionZ = z;

	}

	//заканчивается движение
    isMove = false;


    return executeResult;
}
