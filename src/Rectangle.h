#pragma once
#include "Primitiva.h"


class Rectangle:public Primitiva{
public:
	Rectangle(vector<float> data, char *cullorder);
	void draw();
	void printTipo()
	{
		cout << "Tipo: rectangulo" << endl;
	}
};