#pragma once

#include "Plane.h"
class WindowWall {
public:
	WindowWall(void);
	WindowWall(int, double, double);
	~WindowWall(void);
	void draw();
private:
	int _numDivisions; // Number of triangles that constitute rows/columns
	double domain;
	double delta;
};

