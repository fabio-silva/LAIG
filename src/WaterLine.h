#pragma once
#include "Plane.h"
#include "CGFshader.h"
#include "CGFtexture.h"


class WaterLine:public CGFshader
{
public:
	WaterLine();
	virtual void bind(void);
	void draw();

protected:
	Plane *p;
	CGFtexture *bump, *texture;
	
};