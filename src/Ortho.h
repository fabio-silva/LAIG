#ifndef ORTHO_H
#define ORTHO_H

#include "Camera.h"

class Ortho:public Camera{

public:
	Ortho(char *id, float near_, float far_, float left, float right, float top, float bottom);
	void render();

protected:
	char* id;
	float near_,far_,left, right, top, bottom;
};
#endif