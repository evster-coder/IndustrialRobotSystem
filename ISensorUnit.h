#pragma once
#include "Detail.h"

//интерфейс сканирующего устройства
class ISensorUnit
{
public:

    virtual ~ISensorUnit(){}

	//Получить грузоподъемность робота
	virtual double getCapacity() = 0;

	//получить обрабатываемую деталь
	virtual Detail* getDetail() = 0;

	//получить величину освещения
	virtual double getLightly() = 0;

	//получить величину давления
	virtual double getPressure() = 0;

	//получить величину радиации
	virtual double getRadiation() = 0;

	//получить температуру
	virtual double getTemperature() = 0;

	//получить влажность
	virtual double getWet() = 0;


	//получение сведений о детали от сканеров
	virtual bool scanDetail() = 0;

	//получение сведений о окружающей среде от сканеров
	virtual bool scanConditions() = 0;


	//установить параметры обрабатываемой детали
	virtual void setDetail(Detail det) = 0;

	//установить заданную освещенность
	virtual  void setLightly(double light) = 0;

	//установить параметры давления на деталь
	virtual void setPressure(double press) = 0;

	//установить заданную радиацию
	virtual void setRadiation(double radiation) = 0;

	//установить заданную температуру
	virtual void setTemperature(double temperature) = 0;

	//установить заданную влажность
	virtual void setWet(double wet) = 0;

};
