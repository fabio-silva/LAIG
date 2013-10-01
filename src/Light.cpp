#include "Light.h"

Light::Light(bool doublesided, bool local, bool enabled, vector<float> ambient):doublesided(doublesided), local(local),enabled(enabled), ambient(ambient)
{
}

bool Light::isDoubleSided()
{
	return doublesided;
}

bool Light::isLocal()
{
	return local;
}

bool Light::isEnabled()
{
	return enabled;
}

vector<float> Light::getAmbient()
{
	return ambient;
}