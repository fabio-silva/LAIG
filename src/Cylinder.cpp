#include "Cylinder.h"

Cylinder::Cylinder(vector<float> data, char *cullorder):Primitiva(data, cullorder)
{
	obj = gluNewQuadric();
	/*GLuint esferaText;
	glGenTextures( 1, &esferaText );
	glBindTexture(GL_TEXTURE_2D, 1);
	gluQuadricTexture(obj,GL_TRUE); */
}

void Cylinder::draw()
{
/*	if (strcmp(cullorder,"CW") == 0)
	{
		gluQuadricOrientation(obj, GLU_INSIDE);
	}
	else if (strcmp(cullorder,"CCW") == 0)
	{
		gluQuadricOrientation(obj, GLU_OUTSIDE);
	}*/

	gluQuadricDrawStyle(obj, GLU_FILL);
	gluQuadricTexture(obj, GL_TRUE);
	gluQuadricNormals(obj, GLU_SMOOTH);

	gluCylinder(obj, (double)data[0], (double)data[1], (double)data[2], (int)data[3], (int)data[4]);
}