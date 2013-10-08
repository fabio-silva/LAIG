#include "Cylinder.h"

Cylinder::Cylinder(vector<float> data, char *cullorder):Primitiva(data, cullorder)
{
	obj = gluNewQuadric();
}

void Cylinder::draw()
{
	gluCylinder(obj, (double)data[0], (double)data[1], (double)data[2], (int)data[3], (int)data[4]);
}