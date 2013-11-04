#include "Rectangle.h"


Rectangle::Rectangle(vector <float> data, char *cullorder, char* shading) : Primitiva(data, cullorder)
{
	this->shading = shading;
}



void Rectangle::draw()
{
	float w = fabs(data[2]-data[0]);
	float h = fabs(data[3] - data[1]);
	glBegin(GL_POLYGON);
	
	if(strcmp(cullorder, "CW") == 0 )
	{ 
		if(strcmp(shading, "flat")==0) glNormal3fv(&getNormals()[0]);

		if(strcmp(shading,"gouraud") == 0)glNormal3fv(&getNormals()[0]);
		//glTexCoord2d(0,1);
		if(material != NULL) glTexCoord2d(0,h/material->get_t());
		else glTexCoord2d(0,1);
		glVertex2d(data[0],data[3]);

		if(strcmp(shading,"gouraud") == 0) glNormal3fv(&getNormals()[0]);
		//glTexCoord2d(1,1);
		if(material != NULL) glTexCoord2d(w/material->get_s(),h/material->get_t());
		else glTexCoord2d(1,1);
		glVertex2d(data[2], data[3]);

		if(strcmp(shading,"gouraud") == 0) glNormal3fv(&getNormals()[0]);
		//glTexCoord2d(1,0);
		if(material != NULL) glTexCoord2d(w/material->get_s(),0);
		else glTexCoord2d(1,0);
		glVertex2d(data[2], data[1]);

		if(strcmp(shading,"gouraud") == 0) glNormal3fv(&getNormals()[0]);
		//glTexCoord2d(0,0);
		if(material != NULL) glTexCoord2d(0,0);
		else glTexCoord2d(0,0);
		glVertex2d(data[0], data[1]);

	}

	else 
	{
		
		if(strcmp(shading, "flat")==0) glNormal3f(getNormals()[0],getNormals()[1],getNormals()[2]);
		
		if(strcmp(shading,"gouraud") == 0) glNormal3fv(&getNormals()[0]);
		glTexCoord2d(0,1);
		
		
		glVertex2d(data[0],data[3]);

		if(strcmp(shading,"gouraud") == 0) glNormal3fv(&getNormals()[0]);
		glTexCoord2d(0,0);
		
		glVertex2d(data[0], data[1]); 

		if(strcmp(shading,"gouraud") == 0) glNormal3fv(&getNormals()[0]);
		glTexCoord2d(1,0);
		
		glVertex2d(data[2], data[1]);

		if(strcmp(shading,"gouraud") == 0) glNormal3fv(&getNormals()[0]);
		glTexCoord2d(1,1);
		
		glVertex2d(data[2], data[3]);
	}

	glEnd();
}