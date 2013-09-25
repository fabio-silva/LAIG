#ifndef CENA_H
#define CENA_H

#include <GL/glui.h>

class Cena{

public:
	Cena();
	void setGlobals(float backR, float backG, float backB, float backAlpha, char *drawmode, char *shading, char *cullface, char *cullorder);
	void processa();
protected:
	float backR, backG, backB, backAlpha;
	char *drawmode, *shading, *cullface, *cullorder;


};

#endif