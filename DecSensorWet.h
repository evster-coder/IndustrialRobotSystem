#pragma once

#include "DecoratorSensorUnit.h"

//конкретный декоратор
class DecSensorWet : public DecoratorSensorUnit
{
public:
	//вызов функции сканирования для класса + для item
	bool scanConditions();

	DecSensorWet(ISensorUnit* inItem) : DecoratorSensorUnit(inItem) {}
};