#include "Cena.h"
#include <iostream>
Cena::Cena()
{
}

void Cena::setGlobals(float backR, float backG, float backB, float backAlpha, char *drawmode, char *shading, char *cullface, char *cullorder)
{
	this->backR = backR;
	this->backG = backG;
	this->backB = backB;
	this->backAlpha = backAlpha;
	this->drawmode = drawmode;
	this->shading = shading;
	this->cullface = cullface;
	this->cullorder = cullorder;

	std::cout << "bckgrd = " << backR << " " << backG << " " << backB << " " << backAlpha << std::endl;
}

void Cena::processa()
{
	
	GLUI  *glui2;
	

	
	

	 


	glutPostRedisplay();

	glClearColor(backR,backG,backB,backAlpha); 
	
	glEnable(GL_CULL_FACE);		
	if(strcmp(cullface,"back") == 0) glCullFace(GL_BACK);
	else glCullFace(GL_FRONT);

	if(strcmp(drawmode, "fill") == 0) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else if(strcmp(drawmode, "line") == 0) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	if(strcmp(shading, "flat") == 0) glShadeModel(GL_FLAT);
	else glShadeModel(GL_SMOOTH);

	if(strcmp(cullorder, "CW") == 0) glFrontFace(GL_CW);
	else glFrontFace(GL_CCW);



}