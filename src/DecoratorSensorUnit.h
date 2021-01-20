#pragma once

#include "ISensorUnit.h"
#include <iostream>

class DecoratorSensorUnit : public ISensorUnit
{
protected:
	//декорируемый объект
	ISensorUnit* item;

public:
	DecoratorSensorUnit(ISensorUnit* itItem);
	~DecoratorSensorUnit();

	//Получить грузоподъемность робота
	double getCapacity();

	//получить обрабатываемую деталь
	Detail* getDetail();

	//получить величину освещения
	double getLightly();

	//получить величину давления
	double getPressure();

	//получить величину радиации
	double getRadiation();

	//получить температуру
	double getTemperature();

	//получить влажность
	double getWet();


	//получение сведений о детали от сканеров
	bool scanDetail();

	//получение сведений о окружающей среде от сканеров
	virtual bool scanConditions() = 0;


	//установить параметры обрабатываемой детали
	void setDetail(Detail det);

	//установить заданную освещенность
	void setLightly(double light);

	//установить параметры давления на деталь
	void setPressure(double press);

	//установить заданную радиацию
	void setRadiation(double radiation);

	//установить заданную температуру
	void setTemperature(double temperature);

	//установить заданную влажность
	void setWet(double wet);

};