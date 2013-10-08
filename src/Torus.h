#pragma once
#include "Primitiva.h"


class Torus:public Primitiva{
public:
	Torus(vector<float> data,char *cullorder);
	void draw();
};