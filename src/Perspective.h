#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H
#include "Camera.h"
class Perspective: public Camera{

public:

	Perspective(char *id, float near, float far, float angle,float position[3], float target[3]);

protected:
	float angle;
	float position[3], target[3];
};
#endif