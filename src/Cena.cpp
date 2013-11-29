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
	gameBeginning = true;
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
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	




	/*Client *client = new Client(60001, "127.0.0.1");

	string msg  = "'Ola mundo'.";

	client->sendData(const_cast<char*>(msg.c_str()));

	cout << "DATA SENT " << endl;
	char *data = client->receiveData();

	string temp = data;

	string sub = temp.substr(0, temp.size() - 2);

	cout << "SUB = " << sub << endl;
	cout << "DATA = " << data << endl;

	char delimiters[] = {'[',']'};
	string new_data = strtok(data,delimiters);
	cout << new_data << endl;
	getchar();
	exit(1);
	vector<string> datas;
	int size = 21;
	while (size > 0)
	{
	if (strcmp(new_data.c_str(),",") != 0 && strcmp(new_data.c_str(),".") != 0)
	{
	cout << "NEW DATA = " << new_data << endl;
	datas.push_back(new_data);
	}
	new_data = strtok(NULL,delimiters);	

	size--;
	}
	this->setDatas(datas);
	blank_hexa = new Hexagon("CCW",0);
	p1_hexa = new Hexagon("CCW",1);
	p2_hexa = new Hexagon("CCW",2);*/
}

void Cena::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	



	glEnable(GL_TEXTURE_2D);
	if(gameBeginning)
	{

		glOrtho(0, 10, 0, 10, 0, 1);
		GLfloat emission[] = {2.0,2.0,2.0,2.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
		//Ecra Inicial
		vector<float> default(4,1.0);

		Material *initialTex = new Material(NULL, default, default, default, default, 1.0, 1, 1, GL_CCW);
		initialTex->setTexture(new Texture(NULL, "initial.jpg"));

		initialTex->apply();

		glBegin(GL_POLYGON);

		glNormal3d(0, 0, 1);

		glTexCoord2f(0.0, 1.0);
		glVertex2f(0.0, 10.0);

		glTexCoord2f(0.0, 0.0);
		glVertex2f(0.0, 0.0);

		glTexCoord2f(1.0, 0.0);
		glVertex2f(10.0, 0.0);

		glTexCoord2f(1.0, 1.0);
		glVertex2f(10.0, 10.0);

		glEnd();
	}

	else
	{
		activeCamera->render();
		glPushMatrix();
		glTranslated(3,0,11);
		glRotated(90,1,0,0);
		int cont;
		/*for(int i = 0; i < datas.size(); i++)
		{
		cont = 0;
		for(int j = 0; j < datas[i].size(); j++)
		{
		if (datas[i][j] == '0')
		{
		glPushMatrix();
		if (i <= 5)
		glTranslated((0.5*j+(-0.5*i)),(-1*i),0);
		if (i >= 6)
		glTranslated((0.5*j+(-5+(0.5*i))),(-1*i),0);
		blank_hexa->draw();
		glPopMatrix();
		cont++;
		}
		else if (datas[i][j] == '1')
		{
		glPushMatrix();
		if (i <= 5)
		glTranslated((0.5*j+(-0.5*i)),(-1*i),0);
		if (i >= 6)
		glTranslated((0.5*j+(-5+(0.5*i))),(-1*i),0);
		p1_hexa->draw();
		glPopMatrix();
		cont++;
		}
		else if (datas[i][j] == '2')
		{
		glPushMatrix();
		if (i <= 5)
		glTranslated((0.5*j+(-0.5*i)),(-1*i),0);
		if (i >= 6)
		glTranslated((0.5*j+(-5+(0.5*i))),(-1*i),0);
		p2_hexa->draw();
		glPopMatrix();
		cont++;
		}
		}
		}*/
		glPopMatrix();
	}
	glFlush();
	glutSwapBuffers();
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

void Cena::setDatas(vector<string> datas)
{
	this->datas = datas;
}

bool Cena::isGameStarting()
{
	return gameBeginning;
}

Cena::~Cena()
{
}

