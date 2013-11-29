#pragma once

#include "Primitiva.h"

class Cylinder:public Primitiva{
public:
	Cylinder(vector<float> data, char *cullorder);
	void draw();
	vector<float> getNormals(){vector<float> res; return res;}

protected:
	GLUquadricObj *obj;
};