#include "Spot.h"

Spot::Spot(vector<float> location, vector<float>ambient, vector<float>diffuse, vector<float>specular, vector<float> direction, char *id, bool enabled, float angle, float exponent)
{
	this->location = location;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular= specular;
	this->id = id;
	this->enabled = enabled;
	this->angle = angle;
	this->direction = direction;
	this->exponent = exponent;
	
}

vector<float> Spot::getLocation()
{
	return location;
}

vector<float> Spot::getAmbient()
{
	return ambient;
}

vector<float> Spot::getDiffuse()
{
	return diffuse;
}

vector<float> Spot::getSpecular()
{
	return specular;
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

bool Spot::isEnabled()
{
	return enabled;
}

char* Spot::getId()
{
	return id;
}