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
#include "AmbientLight.h"
#include "Plane.h"
#include "LinearAnimation.h"
#include "WaterLine.h"
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
	void setGraph(vector<Node *> graph);
	~Cena();
	char *getCullOrder();
	void processNode(Node *n, Material *m);
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
	void initLists(Node *n, Material *m);
	void addAnim(LinearAnimation *l);

protected:
	float backR, backG, backB, backAlpha;
	char *drawmode, *shading, *cullface, *cullorder;
	AmbientLight *ambient_light;
	vector <Spot *> spots;
	vector <Omni *> omnis;
	CGFlight *light0;
	CGFaxis axis;
	vector<Node*> graph;
	vector <Camera*> scene_cameras;
	Camera* activeCamera;
	char* initialCameraId;
	vector<GLuint> indexes;
	Plane *p;
	vector<LinearAnimation *> anims;
	WaterLine *w;
};

#endif