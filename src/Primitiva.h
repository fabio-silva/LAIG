#pragma once

#include <vector>

#include <math.h>

#include "Material.h"

#include "GL\gl.h"
#include "glut.h"
#include <iostream>

using namespace std;

class Primitiva{

public:
	Primitiva(vector<float> data, char *cullorder);
	virtual void draw() = 0;
	void setMaterial(Material *m);
	 vector<float> getNormals();

protected:
	Material *material;
	vector<float> data;
	char *cullorder;

};