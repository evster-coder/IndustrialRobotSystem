#include "DecSensorTemperature.h"


bool DecSensorTemperature::scanConditions()
{
	item->setTemperature(double(rand() % 100) - 50);
	return item->scanConditions();
}
