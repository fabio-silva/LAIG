#include "myTable.h"

void myTable::draw() {
	myCube = new CasaTeste();

	//tampo
	glPushMatrix();
	glTranslated(0, 2, 0);
	glScaled(3, 0.3, 3);
	myCube->draw();
	glPopMatrix();

	//perna 1
	glPushMatrix();
	glTranslated(1, 1.2, 1);
	glScaled(0.3, 1.5, 0.3);
	myCube->draw();
	glPopMatrix();

	//perna 2
	glPushMatrix();
	glTranslated(-1, 1.2, -1);
	glScaled(0.3, 1.5, 0.3);
	myCube->draw();
	glPopMatrix();

	//perna 3
	glPushMatrix();
	glTranslated(-1, 1.2, 1);
	glScaled(0.3, 1.5, 0.3);
	myCube->draw();
	glPopMatrix();

	//perna 4
	glPushMatrix();
	glTranslated(1, 1.2, -1);
	glScaled(0.3, 1.5, 0.3);
	myCube->draw();
	glPopMatrix();
}
