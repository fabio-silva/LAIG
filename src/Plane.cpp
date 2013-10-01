#include "Plane.h"
#include "myUnitCube.h"
#include <GL/glu.h>

Plane::Plane(void) {
	tMultiplier = 1;
	sMultiplier = 1;
	_numDivisions = 1;
	domain = 1;
	delta = 0;
}

Plane::Plane(int n, int s, int t, double domain, double delta) {
	_numDivisions = n;
	sMultiplier = s;
	tMultiplier = t;
	this->domain = domain;
	this->delta = delta;
}

Plane::~Plane(void) {
}

void Plane::draw() {
	glPushMatrix();
	glRotatef(180.0, 1, 0, 0);
	glTranslatef(-0.5, 0.0, -0.5);
	glScalef(1.0 / (double) _numDivisions, 1, 1.0 / (double) _numDivisions);
	glNormal3f(0, -1, 0);

	for (int bx = 0; bx < _numDivisions; bx++) {
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2d(((double) bx / _numDivisions) * sMultiplier,
				0 * tMultiplier);
		glVertex3f(bx, 0, 0);
		for (int bz = 0; bz < _numDivisions; bz++) {
			glTexCoord2d(((double) (bx + 1) / _numDivisions) * sMultiplier,
					((double) bz / _numDivisions) * tMultiplier);
			glVertex3f(bx + 1, 0, bz);
			glTexCoord2d(((double) bx / _numDivisions) * sMultiplier,
					((double) (bz + 1) / _numDivisions) * tMultiplier);
			glVertex3f(bx, 0, bz + 1);
		}
		glTexCoord2d(((double) (bx + 1) / _numDivisions) * sMultiplier,
				1 * tMultiplier);
		glVertex3d(bx + 1, 0, _numDivisions);

		glEnd();
	}
	glPopMatrix();

}
