#pragma once
#define BALLOON_SIDE 10.0
#include "Primitiva.h"
#include "Patch.h"
#include "Rectangle.h"
class Vehicle:public Primitiva
{
public:
	Vehicle(char *cullorder);
	void draw();
protected:
	Rectangle *f1,*f2,*f3,*f4,*f5;
	Material *m,*m2;
	Patch *p;

	

	
};