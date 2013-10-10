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
	virtual void printTipo()
	{
		cout << "Tipo: basico " <<endl;
	}
	virtual vector<float> getNormals() = 0;

	vector<float> vertexNormal(float x, float y, float z)
 	 {
 	float norm = sqrt(x*x + y*y + z*z);

 	vector<float> normal;
 	if( x == 0) x = norm;
 	if( y == 0) y = norm;
 	if( z == 0) z = norm;

 	normal.push_back(x / norm);
 	normal.push_back(y / norm);
 	normal.push_back(z / norm);

 	return normal;

 }

protected:
	Material *material;
	vector<float> data;
	char *cullorder;

};