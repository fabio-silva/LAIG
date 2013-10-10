#pragma once
#include "Primitiva.h"


class Torus:public Primitiva{
public:
	Torus(vector<float> data,char *cullorder);
	void draw();
	vector<float> getNormals();

protected:
	float theta1, phi1, theta2, phi2;
	float v0[3];
	float v1[3];
	float v2[3];
	float v3[3];
	float n0[3];
	float n1[3];
	float n2[3];
	float n3[3];
	float innerRadius;
	float outerRadius;

	vector< float*> vertices;
	vector< float*> normals;
	vector< float *> texturesV;
};