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

	int n_lights = 0;

	for (int i = 0; i < spots.size(); i++)
	{
		if (spots[i]->isEnabled())
		{
			switch(n_lights)
			{
			case 0:
				glEnable(GL_LIGHT0);
				glLightfv(GL_LIGHT0, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT0, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT0, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spots[i]->getExponent());
				break;
			case 1:
				glEnable(GL_LIGHT1);
				glLightfv(GL_LIGHT1, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT1, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT1, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT1, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spots[i]->getExponent());
				break;
			case 2:
				glEnable(GL_LIGHT2);
				glLightfv(GL_LIGHT2, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT2, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT2, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT2, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spots[i]->getExponent());
				break;
			case 3:
				glEnable(GL_LIGHT3);
				glLightfv(GL_LIGHT3, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT3, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT3, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT3, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, spots[i]->getExponent());
				break;
			case 4:
				glEnable(GL_LIGHT4);
				glLightfv(GL_LIGHT4, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT4, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT4, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT4, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, spots[i]->getExponent());
				break;
			case 5:
				glEnable(GL_LIGHT5);
				glLightfv(GL_LIGHT5, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT5, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT5, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT5, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, spots[i]->getExponent());
				break;
			case 6:
				glEnable(GL_LIGHT6);
				glLightfv(GL_LIGHT6, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT6, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT6, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT6, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, spots[i]->getExponent());
				break;
			case 7:
				glEnable(GL_LIGHT7);
				glLightfv(GL_LIGHT7, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT7, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT7, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT7, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT7, GL_SPOT_EXPONENT, spots[i]->getExponent());
				break;
			}
			n_lights++;
		}
		else
		{
			switch(n_lights)
			{
			case 0:
				glDisable(GL_LIGHT0);
				glLightfv(GL_LIGHT0, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT0, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT0, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spots[i]->getExponent());
				break;
			case 1:
				glDisable(GL_LIGHT1);
				glLightfv(GL_LIGHT1, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT1, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT1, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT1, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spots[i]->getExponent());
				break;
			case 2:
				glDisable(GL_LIGHT2);
				glLightfv(GL_LIGHT2, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT2, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT2, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT2, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spots[i]->getExponent());
				break;
			case 3:
				glDisable(GL_LIGHT3);
				glLightfv(GL_LIGHT3, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT3, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT3, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT3, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, spots[i]->getExponent());
				break;
			case 4:
				glDisable(GL_LIGHT4);
				glLightfv(GL_LIGHT4, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT4, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT4, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT4, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, spots[i]->getExponent());
				break;
			case 5:
				glDisable(GL_LIGHT5);
				glLightfv(GL_LIGHT5, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT5, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT5, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT5, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, spots[i]->getExponent());
				break;
			case 6:
				glDisable(GL_LIGHT6);
				glLightfv(GL_LIGHT6, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT6, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT6, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT6, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, spots[i]->getExponent());
				break;
			case 7:
				glDisable(GL_LIGHT7);
				glLightfv(GL_LIGHT7, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT7, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT7, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT7, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT7, GL_SPOT_EXPONENT, spots[i]->getExponent());
				break;
			}
			n_lights++;
		}
	}

	for (int i = 0; i < omnis.size(); i++)
	{
		if (omnis[i]->isEnabled())
		{
			switch(n_lights)
			{
			case 0:
				glEnable(GL_LIGHT0);
				glLightfv(GL_LIGHT0, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT0, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT0, GL_POSITION, &omnis[i]->getLocation()[0]);
				break;
			case 1:
				glEnable(GL_LIGHT1);
				glLightfv(GL_LIGHT1, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT1, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT1, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT1, GL_POSITION, &omnis[i]->getLocation()[0]);
				break;
			case 2:
				glEnable(GL_LIGHT2);
				glLightfv(GL_LIGHT2, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT2, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT2, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT2, GL_POSITION, &omnis[i]->getLocation()[0]);
				break;
			case 3:
				glEnable(GL_LIGHT3);
				glLightfv(GL_LIGHT3, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT3, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT3, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT3, GL_POSITION, &omnis[i]->getLocation()[0]);
				break;
			case 4:
				glEnable(GL_LIGHT4);
				glLightfv(GL_LIGHT4, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT4, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT4, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT4, GL_POSITION, &omnis[i]->getLocation()[0]);
				break;
			case 5:
				glEnable(GL_LIGHT5);
				glLightfv(GL_LIGHT5, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT5, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT5, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT5, GL_POSITION, &omnis[i]->getLocation()[0]);
				break;
			case 6:
				glEnable(GL_LIGHT6);
				glLightfv(GL_LIGHT6, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT6, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT6, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT6, GL_POSITION, &omnis[i]->getLocation()[0]);
				break;
			case 7:
				glEnable(GL_LIGHT7);
				glLightfv(GL_LIGHT7, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT7, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT7, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT7, GL_POSITION, &omnis[i]->getLocation()[0]);
				break;
			}
			n_lights++;
		}
		else
		{
			switch(n_lights)
			{
			case 0:
				glDisable(GL_LIGHT0);
				glLightfv(GL_LIGHT0, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT0, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT0, GL_POSITION, &omnis[i]->getLocation()[0]);
				break;
			case 1:
				glDisable(GL_LIGHT1);
				glLightfv(GL_LIGHT1, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT1, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT1, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT1, GL_POSITION, &omnis[i]->getLocation()[0]);
				break;
			case 2:
				glDisable(GL_LIGHT2);
				glLightfv(GL_LIGHT2, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT2, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT2, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT2, GL_POSITION, &omnis[i]->getLocation()[0]);
				break;
			case 3:
				glDisable(GL_LIGHT3);
				glLightfv(GL_LIGHT3, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT3, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT3, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT3, GL_POSITION, &omnis[i]->getLocation()[0]);
				break;
			case 4:
				glDisable(GL_LIGHT4);
				glLightfv(GL_LIGHT4, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT4, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT4, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT4, GL_POSITION, &omnis[i]->getLocation()[0]);
				break;
			case 5:
				glDisable(GL_LIGHT5);
				glLightfv(GL_LIGHT5, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT5, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT5, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT5, GL_POSITION, &omnis[i]->getLocation()[0]);
				break;
			case 6:
				glDisable(GL_LIGHT6);
				glLightfv(GL_LIGHT6, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT6, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT6, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT6, GL_POSITION, &omnis[i]->getLocation()[0]);
				break;
			case 7:
				glDisable(GL_LIGHT7);
				glLightfv(GL_LIGHT7, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT7, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT7, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT7, GL_POSITION, &omnis[i]->getLocation()[0]);
				break;
			}
			n_lights++;
		}
	}

	/*float light0_pos[4] = {4.0, 6.0, 5.0, 1.0};
	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->enable();*/

	if(ambient_light->isDoubleSided()) glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	else glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	if(ambient_light->isLocal()) glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	else  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

	if(ambient_light->isEnabled()) glLightModelfv(GL_LIGHT_MODEL_AMBIENT, &ambient_light->getAmbient()[0]);
}

