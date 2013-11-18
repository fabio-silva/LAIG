#ifndef SPOT_H
#define SPOT_H

#include <vector>
#include "GL\gl.h"
#include "Light.h"
using namespace std;

class Spot:public Light{

public:
	Spot(vector<float> location, vector<float>ambient, vector<float>diffuse, vector<float>specular, vector<float> direction, char *id, bool enabled, float angle, float exponent);
	vector<float> getDirection();
	float getAngle();
	float getExponent();

protected:
	vector<float> direction;
	float angle,exponent;
};
#endif