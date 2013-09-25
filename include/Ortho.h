#ifndef ORTHO_H
#define ORTHO_H
#include "Camera.h"

class Ortho:public Camera{

public:

	Ortho(char *id, float near, float far, float left, float right, float top, float bottom);

protected:

	float left, right, top, bottom;
};
#endif