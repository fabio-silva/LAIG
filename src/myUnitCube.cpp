#include "myUnitCube.h"

void myUnitCube::draw() {

	glPushMatrix();
	glTranslated(0, 0, -0.5);
	glRotated(180, 0, 1, 0); //tras
	glNormal3f(-1, 0, 0);
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0);
	glVertex2d(-0.5, -0.5);
	glTexCoord2d(1, 0);
	glVertex2d(0.5, -0.5);
	glTexCoord2d(1, 1);
	glVertex2d(0.5, 0.5);
	glTexCoord2d(0, 1);
	glVertex2d(-0.5, 0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.5, 0, 0);
	glRotated(90, 0, 1, 0);
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0);
	glVertex2d(-0.5, -0.5);
	glTexCoord2d(1, 0);
	glVertex2d(0.5, -0.5);
	glTexCoord2d(1, 1);
	glVertex2d(0.5, 0.5);
	glTexCoord2d(0, 1);
	glVertex2d(-0.5, 0.5);
	glEnd();
	glRotated(90, 0, 1, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.5, 0, 0);
	glRotated(-90, 0, 1, 0);
	glNormal3f(0, 0, -1);
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0);
	glVertex2d(-0.5, -0.5);
	glTexCoord2d(1, 0);
	glVertex2d(0.5, -0.5);
	glTexCoord2d(1, 1);
	glVertex2d(0.5, 0.5);
	glTexCoord2d(0, 1);
	glVertex2d(-0.5, 0.5);
	glEnd();
	glRotated(90, 0, 1, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.5, 0);
	glRotated(-90, 1, 0, 0);
	glNormal3f(0, -1, 0);
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0);
	glVertex2d(-0.5, -0.5);
	glTexCoord2d(1, 0);
	glVertex2d(0.5, -0.5);
	glTexCoord2d(1, 1);
	glVertex2d(0.5, 0.5);
	glTexCoord2d(0, 1);
	glVertex2d(-0.5, 0.5);
	glEnd();
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(0, -0.5, 0);
	glRotated(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0);
	glVertex2d(-0.5, -0.5);
	glTexCoord2d(1, 0);
	glVertex2d(0.5, -0.5);
	glTexCoord2d(1, 1);
	glVertex2d(0.5, 0.5);
	glTexCoord2d(0, 1);
	glVertex2d(-0.5, 0.5);
	glEnd();
	glNormal3f(0, 0, 1);
	glPopMatrix();*/
}
