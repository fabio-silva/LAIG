#ifndef CENA_H
#define CENA_H

#include <GL/glui.h>
#include "CGFscene.h"
#include "CGFcamera.h"
#include "Light.h"
#include "Spot.h"
#include "Omni.h"
#include <math.h>

using namespace std;

class Cena:public CGFscene{

public:
	Cena();
	void setGlobals(float backR, float backG, float backB, float backAlpha, char *drawmode, char *shading, char *cullface, char *cullorder);
	void setAmbient(Light *ambient);
	void addSpot(Spot *spot);
	void addOmni(Omni* omni);
	void init();
	void display();
	~Cena();
protected:
	float backR, backG, backB, backAlpha;
	char *drawmode, *shading, *cullface, *cullorder;
	Light *ambient_light;
	vector <Spot *> spots;
	vector <Omni *> omnis;
	CGFlight* light0;
};

#endif