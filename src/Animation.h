#pragma once

#include "Vehicle.h"
#include <string.h>
#include <math.h>

class Animation
{
public:
	Animation(vector<vector<float>> ctrlPoints, int nControlPoints, float duration);
	void draw();

protected:
	vector<vector<float>> ctrlPoints;
	int nControlPoints;
	float duration;
	float timeLeft;
	vector<float> currentPoint;
	float velocity;
	float distance;
};