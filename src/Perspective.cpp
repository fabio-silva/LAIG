#include "Perspective.h"

Perspective::Perspective(char *id, float near, float far, float angle, vector<float> position, vector<float> target):Camera()
{
	this-> id = id;
	this->near = near;
	this->far = far;
	this->angle = angle;
	this->position = position;
	this->target = target;
}

void Perspective::render()
{
	glLoadIdentity();
	gluPerspective(angle,1280/720,near,far);
	glMatrixMode( GL_MODELVIEW);
	gluLookAt(position[0],position[1],position[2],target[0],target[1],target[2],0,1,0);
}