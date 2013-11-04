#include "AmbientLight.h"

AmbientLight::AmbientLight(bool doublesided, bool local, bool enabled, vector<float> ambient)
{
	this->doublesided = doublesided;
	this->local = local;
	this->enabled = enabled;
	this->ambient = ambient;
}

bool AmbientLight::isDoubleSided()
{
	return doublesided;
}

bool AmbientLight::isLocal()
{
	return local;
}

bool AmbientLight::isEnabled()
{
	return enabled;
}

vector<float> AmbientLight::getAmbient()
{
	return ambient;

}