#include "Sphere.h"

Sphere::Sphere(vector<float> data, char *cullorder):Primitiva(data, cullorder)
{
	obj = gluNewQuadric();
	GLuint esferaText;
	glGenTextures( 1, &esferaText );
	glBindTexture(GL_TEXTURE_2D, 1);
	glTranslated(7.5,1.82,6);
	gluQuadricTexture(obj,GL_TRUE); 
}

void Sphere::draw()
{
	gluSphere(obj, (double)data[0], (int)data[1], (int)data[2]);
}
