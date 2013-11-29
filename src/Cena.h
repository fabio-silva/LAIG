#ifndef CENA_H
#define CENA_H

#include <GL/glui.h>
#include "CGFappearance.h"
#include "Client.h"
#include "Light.h"
#include "Spot.h"
#include "Omni.h"
#include "CGFaxis.h"
#include "Camera.h"
#include "Perspective.h"
#include "Ortho.h"
#include "AmbientLight.h"
#include "Hexagon.h"
using namespace std;

class Cena{

public:
	Cena();
	void setGlobals(float backR, float backG, float backB, float backAlpha, char *drawmode, char *shading, char *cullface, char *cullorder);
	void setAmbient(AmbientLight *ambient);
	void addSpot(Spot *spot);
	void addOmni(Omni* omni);
	void display();
	void init();
	~Cena();
	char *getCullOrder();
	void setInitialCameraId(char* initialCameraId);
	void addSceneCamera(Camera* camera);
	void setActiveCamera(Camera *c);
	char* getInitialCameraId();
	vector <Camera*> getCameras();
	vector<Spot *> getSpots();
	vector<Omni *> getOmnis();
	char *getCullFace();
	void setDrawMode(char *drawmode);
	char *getDrawMode();
	void setDatas(vector<string> datas);
	bool isGameStarting();

protected:
	float backR, backG, backB, backAlpha;
	char *drawmode, *shading, *cullface, *cullorder;
	AmbientLight *ambient_light;
	vector <Spot *> spots;
	vector <Omni *> omnis;
	CGFaxis axis;
	vector <Camera*> scene_cameras;
	Camera* activeCamera;
	char* initialCameraId;
	bool gameBeginning;
	vector<string> datas;
	Hexagon* blank_hexa;
	Hexagon* p1_hexa;
	Hexagon* p2_hexa;
};

#endif