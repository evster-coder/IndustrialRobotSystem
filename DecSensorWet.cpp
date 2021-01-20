#include "DecSensorWet.h"
using namespace std;


bool DecSensorWet::scanConditions()
{
	item->setWet(double(rand() % 100));
	return item->scanConditions();
}
