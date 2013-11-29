#pragma once

#include "Primitiva.h"

class Triangle:public Primitiva{

public:
	Triangle(vector<float> data, char *cullorder, char *shading);
	void draw();
protected:
	char *shading;
};