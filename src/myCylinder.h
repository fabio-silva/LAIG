#ifndef MY_CYLINDER
#define MY_CYLINDER

#include "CGFobject.h"

class myCylinder: public CGFobject {

public:
	myCylinder(int slices, int stacks, bool smooth);
	void draw();
	int slices;
	int stacks;
	bool smooth;
};

#endif
