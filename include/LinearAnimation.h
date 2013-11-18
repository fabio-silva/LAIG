#pragma once

#include "Animation.h"


class LinearAnimation:public Animation
{
public:
	LinearAnimation(vector<vector<float>> ctrlPoints, int nControlPoints, float duration,char *id);
	void draw();

protected:
	Vehicle *v;
	int nextPoint;
	int currentTime, previousTime;
	float curX,curY,curZ;	
	vector<vector<float>> vectors;
	vector<float> angles;
};