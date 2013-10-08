#include "Triangle.h"

Triangle::Triangle(vector <float> data,  char *cullorder) : Primitiva(data,cullorder)
{
}

void Triangle::draw()
{
	glBegin(GL_POLYGON);

	if(strcmp(cullorder, "CW") == 0)
	{
		glTexCoord2d(0.5, 1);
		glVertex3f(data[0], data[1], data[2]);

		glTexCoord2d(1, 0);
		glVertex3f(data[3], data[4], data[5]);

		glTexCoord2d(0, 0);
		glVertex3f(data[6], data[7], data[8]);
	}

	else
	{
		glTexCoord2d(0, 0);
		glVertex3f(data[6], data[7], data[8]);
				
		glTexCoord2d(1, 0);
		glVertex3f(data[3], data[4], data[5]);

		glTexCoord2d(0.5, 1);
		glVertex3f(data[0], data[1], data[2]);


	}

	glEnd();
}