#include "Cena.h"
#include <iostream>

Cena::Cena()
{
	activeCamera = NULL;
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

	activeCamera = NULL;

	std::cout << "bckgrd = " << backR << " " << backG << " " << backB << " " << backAlpha << std::endl;
}

void Cena::setInitialCameraId(char* initialCameraId)
{
	this->initialCameraId = initialCameraId;
}

void Cena::addSceneCamera(Camera* camera)
{
	scene_cameras.push_back(camera);
}

void Cena::setActiveCamera(Camera* camera)
{
	activeCamera = camera;
}

char* Cena::getInitialCameraId()
{
	return initialCameraId;
}

void Cena::init()
{
	//glutPostRedisplay();

	glClearColor(backR,backG,backB,backAlpha); 

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

		
	if(strcmp(cullface,"back") == 0) 
		{
			glEnable(GL_CULL_FACE);	
			glCullFace(GL_BACK);
		
			if(strcmp(drawmode, "fill") == 0) glPolygonMode(GL_BACK, GL_FILL);
			else if(strcmp(drawmode, "line") == 0) glPolygonMode(GL_BACK, GL_LINE);
		
				else glPolygonMode(GL_BACK, GL_POINT);
			
		}
	
	else if(strcmp(cullface,"front") == 0)
	{
		glEnable(GL_CULL_FACE);	
		glCullFace(GL_FRONT);
		
		if(strcmp(drawmode, "fill") == 0) glPolygonMode(GL_FRONT, GL_FILL);
			else if(strcmp(drawmode, "line") == 0) glPolygonMode(GL_FRONT, GL_LINE);
				else glPolygonMode(GL_FRONT, GL_POINT);
	}


	else if(strcmp(cullface,"both")==0)
	{
		glEnable(GL_CULL_FACE);	
		glCullFace(GL_FRONT_AND_BACK);

		if(strcmp(drawmode, "fill") == 0) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			else if(strcmp(drawmode, "line") == 0) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				else glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}


	if(strcmp(shading, "flat") == 0) glShadeModel(GL_FLAT);
	else glShadeModel(GL_SMOOTH);

	if(strcmp(cullorder, "CW") == 0) glFrontFace(GL_CW);
	else glFrontFace(GL_CCW);

	int n_lights = 0;

	if(ambient_light->isDoubleSided()) glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	else glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	if(ambient_light->isLocal()) glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	else  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

	if(ambient_light->isEnabled()) glLightModelfv(GL_LIGHT_MODEL_AMBIENT, &ambient_light->getAmbient()[0]);

	for (int i = 0; i < spots.size(); i++)
	{
		if (spots[i]->isEnabled())
		{
			switch(n_lights)
			{
			case 0:
				glLightfv(GL_LIGHT0, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT0, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT0, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spots[i]->getExponent());
				glEnable(GL_LIGHT0);
				break;
			case 1:
				glLightfv(GL_LIGHT1, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT1, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT1, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT1, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spots[i]->getExponent());
				glEnable(GL_LIGHT1);
				break;
			case 2:
				glLightfv(GL_LIGHT2, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT2, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT2, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT2, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spots[i]->getExponent());
				glEnable(GL_LIGHT2);
				break;
			case 3:
				glLightfv(GL_LIGHT3, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT3, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT3, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT3, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, spots[i]->getExponent());
				glEnable(GL_LIGHT3);
				break;
			case 4:
				glLightfv(GL_LIGHT4, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT4, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT4, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT4, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, spots[i]->getExponent());
				glEnable(GL_LIGHT4);
				break;
			case 5:
				glLightfv(GL_LIGHT5, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT5, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT5, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT5, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, spots[i]->getExponent());
				glEnable(GL_LIGHT5);
				break;
			case 6:
				glLightfv(GL_LIGHT6, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT6, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT6, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT6, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, spots[i]->getExponent());
				glEnable(GL_LIGHT6);
				break;
			case 7:
				glLightfv(GL_LIGHT7, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT7, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT7, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT7, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT7, GL_SPOT_EXPONENT, spots[i]->getExponent());
				glEnable(GL_LIGHT7);
				break;
			}
			n_lights++;
		}
		else
		{
			switch(n_lights)
			{
			case 0:
				glLightfv(GL_LIGHT0, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT0, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT0, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spots[i]->getExponent());
				glDisable(GL_LIGHT0);
				break;
			case 1:
				glLightfv(GL_LIGHT1, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT1, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT1, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT1, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spots[i]->getExponent());
				glDisable(GL_LIGHT1);
				break;
			case 2:
				glLightfv(GL_LIGHT2, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT2, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT2, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT2, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spots[i]->getExponent());
				glDisable(GL_LIGHT2);
				break;
			case 3:
				glLightfv(GL_LIGHT3, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT3, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT3, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT3, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, spots[i]->getExponent());
				glDisable(GL_LIGHT3);
				break;
			case 4:
				glLightfv(GL_LIGHT4, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT4, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT4, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT4, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, spots[i]->getExponent());
				glDisable(GL_LIGHT4);
				break;
			case 5:
				glLightfv(GL_LIGHT5, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT5, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT5, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT5, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, spots[i]->getExponent());
				glDisable(GL_LIGHT5);
				break;
			case 6:
				glLightfv(GL_LIGHT6, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT6, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT6, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT6, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, spots[i]->getExponent());
				glDisable(GL_LIGHT6);
				break;
			case 7:
				glLightfv(GL_LIGHT7, GL_AMBIENT, &spots[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT7, GL_DIFFUSE, &spots[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT7, GL_SPECULAR, &spots[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT7, GL_POSITION, &spots[i]->getLocation()[0]);
				glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, &spots[i]->getDirection()[0]);
				glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, spots[i]->getAngle());
				glLightf(GL_LIGHT7, GL_SPOT_EXPONENT, spots[i]->getExponent());
				glDisable(GL_LIGHT7);
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
				glLightfv(GL_LIGHT0, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT0, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT0, GL_POSITION, &omnis[i]->getLocation()[0]);
				glEnable(GL_LIGHT0);
				break;
			case 1:
				glLightfv(GL_LIGHT1, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT1, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT1, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT1, GL_POSITION, &omnis[i]->getLocation()[0]);
				glEnable(GL_LIGHT1);
				break;
			case 2:
				glLightfv(GL_LIGHT2, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT2, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT2, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT2, GL_POSITION, &omnis[i]->getLocation()[0]);
				glEnable(GL_LIGHT2);
				break;
			case 3:
				glLightfv(GL_LIGHT3, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT3, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT3, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT3, GL_POSITION, &omnis[i]->getLocation()[0]);
				glEnable(GL_LIGHT3);
				break;
			case 4:
				glLightfv(GL_LIGHT4, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT4, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT4, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT4, GL_POSITION, &omnis[i]->getLocation()[0]);
				glEnable(GL_LIGHT4);
				break;
			case 5:
				glLightfv(GL_LIGHT5, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT5, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT5, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT5, GL_POSITION, &omnis[i]->getLocation()[0]);
				glEnable(GL_LIGHT5);
				break;
			case 6:
				glLightfv(GL_LIGHT6, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT6, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT6, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT6, GL_POSITION, &omnis[i]->getLocation()[0]);
				glEnable(GL_LIGHT6);
				break;
			case 7:
				glLightfv(GL_LIGHT7, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT7, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT7, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT7, GL_POSITION, &omnis[i]->getLocation()[0]);
				glEnable(GL_LIGHT7);
				break;
			}
			n_lights++;
		}
		else
		{
			switch(n_lights)
			{
			case 0:
				glLightfv(GL_LIGHT0, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT0, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT0, GL_POSITION, &omnis[i]->getLocation()[0]);
				glDisable(GL_LIGHT0);
				break;
			case 1:
				glLightfv(GL_LIGHT1, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT1, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT1, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT1, GL_POSITION, &omnis[i]->getLocation()[0]);
				glDisable(GL_LIGHT1);
				break;
			case 2:
				glLightfv(GL_LIGHT2, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT2, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT2, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT2, GL_POSITION, &omnis[i]->getLocation()[0]);
				glDisable(GL_LIGHT2);
				break;
			case 3:
				glLightfv(GL_LIGHT3, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT3, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT3, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT3, GL_POSITION, &omnis[i]->getLocation()[0]);
				glDisable(GL_LIGHT3);
				break;
			case 4:
				glLightfv(GL_LIGHT4, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT4, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT4, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT4, GL_POSITION, &omnis[i]->getLocation()[0]);
				glDisable(GL_LIGHT4);
				break;
			case 5:
				glLightfv(GL_LIGHT5, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT5, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT5, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT5, GL_POSITION, &omnis[i]->getLocation()[0]);
				glDisable(GL_LIGHT5);
				break;
			case 6:
				glLightfv(GL_LIGHT6, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT6, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT6, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT6, GL_POSITION, &omnis[i]->getLocation()[0]);
				glDisable(GL_LIGHT6);
				break;
			case 7:
				glLightfv(GL_LIGHT7, GL_AMBIENT, &omnis[i]->getAmbient()[0]);
				glLightfv(GL_LIGHT7, GL_DIFFUSE, &omnis[i]->getDiffuse()[0]);
				glLightfv(GL_LIGHT7, GL_SPECULAR, &omnis[i]->getSpecular()[0]);
				glLightfv(GL_LIGHT7, GL_POSITION, &omnis[i]->getLocation()[0]);
				glDisable(GL_LIGHT7);
				break;
			}
			n_lights++;
		}
	}
}

void Cena::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/*glMatrixMode( GL_PROJECTION);
	glLoadIdentity();
	//CGFscene::activeCamera->applyView();
	glFrustum(-1, 1, -1, 1, 1.5, 500.0 );
	gluPerspective(90,1280/720,0.3,300);
	//glRotated(45,0,1,0);
	glMatrixMode( GL_MODELVIEW);
	//glLoadIdentity();
	gluLookAt(30,15,20,0,0,0,0,1,0);*/

	activeCamera->render();
	cout << "CAMARA ACTIVA " << endl;

	//axis.draw();


	for(int i = 0; i<graph.size(); i++) if(graph[i]->isRoot()) 
		{
			processNode(graph[i], NULL);
		}

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


void Cena::calculateMatrixes(Node *n)
{
	float newMatrix[16];
	glPushMatrix();
	
	glLoadMatrixf(n->getMatrix());
	
	if(n->getParent() != NULL) 
	{
		glMultMatrixf(n->getParent()->getMatrix());
		glGetFloatv(GL_MODELVIEW_MATRIX, newMatrix);
		n->setMatrix(newMatrix);
	}

	
	
	
	//glPopMatrix();
	

	for(int i = 0; i < n->getChildren().size(); i++) calculateMatrixes(n->getChildren()[i]);
}
void Cena::processNode(Node *n, Material *m)
{     
	
	glEnable(GL_TEXTURE_2D);

	cout << "A processar No: " << n->getId() << endl;
			
	if(n->getMaterial() != NULL) n->getMaterial()->apply();
	
	
	cout << "Textura ok " << endl;
	glMultMatrixf(n->getMatrix());
	
	for(int i = 0; i<n->getPrimitivas().size();i++)
	{
		n->getPrimitivas()[i]->draw();
	}
		
	glDisable(GL_TEXTURE_2D);


		
		for(int i = 0; i < n->getChildren().size(); i++)
		{
			glPushMatrix();
			processNode(n->getChildren()[i], n->getMaterial());
			glPopMatrix();
		}
			
	
	
}
Cena::~Cena()
{
}

