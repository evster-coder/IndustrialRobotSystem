#pragma once
#include "ISensorUnit.h"


//Сенсорное устройство робота
class SensorUnit : public ISensorUnit
{
private:
	//обрабатываемая роботом деталь
	Detail currentDetail;

	//освещение рабочего места
	double lightValue;

	//величина радиации
	double radiationValue;

	//температура окружающей среды
	double temperatureValue;

	//влажность окружающей среды
	double wetValue;

	//Давление на деталь
	double pressureValue;

	//Грузоподъемность робота
	double robotCapacity;

public:
	SensorUnit(double capacity);
	~SensorUnit();

	//получение сведений о детали от сканеров
	bool scanDetail();

	//получение сведений о окружающей среде от сканеров
	bool scanConditions();


	//установить заданную температуру
	void setTemperature(double temperature);

	//установить заданную влажность
	void setWet(double wet);

	//установить значение освещенности
	void setLightly(double light);

	//установить значение радиации
	void setRadiation(double radiation);

	//установить параметры обрабатываемой детали
	void setDetail(Detail det);

	//установить параметры давления на деталь
	void setPressure(double press);


	//получить температуру
	double getTemperature();

	//получить влажность
	double getWet();

	//получить освещенность
	double getLightly();

	//получить радиацию
	double getRadiation();

	//получить обрабатываемую деталь
	Detail* getDetail();

	//получить величину давления
	double getPressure();

	//Получить грузоподъемность робота
	double getCapacity();
};