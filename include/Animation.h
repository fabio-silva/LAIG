#pragma once

#include "Vehicle.h"
#include <string.h>
#include <math.h>

#define PI 3.14159265

class Animation
{
public:
	Animation(vector<vector<float>> ctrlPoints, int nControlPoints, float duration,char *id);
	void draw();

protected:
	vector<vector<float>> ctrlPoints;
	int nControlPoints;
	float duration;
	float timeLeft;
	vector<float> currentPoint;
	float velocity;
	float distance;
	char *id;
};