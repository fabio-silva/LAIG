#pragma once

#include <stdio.h>
#include <GL/glu.h>
#include "Primitiva.h"

class Patch : public Primitiva{
public:
	Patch(int order, int u, int v, char *compute, char *cullorder);
	void addControPoint(GLfloat *ctrl);
	void draw();
	void setControlPoints(GLfloat ***ctrl);

protected:
	int order, u, v;
	char *compute;
	int iPos,jPos;

	GLfloat ***ctrlPoints;
};