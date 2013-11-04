#include "Light.h"

Light::Light(vector<float> location, vector<float> ambient, vector<float> diffuse, vector<float> specular, char *id, bool enabled)
{
	this->location = location;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->id = id;
	this->enabled = enabled;
}

vector<float> Light::getLocation()
{
	return location;
}

vector<float> Light::getAmbient()
{
	return ambient;
}

vector<float> Light::getDiffuse()
{
	return diffuse;
}

vector<float> Light::getSpecular()
{
	return specular;
}

bool Light::isEnabled()
{
	return enabled;
}

char *Light::getId()
{
	return id;
}

void Light::setLightnr(GLenum nr)
{
	lightnr = nr;
}

GLenum Light::getLightNr()
{
	return lightnr;
}