#pragma once

#include "CGFobject.h"

#include "Primitiva.h"

class Plane :public Primitiva{
public:
	Plane(int div);
	void draw();

private:
	int divisions;
};

