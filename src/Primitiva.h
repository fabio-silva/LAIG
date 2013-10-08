#pragma once
#include <vector>
#include "Material.h"
#include "GL\gl.h"
#include "glut.h"

using namespace std;

class Primitiva{

public:
	Primitiva(vector<float> data, char *cullorder);
	virtual void draw() = 0;
	void setMaterial(Material *m);

protected:
	Material *material;
	vector<float> data;
	char *cullorder;

};