#pragma once
#include "EUnitCreator.h"
#include "ExecutiveUnitSpray.h"

//реализует фабричный метод создания спрея-исполнительного органа
class EUnitSprayCreator : public EUnitCreator {
public:
	//фабричный метод создания пульверизатора-органа
	ExecutiveUnit* createUnit() override;
};