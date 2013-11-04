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
}

vector <Camera*> Cena::getCameras()
{
	return scene_cameras;
}

void Cena::setInitialCameraId(char* initialCameraId)
{
	this->initialCameraId = initialCameraId;
}

void Cena::addSceneCamera(Camera* camera)
{
	scene_cameras.push_back(camera);
}

void Cena::setActiveCamera(Camera *c)
{
	activeCamera = c;
}

char* Cena::getInitialCameraId()
{
	return initialCameraId;
}

void Cena::init()
{
	

	glClearColor(backR,backG,backB,backAlpha); 

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

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


	for (unsigned int i = 0; i < omnis.size(); i++)
	{
		float pos[3] = {omnis[i]->getLocation()[0], omnis[i]->getLocation()[1], omnis[i]->getLocation()[2]};
		float ambient[3] = {omnis[i]->getAmbient()[0], omnis[i]->getAmbient()[1], omnis[i]->getAmbient()[2]};
		float diffuse[3] = {omnis[i]->getDiffuse()[0], omnis[i]->getDiffuse()[1], omnis[i]->getDiffuse()[2]};
		float specular[3] = {omnis[i]->getSpecular()[0], omnis[i]->getSpecular()[1], omnis[i]->getSpecular()[2]};

		glLightfv(omnis[i]->getLightNr(), GL_AMBIENT, ambient);
		glLightfv(omnis[i]->getLightNr(), GL_DIFFUSE, diffuse);
		glLightfv(omnis[i]->getLightNr(), GL_SPECULAR, specular);
		glLightfv(omnis[i]->getLightNr(), GL_POSITION, pos);


		if(omnis[i]->isEnabled()) glEnable(omnis[i]->getLightNr());
		else glDisable(omnis[i]->getLightNr());
	}

	for (unsigned int i = 0; i < spots.size(); i++)
	{

		float pos[3] = {spots[i]->getLocation()[0], spots[i]->getLocation()[1], spots[i]->getLocation()[2]};
		float ambient[3] = {spots[i]->getAmbient()[0], spots[i]->getAmbient()[1], spots[i]->getAmbient()[2]};
		float diffuse[3] = {spots[i]->getDiffuse()[0], spots[i]->getDiffuse()[1], spots[i]->getDiffuse()[2]};
		float specular[3] = {spots[i]->getSpecular()[0], spots[i]->getSpecular()[1], spots[i]->getSpecular()[2]};
		float direction[3] = {spots[i]->getDirection()[0], spots[i]->getDirection()[1], spots[i]->getDirection()[2]};

		glLightfv(spots[i]->getLightNr(), GL_AMBIENT, ambient);
		glLightfv(spots[i]->getLightNr(), GL_DIFFUSE, diffuse);
		glLightfv(spots[i]->getLightNr(), GL_SPECULAR, specular);
		glLightfv(spots[i]->getLightNr(), GL_POSITION, pos);
		glLightfv(spots[i]->getLightNr(), GL_SPOT_DIRECTION, direction);
		glLightf(spots[i]->getLightNr(), GL_SPOT_CUTOFF, spots[i]->getAngle());
		glLightf(spots[i]->getLightNr(), GL_SPOT_EXPONENT, spots[i]->getExponent());

		if(spots[i]->isEnabled()) glEnable(spots[i]->getLightNr());
		else glDisable(spots[i]->getLightNr());
	}


	for(unsigned int i = 0; i<graph.size(); i++) 
	{

		if(!graph[i]->isRoot()) initLists(graph[i], NULL);
		if(graph[i]->isUsingDisplayList()) 
		{
			glEndList();
			cout << "No " << graph[i]->getId() << " fechou lista " << endl;
		}
	}
}

void Cena::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	activeCamera->render();

	for(unsigned int i = 0; i<graph.size(); i++) if(graph[i]->isRoot()) 
	{
		processNode(graph[i], NULL);

	}
	axis.draw();

	glEnable(GL_TEXTURE_2D);
	glutSwapBuffers();
}


