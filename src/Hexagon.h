#pragma once
#include "Primitiva.h"

class Hexagon{
public:
	Hexagon(char* cullorder, int piece_type);
	void draw();
private:
	char* cullorder;
	int piece_type;
	CGFtexture *t;
};