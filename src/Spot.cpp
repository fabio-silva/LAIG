#include "Spot.h"

Spot::Spot(vector<float> location, vector<float>ambient, vector<float>diffuse, vector<float>specular, vector<float> direction, char *id, bool enabled, float angle, float exponent):Light(location, ambient, diffuse,specular,id,enabled)
{
	this->angle = angle;
	this->direction = direction;
	this->exponent = exponent;
}



vector<float> Spot::getDirection()
{
	return direction;
}

float Spot::getAngle()
{
	return angle;
}

float Spot::getExponent()
{
	return exponent;
}