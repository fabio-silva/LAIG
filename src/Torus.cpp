#include "Torus.h"
#include <math.h>


Torus::Torus(vector<float> data,char *cullorder):Primitiva(data ,cullorder)
{
	
}
void Torus::draw()
{
	glutSolidTorus((double)data[0], (double)data[1], (int)data[2], (int)data[3]);
}