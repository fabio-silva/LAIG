#include "Perspective.h"

Perspective::Perspective(char *id, float near, float far, float angle,float position[3], float target[3])
{
	strcpy(this->id, id);
	this->near = near;
	this->far = far;
	this->angle = angle;
	memcpy(this->position, position, 3*sizeof(float));
	memcpy(this->target, target, 3*sizeof(float));
}