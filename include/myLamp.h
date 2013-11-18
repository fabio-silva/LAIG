#ifndef MY_LAMP
#define MY_LAMP

#include "CGFobject.h"

class myLamp: public CGFobject {

public:
	myLamp(int slices, int stacks);
	void draw();
	int slices;
	int stacks;
};

#endif
