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

void Cena::init()
{
	//glutPostRedisplay();

	glClearColor(backR,backG,backB,backAlpha); 

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

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

	float cores[] = {0.5,0.5,0.5,1};
	float pos[] = {5,5,5};
	/*glLightfv(GL_LIGHT0, GL_AMBIENT, cores);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, cores);
	glLightfv(GL_LIGHT0, GL_SPECULAR, cores);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHT0);*/

	float light0_pos[4] = {4.0, 6.0, 5.0, 1.0};
	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->enable();

	if(ambient_light->isDoubleSided()) glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	else glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	if(ambient_light->isLocal()) glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	else  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

	//if(ambient_light->isEnabled()) glEnable(GL_LIGHT0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, &ambient_light->getAmbient()[0]);
}

void Cena::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode( GL_PROJECTION);
	glLoadIdentity();

	//CGFscene::activeCamera->applyView();
	glFrustum(-10, 10, -10, 10, 0, 100.0 ); //Alterar de acordo com yaf

	glMatrixMode( GL_MODELVIEW);

	light0->draw();
	axis.draw();

	GLUquadric *quad =  gluNewQuadric();
	glPushMatrix();
	//glTranslated(2,1,2);
	gluSphere(quad,0.3,200,200);
	glPopMatrix();

	glutSwapBuffers();
}

void Cena::setAmbient(Light *ambient)
{
	ambient_light = ambient;
}

void Cena::addSpot(Spot *spot)
{
	spots.push_back(spot);
}

void Cena::addOmni(Omni *omni)
{
	omnis.push_back(omni);
}

Cena::~Cena()
{
}