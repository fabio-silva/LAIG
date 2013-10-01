#include "Torus.h"
#include <math.h>


Torus::Torus(int numc, int numt)
{
	this->numc = numc;
	this->numt = numt;
}
void Torus::draw()
{

	float pi = acos(-1.0);
	float deg2rad = pi / 180.0;

	int i, j, k;
	double s, t, x, y, z, twopi;

	twopi = 2 * (float)pi;
	for (i = 0; i < numc; i++) {
		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= numt; j++) {
			for (k = 1; k >= 0; k--) {
				s = (i + k) % numc + 0.5;
				t = j % numt;

				x = (1+.1*cos(s*twopi/numc))*cos(t*twopi/numt);
				y = (1+.1*cos(s*twopi/numc))*sin(t*twopi/numt);
				z = .1 * sin(s * twopi / numc);
				glVertex3f(x, y, z);
			}
		}
		glEnd();
	}
}