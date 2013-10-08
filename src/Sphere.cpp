#include "Sphere.h"

Sphere::Sphere(vector<float> data, char *cullorder):Primitiva(data, cullorder)
{
	obj = gluNewQuadric();
}

void Sphere::draw()
{
	gluSphere(obj, (double)data[0], (int)data[1], (int)data[2]);
}
