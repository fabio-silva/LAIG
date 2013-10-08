#pragma once
#include "Primitiva.h"


class Cylinder:public Primitiva{
public:
	Cylinder(vector<float> data, char *cullorder);
	void draw();

protected:
	GLUquadricObj *obj;
};