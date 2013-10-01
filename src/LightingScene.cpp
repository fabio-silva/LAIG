#include "LightingScene.h"





using namespace std;

float pi = acos(-1.0);
float deg2rad = pi / 180.0;

#define BOARD_HEIGHT 6.0
#define BOARD_WIDTH 6.4

// number of divisions
#define BOARD_A_DIVISIONS 30
#define BOARD_B_DIVISIONS 100

// Positions for two lights
float light0_pos[4] = { 8, 6.0, 8, 1.0 };
float light1_pos[4] = { 10, 6.0, 0.25, 1.0 }; //luz fagota 2
float light2_pos[4] = { 13, 4.0, 6, 1.0 };
float light3_pos[4] = { 0.25, 6.0, 10.0, 1.0 }; //luz fagota 1
float light4_pos[4] = { 0.2, 4, -3.5, 1.0 };

// Global ambient light (do not confuse with ambient component of individual lights)
float globalAmbientLight[4] = { 0, 0, 0, 1.0 };
float ambientNull[4] = { 1, 1, 1, 0};
float yellow[4] = { 1, 1, 0, 1 };

float ambTable[3] = { 0.2, 0.2, 0.2 };
float difTable[3] = { 1, 1, 1 };
float specTable[3] = { 0.2, 0.2, 0.2 };
float shininessTable = 1.0f;

float ambSlides[3] = { 0.2, 0.2, 0.2 };
float difSlides[3] = { 1, 1, 1 };
float specSlides[3] = { 0.2, 0.2, 0.2 };
float shininessSlides = 1.0f;

float ambBoard[3] = { 0.2, 0.2, 0.2 };
float difBoard[3] = { 0.5, 0.5, 0.5 };
float specBoard[3] = { 0.4, 0.4, 0.4 };
float shininessBoard = 60.0f;

float ambClock[3] = { 1, 1, 1 };
float difClock[3] = { 1, 1, 1 };
float specClock[3] = { 1, 1, 1 };
float shininessClock = 400.0f;

float ambFloor[3] = { 1, 1, 1 };
float difFloor[3] = { 1, 1, 1 };
float specFloor[3] = { 0, 0, 0 };
float shininessFloor = 10.0f;

float ambLamp[3] = { 1, 1, 1 };
float difLamp[3] = { 1, 1, 1 };
float specLamp[3] = { 1, 1, 1 };
float shininessLamp = 400.0f;

float ambWindow[3] = { 1, 1, 1 };
float difWindow[3] = { 1, 1, 1 };
float specWindow[3] = { 1, 1, 1 };
float shininessWindow = 800.0f;

float ambRobot[3] = { 1, 1, 1 };
float difRobot[3] = { 1, 1, 1 };
float specRobot[3] = { 1, 1, 1 };
float shininessRobot = 400.0f;

float cores[3] = {1,1,1};
float cores1[4] = {1,1,1,1};



