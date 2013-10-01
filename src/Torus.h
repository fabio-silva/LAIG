#pragma once

#include "CGFobject.h"

class Torus: public CGFobject{
public:
	Torus(int numc, int numt);
	void draw();
private:
	int numc, numt;
};