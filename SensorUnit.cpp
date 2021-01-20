#include "SensorUnit.h"
#include <cstdlib>
#include <ctime>

#include <sstream>
using namespace std;

SensorUnit::SensorUnit(double capacity)
{
	temperatureValue = wetValue = pressureValue = radiationValue = lightValue = 0;
	robotCapacity = capacity;
    setDetail(Detail(0, 0, 0, -1));

	srand(static_cast<unsigned int>(time(0)));
}

SensorUnit::~SensorUnit() {}

bool SensorUnit::scanDetail()
{
	//получение информации о детали; в отсутствии реальных сканеров - случайная генерация
    Detail det = Detail(1 + double(rand() % 1000), 1 + double(rand() % 1000),
		1 + double(rand() % 1000), 1 + double(rand() % 1000));	
    setDetail(det);

	//получение информации о необходимом давлении сжатия детали
	pressureValue = 100 + double(rand() % 10000);

	return true;
}

bool SensorUnit::scanConditions()
{
	return true;
}

Detail* SensorUnit::getDetail()
{
	return &currentDetail;
}

double SensorUnit::getLightly()
{
	return lightValue;
}

double SensorUnit::getRadiation()
{
	return radiationValue;
}

double SensorUnit::getTemperature()
{
	return temperatureValue;
}

double SensorUnit::getWet()
{
	return wetValue;
}

double SensorUnit::getPressure()
{
	return pressureValue;
}

double SensorUnit::getCapacity()
{
	return robotCapacity;
}

void SensorUnit::setDetail(Detail det)
{
	this->currentDetail = det;
}

void SensorUnit::setPressure(double press)
{
	pressureValue = press;
}

void SensorUnit::setLightly(double light)
{
	lightValue = light;
}

void SensorUnit::setRadiation(double radiation)
{
	radiationValue = radiation;
}

void SensorUnit::setTemperature(double temperature)
{
	this->temperatureValue = temperature;
}

void SensorUnit::setWet(double wet)
{
	this->wetValue = wet;
}
