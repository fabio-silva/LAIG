#ifndef LightingScene_H
#define LightingScene_H

#include "CGFscene.h"
#include "CGFappearance.h"
#include "myTable.h"
#include "CGFapplication.h"
#include "Plane.h"
#include "myCylinder.h"
#include "myLamp.h"
#include "WindowWall.h"
#include "CasaTeste.h"
#include "CGFaxis.h"
#include <math.h>
#include "Torus.h"
#include <iostream>
#include <fstream>

class LightingScene: public CGFscene {
public:
	void init();
	void display();
	void toggleSomething();

	int sceneVar;

	CGFlight* light0;
	CGFlight* light1;
	CGFlight* light2;
	CGFlight* light3;
	CGFlight* light4;

	myTable* table;
	Plane* wall;
	WindowWall* windowWall;
	Plane* boardA;
	Plane* boardB;
	myCylinder* cylinder1;
	myCylinder* cylinder2;
	myLamp* lamp;
	GLUquadricObj* cilindro;
	GLUquadricObj* esfera;
	GLUquadricObj* em1;
	GLUquadricObj* em2;
	GLUquadricObj* em3;
	myUnitCube* luzFagota1;
	myUnitCube* luzFagota2;
	Torus* t1;

	CGFappearance* defaultAppearance;
	CGFappearance* materialA;
	CGFappearance* materialB;
	CGFappearance* tableAppearance;
	CGFappearance* slidesAppearance;
	CGFappearance* boardAppearance;
	CGFappearance* clockAppearance;
	CGFappearance* floorAppearance;
	CGFappearance* lampAppearance;
	CGFappearance* windowAppearance;
	CGFappearance* robotAppearance;
	CGFappearance* carpetAppearance;
	CGFappearance* fagotaAppearance;
	CGFappearance* laigAppearance;
	CGFappearance* tennisAppearance;
	CGFappearance* torusAppearance;
	CGFappearance* wallAppearance;

	~LightingScene();
};

#endif
