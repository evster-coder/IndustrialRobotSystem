#include "DecoratorSensorUnit.h"

DecoratorSensorUnit::DecoratorSensorUnit(ISensorUnit* inItem)
{
	item = inItem;
}

DecoratorSensorUnit::~DecoratorSensorUnit()
{
	if (item)
		delete item;
}


double DecoratorSensorUnit::getCapacity()
{
	return item->getCapacity();
}

Detail* DecoratorSensorUnit::getDetail()
{
	return item->getDetail();
}

double DecoratorSensorUnit::getLightly()
{
	return item->getLightly();
}

double DecoratorSensorUnit::getPressure()
{
	return item->getPressure();
}

double DecoratorSensorUnit::getRadiation()
{
	return item->getRadiation();
}

double DecoratorSensorUnit::getTemperature()
{
	return item->getTemperature();
}

double DecoratorSensorUnit::getWet()
{
	return item->getWet();
}

bool DecoratorSensorUnit::scanDetail()
{
	return item->scanDetail();
}

void DecoratorSensorUnit::setDetail(Detail det)
{
	item->setDetail(det);
}

void DecoratorSensorUnit::setLightly(double light)
{
    item->setLightly(light);
}

void DecoratorSensorUnit::setPressure(double pressure)
{
	item->setPressure(pressure);
}

void DecoratorSensorUnit::setRadiation(double radiation)
{
	item->setRadiation(radiation);
}

void DecoratorSensorUnit::setTemperature(double temperature)
{
	item->setTemperature(temperature);
}

void DecoratorSensorUnit::setWet(double wet)
{
	item->setWet(wet);
}
