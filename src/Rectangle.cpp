#include "Rectangle.h"


Rectangle::Rectangle(vector <float> data, char *cullorder) : Primitiva(data, cullorder)
{
}

void Rectangle::draw()
{
	glBegin(GL_POLYGON);
	if(strcmp(cullorder, "CW") == 0) 
	{


		glTexCoord2d(0,1);
		glVertex2d(data[0],data[3]);

		glTexCoord2d(1,1);
		glVertex2d(data[2], data[3]);

		glTexCoord2d(1,0);
		glVertex2d(data[2], data[1]);

		glTexCoord2d(0,0);
		glVertex2d(data[0], data[1]);


	}

	else
	{


		glTexCoord2d(0,0);
		glVertex2d(data[0], data[1]);

		glTexCoord2d(1,0);
		glVertex2d(data[2], data[1]);

		glTexCoord2d(1,1);
		glVertex2d(data[2], data[3]);

		glTexCoord2d(0,1);
		glVertex2d(data[0],data[3]);

	}

	glEnd();
}