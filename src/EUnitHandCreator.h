#pragma once
#include "EUnitCreator.h"
#include "ExecutiveUnitHand.h"

//реализует фабричный метод создания спрея-исполнительного органа
class EUnitHandCreator : public EUnitCreator {
public:
	//фабричный метод создания захвата-органа
	ExecutiveUnit* createUnit() override;
};