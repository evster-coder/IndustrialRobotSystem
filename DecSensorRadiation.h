#pragma once

#include "DecoratorSensorUnit.h"

//конкретный декоратор
class DecSensorRadiation : public DecoratorSensorUnit
{
public:

	//вызов функции сканирования для класса + для item
	bool scanConditions();
	DecSensorRadiation(ISensorUnit* inItem) : DecoratorSensorUnit(inItem) {}
};