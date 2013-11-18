#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <vector>
#include "GL\gl.h"
#include "glut.h"
#include <iostream>

using namespace std;

class Camera{

public:
	Camera(char *id);
	virtual void render() = 0;
	char *getId();
	string tipo;

protected:
	char *id;
	static const int conta_camaras = 0;
};
#endif