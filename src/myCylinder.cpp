#include "myCylinder.h"
#include "math.h"
#include "stdio.h"

myCylinder::myCylinder(int slices, int stacks, bool smooth) {
	this->slices = slices;
	this->stacks = stacks;
	this->smooth = smooth;
}

void myCylinder::draw() {

	float pi = acos(-1.0);
	float deg2rad = pi / 180.0;
	float stepl = 360.0 / slices;
	float steph = 1.0 / stacks;

	glPushMatrix();
	glBegin(GL_POLYGON);
	for (float i = 0.0; i < 360.0; i = i + (stepl)) {
		glNormal3d(0, -1, 0);
		glTexCoord2d((cos(i * deg2rad) / 2) + 0.5,
				(sin(i * deg2rad) / 2) + 0.5);
		glVertex3d(sin(i * deg2rad), -0.5, cos(i * deg2rad));
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_POLYGON);
	for (float i = 0.0; i < 360.0; i = i + (stepl)) {
		glNormal3d(0, 1, 0);
		glTexCoord2d((cos(i * deg2rad) / 2) + 0.5,
				(sin(i * deg2rad) / 2) + 0.5);
		glVertex3d(sin(i * deg2rad), 0.5, cos(i * deg2rad));
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	if (smooth)
		for (float i = 0.0; i < 360.0; i = i + (stepl)) {
			for (float j = -0.5; j < 0.5; j += (steph)) {
				glPushMatrix();
				glBegin(GL_POLYGON);
				glNormal3d(sin((i + stepl) * deg2rad), 0,
						cos((i + stepl) * deg2rad));
				glVertex3d(sin((i + stepl) * deg2rad), j + steph,
						cos((i + stepl) * deg2rad));
				glNormal3d(sin(i * deg2rad), 0, cos(i * deg2rad));
				glVertex3d(sin(i * deg2rad), j + steph, cos(i * deg2rad));
				glNormal3d(sin(i * deg2rad), 0, cos(i * deg2rad));
				glVertex3d(sin(i * deg2rad), j, cos(i * deg2rad));
				glNormal3d(sin((i + stepl) * deg2rad), 0,
						cos((i + stepl) * deg2rad));
				glVertex3d(sin((i + stepl) * deg2rad), j,
						cos((i + stepl) * deg2rad));
				glEnd();
				glPopMatrix();
			}
		}
	else {
		for (float i = 0.0; i < 360.0; i = i + (stepl)) {
			for (float j = -0.5; j < 0.5; j += (steph)) {
				glPushMatrix();
				glBegin(GL_POLYGON);
				glNormal3d(sin((i + stepl) * deg2rad) / 2, j + steph / 2,
						cos((i + stepl) * deg2rad) / 2);
				glVertex3d(sin((i + stepl) * deg2rad), j + steph,
						cos((i + stepl) * deg2rad));
				glVertex3d(sin(i * deg2rad), j + steph, cos(i * deg2rad));
				glVertex3d(sin(i * deg2rad), j, cos(i * deg2rad));
				glVertex3d(sin((i + stepl) * deg2rad), j,
						cos((i + stepl) * deg2rad));
				glEnd();
				glPopMatrix();
			}
		}
	}
	glPopMatrix();

}
