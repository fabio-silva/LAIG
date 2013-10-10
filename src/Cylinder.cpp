#include "Cylinder.h"

Cylinder::Cylinder(vector<float> data, char *cullorder):Primitiva(data, cullorder)
{
	obj = gluNewQuadric();
	GLuint esferaText;
	glGenTextures( 1, &esferaText );
	glBindTexture(GL_TEXTURE_2D, 1);
	glTranslated(7.5,1.82,6);
	gluQuadricTexture(obj,GL_TRUE); 
}

void Cylinder::draw()
{
	gluCylinder(obj, (double)data[0], (double)data[1], (double)data[2], (int)data[3], (int)data[4]);
}