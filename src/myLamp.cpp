#include "myLamp.h"
#include "math.h"
#include "stdio.h"

myLamp::myLamp(int slices, int stacks) {
	this->slices = slices;
	this->stacks = stacks;
}

void myLamp::draw() {

	float pi = acos(-1.0);
	float deg2rad = pi / 180.0;
	float stept = 360.0 / slices;
	float stepp = 90 / stacks;
	float phi = 0;
	glPushMatrix();

	for (float theta = 0.0; theta < 360.0; theta += stept) {
		for (phi = 0; phi < 90; phi += stepp) {
			glPushMatrix();
			glBegin(GL_POLYGON);
			glNormal3d(cos((phi + stepp) * deg2rad) * sin(theta * deg2rad),
					sin((phi + stepp) * deg2rad),
					cos((phi + stepp) * deg2rad) * cos(theta * deg2rad));
			glVertex3d(cos((phi + stepp) * deg2rad) * sin(theta * deg2rad),
					sin((phi + stepp) * deg2rad),
					cos((phi + stepp) * deg2rad) * cos(theta * deg2rad));

			glNormal3d(cos(phi * deg2rad) * sin(theta * deg2rad),
					sin(phi * deg2rad),
					cos(phi * deg2rad) * cos(theta * deg2rad));
			glVertex3d(cos(phi * deg2rad) * sin(theta * deg2rad),
					sin(phi * deg2rad),
					cos(phi * deg2rad) * cos(theta * deg2rad));

			glNormal3d(cos(phi * deg2rad) * sin((theta + stept) * deg2rad),
					sin(phi * deg2rad),
					cos(phi * deg2rad) * cos((theta + stept) * deg2rad));
			glVertex3d(cos(phi * deg2rad) * sin((theta + stept) * deg2rad),
					sin(phi * deg2rad),
					cos(phi * deg2rad) * cos((theta + stept) * deg2rad));

			glNormal3d(
					cos((phi + stepp) * deg2rad)
							* sin((theta + stept) * deg2rad),
					sin((phi + stepp) * deg2rad),
					cos((phi + stepp) * deg2rad)
							* cos((theta + stept) * deg2rad));
			glVertex3d(
					cos((phi + stepp) * deg2rad)
							* sin((theta + stept) * deg2rad),
					sin((phi + stepp) * deg2rad),
					cos((phi + stepp) * deg2rad)
							* cos((theta + stept) * deg2rad));
			glEnd();
			glPopMatrix();
		}

		if (phi == 90)
			phi = 0;
	}
	glPopMatrix();

}
