#include "Triangle.h"

Triangle::Triangle(vector <float> data,  char *cullorder, char *shading) : Primitiva(data,cullorder)
{
	this->shading = shading;
}



void Triangle::draw()
{
	glBegin(GL_POLYGON);

	if(strcmp(cullorder, "CW") == 0)
	{
		if(strcmp(shading, "flat")==0) glNormal3fv(&getNormals()[0]);
		if(strcmp(shading,"gouraud") == 0) glNormal3f(data[0], data[1], data[2]);
		glTexCoord2d(0.5, 1);
		glVertex3f(data[0], data[1], data[2]);

		if(strcmp(shading,"gouraud") == 0) glNormal3f(data[3],data[4], data[5]);
		glTexCoord2d(1, 0);
		glVertex3f(data[3], data[4], data[5]);

		if(strcmp(shading,"gouraud") == 0) glNormal3f(data[6],data[7],data[8]);
		glTexCoord2d(0, 0);
		glVertex3f(data[6], data[7], data[8]);
	}

	else
	{
		if(strcmp(shading, "flat")==0) glNormal3fv(&getNormals()[0]);
		if(strcmp(shading,"gouraud") == 0) glNormal3f(data[6],data[7],data[8]);
		glTexCoord2d(0, 0);
		glVertex3f(data[6], data[7], data[8]);

		if(strcmp(shading,"gouraud") == 0) glNormal3f(data[3],data[4],data[5]);
		glTexCoord2d(1, 0);
		glVertex3f(data[3], data[4], data[5]);

		if(strcmp(shading,"gouraud") == 0) glNormal3f(data[0],data[1],data[2]);
		glTexCoord2d(0.5, 1);
		glVertex3f(data[0], data[1], data[2]);
	}

	glEnd();
}