void LightingScene::init() {
	// Enables lighting computations
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	// Sets up some lighting parameters
	// Computes lighting only using the front face normals and materials
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	// Define ambient light (do not confuse with ambient component of individual lights)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);

	sceneVar = 0;

	// Lights declaration

	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->setAmbient(globalAmbientLight);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1);
	light0->enable();
	
	light1 = new CGFlight(GL_LIGHT1, light1_pos);
	light1->setSpecular(yellow);
	light1->enable();

	light2 = new CGFlight(GL_LIGHT2, light2_pos);
	light2->setAmbient(cores1);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.3);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0);
	light2->enable();

	light3 = new CGFlight(GL_LIGHT3, light3_pos);
	light3->setSpecular(cores);
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 1);
	light3->enable();

	/*light4 = new CGFlight(GL_LIGHT4, light4_pos);
	light4->setAmbient(globalAmbientLight);
	light4->setSpecular(yellow);
	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 0);
	glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 1);
	glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0);
	light4->enable();*/

	glEnable(GL_NORMALIZE);

	//Declares materials
	defaultAppearance = new CGFappearance(ambClock, difClock, specClock,
			shininessClock);
	tennisAppearance = new CGFappearance(ambClock,difClock,specClock,shininessClock);
	tennisAppearance->setTexture("tennis.png");
	torusAppearance = new CGFappearance(ambClock,difClock,specClock,shininessClock);
	torusAppearance->setTexture("torus.png");
	tableAppearance = new CGFappearance(ambTable, difTable, specTable,
			shininessTable);
	tableAppearance->setTexture("table.png");
	floorAppearance = new CGFappearance(ambFloor, difFloor, specFloor,
			shininessFloor);
	floorAppearance->setTexture("floor.png");
	floorAppearance->setTextureWrap(GL_CLAMP, GL_CLAMP);
	lampAppearance = new CGFappearance(ambLamp, difLamp, specLamp,
			shininessLamp);
	lampAppearance->setTexture("table.png");
	carpetAppearance = new CGFappearance(ambFloor,difFloor,specFloor,shininessFloor);
	carpetAppearance->setTexture("carpet.png");
	fagotaAppearance = new CGFappearance(ambBoard,difBoard,specBoard,shininessBoard);
	fagotaAppearance->setTexture("metal.png");
	laigAppearance = new CGFappearance(ambBoard,difBoard,specBoard,shininessBoard);
	laigAppearance->setTexture("laig.png");
	wallAppearance = new CGFappearance(ambFloor, difFloor, specFloor,
			shininessFloor);
	wallAppearance->setTexture("wall.png");
	
	//Declares scene elements
	table = new myTable();
	luzFagota1 = new myUnitCube();
	luzFagota2 = new myUnitCube();
	t1 = new Torus(8,25);
	wall = new Plane(1, 10, 12, 2, -0.5);
	windowWall = new WindowWall(3, 2.5, -0.75);
	lamp = new myLamp(30, 30);
	boardA = new Plane(BOARD_A_DIVISIONS, 1, 1, 1, 0);
	boardB = new Plane(BOARD_B_DIVISIONS, 1, 1, 1, 0);
	cylinder1 = new myCylinder(30, 30, 1);
	cylinder2 = new myCylinder(30, 30, 0);
	cilindro = gluNewQuadric();
	esfera = gluNewQuadric();
	em1 = gluNewQuadric();
	em2 = gluNewQuadric();
	em3 = gluNewQuadric();
	gluQuadricNormals(cilindro,GLU_SMOOTH);
	setUpdatePeriod(100);
}

