#pragma once

#include "DecoratorSensorUnit.h"

//конкретный декоратор
class DecSensorLight : public DecoratorSensorUnit
{
public:

	//вызов функции сканирования для класса + для item
	bool scanConditions();
	DecSensorLight(ISensorUnit* inItem) : DecoratorSensorUnit(inItem) {}
};