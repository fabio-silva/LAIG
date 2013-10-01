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