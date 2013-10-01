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