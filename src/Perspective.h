#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H
#include "Camera.h"

class Perspective: public Camera{

public:

	Perspective(char *id, float near, float far, float angle,vector <float> position, vector<float> target);
	void render();

protected:
	char* id;
	float near, far,angle;
	vector <float> position;
	vector <float> target;
};
#endif