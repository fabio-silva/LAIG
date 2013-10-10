#ifndef CENA_H
#define CENA_H

#include <GL/glui.h>
#include "Light.h"
#include "Spot.h"
#include "Omni.h"
#include "CGFlight.h"
#include "CGFaxis.h"
#include "Node.h"
#include "Camera.h"
#include "Perspective.h"
#include "Ortho.h"

using namespace std;
class Cena{

public:
	Cena();
	void setGlobals(float backR, float backG, float backB, float backAlpha, char *drawmode, char *shading, char *cullface, char *cullorder);
	void setAmbient(Light *ambient);
	void addSpot(Spot *spot);
	void addOmni(Omni* omni);
	void display();
	void init();
	void setGraph(vector<Node *> graph);
	~Cena();
	char *getCullOrder();
	void processNode(Node *n, Material *m);
	void calculateMatrixes(Node *n);
	void setInitialCameraId(char* initialCameraId);
	void addSceneCamera(Camera* camera);
	void setActiveCamera(Camera* camera);
	char* getInitialCameraId();

protected:
	float backR, backG, backB, backAlpha;
	char *drawmode, *shading, *cullface, *cullorder;
	Light *ambient_light;
	vector <Spot *> spots;
	vector <Omni *> omnis;
	CGFlight *light0;
	CGFaxis axis;
	vector<Node*> graph;
	vector <Camera*> scene_cameras;
	Camera* activeCamera;
	char* initialCameraId;
};

#endif