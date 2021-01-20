#pragma once

#include "DecoratorSensorUnit.h"

//конкретный декоратор
class DecSensorTemperature : public DecoratorSensorUnit
{
public:

	//вызов функции сканирования для класса + для item
	bool scanConditions();
	DecSensorTemperature(ISensorUnit* inItem) : DecoratorSensorUnit(inItem) {}
};