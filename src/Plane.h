#pragma once

#include "CGFobject.h"
class Plane {
public:
	Plane(void);
	Plane(int, int, int, double, double);
	~Plane(void);
	void draw();
private:
	int _numDivisions; // Number of triangles that constitute rows/columns
	int sMultiplier;
	int tMultiplier;
	double domain;
	double delta;
};

