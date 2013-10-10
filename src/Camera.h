#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <vector>
#include "GL\gl.h"
#include "glut.h"

using namespace std;

class Camera{

public:
	Camera();
	virtual void render() = 0;
};
#endif