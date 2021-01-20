#include "DecSensorRadiation.h"

bool DecSensorRadiation::scanConditions()
{
	item->setRadiation(double(rand() % 10));
	return item->scanConditions();
}