void LightingScene::display() {

	// ---- BEGIN Background, camera and axis setup

	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin
	CGFscene::activeCamera->applyView();

	//light0->draw();
	light1->draw();
	light2->draw();
	light3->draw();
	//light4->draw();

	// Draw axis
	axis.draw();

	// ---- END Background, camera and axis setup

	// ---- BEGIN Primitive drawing section

	//Mesa, esta mesa usa o cubo que está definido na classe Casa Teste(nome estupido para a classe, eu sei xD). 
	//O cubo é unitario e é desenhado na origem (de -0.5 a 0.5)
	glPushMatrix();
	glTranslated(7.5,-0.5,6);
	tableAppearance->apply();
	table->draw();
	glPopMatrix();

	//Parte de cima do candeeiro
	glPushMatrix();
	glTranslated(13,3.6,6);
	glRotated(-90,1,0,0);
	glRotated(90,0,0,1);
	gluCylinder(cilindro, 1.1,0.3,1.0,200,200);
	glPopMatrix();

	//Cabo do candeeiro
	glPushMatrix();
	glTranslated(13,0,6);
	glRotated(-90,1,0,0);
	gluCylinder(esfera,0.1,0.1,3.4,10,10);
	glPopMatrix();

	//Carpete
	glPushMatrix();
	glTranslated(3.5,0.05,8);
	glRotated(-90,1,0,0);
	glScaled(8,4,1);
	carpetAppearance->apply();
	glBegin(GL_POLYGON);
	glTexCoord2d(0,0);
	glVertex2d(0,0);
	glTexCoord2d(1,0);
	glVertex2d(1,0);
	glTexCoord2d(1,1);
	glVertex2d(1,1);
	glTexCoord2d(0,1);
	glVertex2d(0,1);
	glEnd();
	glPopMatrix();
	
	//Chão
	glPushMatrix();

	floorAppearance->apply();
	glRotated(-90,0,0,1);
	glRotated(270,0,1,0);
	glScaled(15, 15,1);

	
	glBegin(GL_POLYGON);
	glTexCoord2d(0,0);
	glVertex2d(0,0);
	glTexCoord2d(1,0);
	glVertex2d(1,0);
	glTexCoord2d(1,1);
	glVertex2d(1,1);
	glTexCoord2d(0,1);
	glVertex2d(0,1);
	glEnd();
	glNormal3f(0.0,-1.0,0.0);
	glPopMatrix();

	//Parede 1(lado direito)
	wallAppearance->apply();
	glPushMatrix();
	glScaled(15, 10,1);
	glBegin(GL_POLYGON);
	glTexCoord2d(0,0);
	glVertex2d(0,0);
	glTexCoord2d(1,0);
	glVertex2d(1,0);
	glTexCoord2d(1,1);
	glVertex2d(1,1);
	glTexCoord2d(0,1);
	glVertex2d(0,1);
	glEnd();
	glNormal3f(0.0,-1.0,0.0);
	glPopMatrix();

	//Parede 2(lado esquerdo)
	glPushMatrix();
	glTranslated(0,0,15);
	glRotated(90,0,1,0);
	glScaled(15, 10,1);
	glBegin(GL_POLYGON);
	glTexCoord2d(0,0);
	glVertex2d(0,0);
	glTexCoord2d(1,0);
	glVertex2d(1,0);
	glTexCoord2d(1,1);
	glVertex2d(1,1);
	glTexCoord2d(0,1);
	glVertex2d(0,1);
	glEnd();
	glNormal3f(0.0,-1.0,0.0);
	glPopMatrix();

	//Poster de LAIG
	glPushMatrix();
	glTranslated(2,6,0.1);
	glScaled(5,3,1);
	laigAppearance->apply();
	glBegin(GL_POLYGON);
	glTexCoord2d(0,0);
	glVertex2d(0,0);
	glTexCoord2d(1,0);
	glVertex2d(1,0);
	glTexCoord2d(1,1);
	glVertex2d(1,1);
	glTexCoord2d(0,1);
	glVertex2d(0,1);
	glEnd();
	glNormal3f(0.0,-1.0,0.0);
	glPopMatrix();

	//Luz da parede 1
	glPushMatrix();
	glTranslated(0.25,6,10);
	glRotated(90,0,1,0);
	glScaled(1,0.5,0.5);
	fagotaAppearance->apply();
	luzFagota1->draw();
	glPopMatrix();

	//Luz da parede 2
	glPushMatrix();
	glTranslated(10,6,0.25);
	glScaled(1,0.5,0.5);
	fagotaAppearance->apply();
	luzFagota2->draw();
	glPopMatrix();

	//Torus
	
	glPushMatrix();
	
	glTranslated(9.8,1,5);
	glColor3f(0.9, 0.3, 0.2); 
	glRotated(30,0,0,1);
	glRotated(60,0,1,0);
	
	glutSolidTorus(0.3,0.7,200,200);
	
	glPopMatrix();
	
	//esfera em cima da mesa(suposto ser uma bola de ténis)
	glPushMatrix();
	tennisAppearance->apply();
	
	//glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,10,10,0,GL_RGB, GL_UNSIGNED_BYTE,pixels);
	GLuint esferaText;
	glGenTextures( 1, &esferaText );
	glBindTexture(GL_TEXTURE_2D, 1);
	glTranslated(7.5,1.82,6);
	gluQuadricTexture(em1,GL_TRUE); 
	glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D,esferaText);
	gluSphere(em1,0.2,200,200);
	//gluDeleteQuadric(em1); 
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// ---- END Primitive drawing section

	glutSwapBuffers();
}

LightingScene::~LightingScene() {
	delete (light0);
	delete (light1);
	delete (light2);
	delete (light3);
	delete (light4);
	delete (table);
	delete (wall);
	delete (boardA);
	delete (boardB);
	delete(lamp);
	delete(windowWall);
}

void LightingScene::toggleSomething() {
}
