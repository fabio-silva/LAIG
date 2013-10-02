#include "Omni.h"

Omni::Omni(vector<float> location, vector<float>ambient, vector<float>diffuse, vector<float>specular, char *id, bool enabled)
{
	this->location = location;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular= specular;
	this->id = id;
	this->enabled = enabled;
}

vector<float> Omni::getLocation()
{
	return location;
}

vector<float> Omni::getAmbient()
{
	return ambient;
}

vector<float> Omni::getDiffuse()
{
	return diffuse;
}

vector<float> Omni::getSpecular()
{
	return specular;
}

bool Omni::isEnabled()
{
	return enabled;
}

char* Omni::getId()
{
	return id;
}