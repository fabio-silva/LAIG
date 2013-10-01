#pragma once

#include "CGFobject.h"
#include "CasaTeste.h"

class myTable: public CGFobject {
public:
	void draw();
private:
	CasaTeste* myCube;
};

