#pragma once
#include "ExecutiveUnit.h"

//абстрактный класс, содержащий фабричный метод
class EUnitCreator{
public:
    virtual ~EUnitCreator(){}

    //создание рабочего органа
	virtual ExecutiveUnit* createUnit() = 0;
};
