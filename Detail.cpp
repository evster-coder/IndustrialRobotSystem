#include "Detail.h"

Detail::Detail()
{
	width = height = depth = mass = 0;
}

Detail::Detail(double w, double h, double d, double m)
{
	this->width = w;
	this->height = h;
	this->depth = d;
	this->mass = m;
}

double Detail::getWidth()
{
	return width;
}

double Detail::getHeight()
{
	return height;
}

double Detail::getDepth()
{
	return depth;
}

double Detail::getMass()
{
	return mass;
}