void Cena::initLists(Node *n, Material *m)
{
	Material *actualM;

	if(n->getMaterial() != NULL) actualM = n->getMaterial();
	else actualM = m;

	if(n->isUsingDisplayList()) 
	{
		cout << "No " << n->getId() << " a usar lista" << endl;
		GLuint id = glGenLists(1);
		n->setListId(id);
		glNewList(id,GL_COMPILE);

		cout << "Lista " << id << endl;
	}



	glEnable(GL_TEXTURE_2D);



	if(actualM != NULL) actualM->apply();
	glEnable(GL_MODELVIEW);
	glMultMatrixf(n->getMatrix());

	for( unsigned int i = 0; i<n->getPrimitivas().size();i++)
	{

		if(strcmp(cullface,"back") == 0) 
		{
			glEnable(GL_CULL_FACE); 
			glCullFace(GL_BACK);

			if(strcmp(drawmode, "fill") == 0) 
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else if(strcmp(drawmode, "line") == 0) 
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			}

		}
		else if(strcmp(cullface,"front") == 0)
		{
			glEnable(GL_CULL_FACE); 
			glCullFace(GL_FRONT);

			if(strcmp(drawmode, "fill") == 0) 
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else if(strcmp(drawmode, "line") == 0) 
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			}
		}
		else if(strcmp(cullface,"both")==0)
		{
			glEnable(GL_CULL_FACE); 
			glCullFace(GL_FRONT_AND_BACK);

			if(strcmp(drawmode, "fill") == 0) 
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else if(strcmp(drawmode, "line") == 0) 
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			}
		}
		else
		{
			if(strcmp(drawmode, "fill") == 0) 
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else if(strcmp(drawmode, "line") == 0) 
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			}
		}


		n->getPrimitivas()[i]->draw();

		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	}

	unsigned int i = 0;
	for(i = 0; i < n->getChildren().size(); i++)
	{
		glPushMatrix();

		initLists(n->getChildren()[i], actualM);
		glPopMatrix();

	}
}

void Cena::setAmbient(AmbientLight *ambient)
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


void Cena::processNode(Node *n, Material *m)
{  

	glEnable(GL_TEXTURE_2D);

	if (n->isUsingDisplayList())
	{
		glCallList(n->getListId());

	}
	else
	{
		Material *actualM;

		if(n->getMaterial() != NULL) actualM = n->getMaterial();
		else actualM = m;

		if(actualM != NULL) actualM->apply();
		glEnable(GL_MODELVIEW);
		glMultMatrixf(n->getMatrix());

		for( unsigned int i = 0; i<n->getPrimitivas().size();i++)
		{

			if(strcmp(cullface,"back") == 0) 
			{
				glEnable(GL_CULL_FACE); 
				glCullFace(GL_BACK);

				if(strcmp(drawmode, "fill") == 0) 
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				}
				else if(strcmp(drawmode, "line") == 0) 
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				}
				else
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
				}

			}
			else if(strcmp(cullface,"front") == 0)
			{
				glEnable(GL_CULL_FACE); 
				glCullFace(GL_FRONT);

				if(strcmp(drawmode, "fill") == 0) 
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				}
				else if(strcmp(drawmode, "line") == 0) 
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				}
				else
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
				}
			}
			else if(strcmp(cullface,"both")==0)
			{
				glEnable(GL_CULL_FACE); 
				glCullFace(GL_FRONT_AND_BACK);

				if(strcmp(drawmode, "fill") == 0) 
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				}
				else if(strcmp(drawmode, "line") == 0) 
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				}
				else
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
				}
			}
			else
			{
				if(strcmp(drawmode, "fill") == 0) 
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				}
				else if(strcmp(drawmode, "line") == 0) 
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				}
				else
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
				}
			}

			n->getPrimitivas()[i]->draw();

			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		}

		for( unsigned int i = 0; i < n->getChildren().size(); i++)
		{
			glPushMatrix();

			processNode(n->getChildren()[i], actualM);

			glPopMatrix();
		}
	}

}



char * Cena::getCullFace()
{
	return cullface;
}

void Cena::setDrawMode(char *drawmode)
{
	this->drawmode = drawmode;
}

char * Cena:: getDrawMode()
{
	return drawmode;
}
vector <Spot *> Cena::getSpots()
{
	return spots;
}

vector <Omni *> Cena::getOmnis()
{
	return omnis;
}

Cena::~Cena()
{
}