void Cena::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode( GL_PROJECTION);
	glLoadIdentity();

	//CGFscene::activeCamera->applyView();
	glFrustum(-10, 10, -10, 10, 0, 100.0 ); //Alterar de acordo com yaf

	glMatrixMode( GL_MODELVIEW);

	//light0->draw();
	axis.draw();

	/*GLUquadric *quad =  gluNewQuadric();
	glPushMatrix();
	gluSphere(quad,0.3,200,200);*/

	for(int i = 0; i<graph.size();i++)
	{
		if( strcmp(graph[i]->getId(), "rectangulo") == 0)
		{
			
			glPushMatrix();
			glRotated(270,0,1,0);
			glBegin(GL_POLYGON);
			glVertex2d(graph[i]->getData()[0], graph[i]->getData()[1]);
			glVertex2d(graph[i]->getData()[2], graph[i]->getData()[1]);
			glVertex2d(graph[i]->getData()[2], graph[i]->getData()[3]);
			glVertex2d(graph[i]->getData()[0], graph[i]->getData()[3]);
			glEnd();
			glPopMatrix();
		}
	}
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

char *Cena::getCullOrder()
{
	return cullorder;
}

void Cena::setGraph(vector<Node *> graph)
{
	this->graph = graph; 
}
Cena::~Cena()
{
}

