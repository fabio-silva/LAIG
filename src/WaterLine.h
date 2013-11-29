#pragma once
#include "Plane.h"
#include "Primitiva.h"
#include "CGFshader.h"
#include "CGFtexture.h"


class WaterLine:public CGFshader, public Primitiva
{
public:
	WaterLine(char *frag, char *vert, char *bmp, char *text);
	virtual void bind(void);
	void draw();

protected:
	Plane *p;
	CGFtexture *bump, *texture;
	float time;
	GLint timeLoc;
	
};