#include "Primitiva.h"

Primitiva::Primitiva(vector<float> data, char *cullorder)
{
	this->data = data;
	this->cullorder = cullorder;
}

void Primitiva::setMaterial(Material *m)
{
	material = m;
}