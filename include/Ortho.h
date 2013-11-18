#ifndef ORTHO_H
#define ORTHO_H

#include "Camera.h"

class Ortho:public Camera{

public:
	Ortho(char *id, float near, float far, float left, float right, float top, float bottom);
	void render();

protected:
	char* id;
	float near,far,left, right, top, bottom;
};
#endif