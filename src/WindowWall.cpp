#include "WindowWall.h"
#include <GL/glu.h>

WindowWall::WindowWall(void) {
	_numDivisions = 1;
	domain = 1;
	delta = 0;
}

WindowWall::WindowWall(int n, double domain, double delta) {
	_numDivisions = n;
	this->domain = domain;
	this->delta = delta;
}

WindowWall::~WindowWall(void) {
}

void WindowWall::draw() {
		glPushMatrix();
	glRotatef(180.0, 1, 0, 0);
	glTranslatef(-0.5, 0.0, -0.5);
	glScalef(1.0 / (double) _numDivisions, 1, 1.0 / (double) _numDivisions);
	glNormal3f(0, -1, 0);

	for (int bx = 0; bx < _numDivisions; bx++) {
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2d(((double) bx / _numDivisions) * domain + delta,
				0 * domain + delta);
		glVertex3f(bx, 0, 0);
		for (int bz = 0; bz < _numDivisions; bz++) {
			glTexCoord2d(((double) (bx + 1) / _numDivisions) * domain + delta,
					((double) bz / _numDivisions) * domain + delta);
			glVertex3f(bx + 1, 0, bz);
			glTexCoord2d(((double) bx / _numDivisions) * domain + delta,
					((double) (bz + 1) / _numDivisions) * domain + delta);
			glVertex3f(bx, 0, bz + 1);
		}
		glTexCoord2d(((double) (bx + 1) / _numDivisions) * domain + delta,
				1 * domain + delta);
		glVertex3d(bx + 1, 0, _numDivisions);

		glEnd();
	}
	glPopMatrix();
}
