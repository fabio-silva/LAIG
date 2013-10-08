#pragma once
#include "Primitiva.h"


class Sphere:public Primitiva{
public:
	Sphere(vector<float> data, char *cullorder);
	void draw();

protected:
	GLUquadricObj *obj;
};