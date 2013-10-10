#pragma once
#include "Primitiva.h"


class Sphere:public Primitiva{
public:
	Sphere(vector<float> data, char *cullorder);
	void draw();
	vector<float> getNormals(){vector<float> res; return res;}

protected:
	GLUquadricObj *obj;
};