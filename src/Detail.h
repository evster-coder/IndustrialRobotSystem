#pragma once

//Обрабатываемая роботом деталь
class Detail
{
private:
	//ширина, высота, глубина детали
	double width, height, depth;
	
	//масса детали
	double mass;
public:
	Detail();

	Detail(double w, double h, double d, double m);

	//Получение ширины детали
	double getWidth();

	//Получение высоты детали
	double getHeight();

	//Получение глубины детали
	double getDepth();

	//Получение массы детали
	double getMass();
};