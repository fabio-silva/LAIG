#include "Torus.h"
#define _USE_MATH_DEFINES
#include <math.h>



Torus::Torus(vector<float> data,char *cullorder):Primitiva(data ,cullorder)
{
	innerRadius = (float) data[0];
	outerRadius = (float) data[1];
}

void Torus::draw()
{

	for(int i = 0; i < (int)data[3]; i++) 
	{
		theta1 = (float)((float)i * 2.0 * M_PI / data[3]);
		theta2 = (float)((float)(i + 1) * 2.0 * M_PI / data[3]);

		for (int j = 0; j < data[2]; j++) 
		{
			phi1 = (float)((float)j * 2.0 * M_PI / data[2]);
			phi2 = (float)((float)(j + 1) * 2.0 * M_PI / data[2]);

			v0[0] = (float)(cos(theta1) * (outerRadius + innerRadius * cos(phi1)));
			v0[1] = (float)(-sin(theta1) * (outerRadius + innerRadius * cos(phi1)));
			v0[2] = (float)(innerRadius * sin(phi1));

			v1[0] = (float)(cos(theta2) * (outerRadius + innerRadius * cos(phi1)));
			v1[1] = (float)(-sin(theta2) * (outerRadius + innerRadius * cos(phi1)));
			v1[2] = (float)(innerRadius * sin(phi1));

			v2[0] = (float)(cos(theta2) * (outerRadius + innerRadius * cos(phi2)));
			v2[1] = (float)(-sin(theta2) * (outerRadius + innerRadius * cos(phi2)));
			v2[2] = (float)(innerRadius * sin(phi2));

			v3[0] = (float)(cos(theta1) * (outerRadius + innerRadius * cos(phi2)));
			v3[1] = (float)(-sin(theta1) * (outerRadius + innerRadius * cos(phi2)));
			v3[2] = (float)(innerRadius * sin(phi2));

			n0[0] = (float)(cos(theta1) * (cos(phi1)));
			n0[1] = (float)(-sin(theta1) * (cos(phi1)));
			n0[2] = (float)(sin(phi1));

			n1[0] = (float)(cos(theta2) * (cos(phi1)));
			n1[1] = (float)(-sin(theta2) * (cos(phi1)));
			n1[2] = (float)(sin(phi1));

			n2[0] = (float)(cos(theta2) * (cos(phi2)));
			n2[1] = (float)(-sin(theta2) * (cos(phi2)));
			n2[2] = (float)(sin(phi2));

			n3[0] = (float)(cos(theta1) * (cos(phi2)));
			n3[1] = (float)(-sin(theta1) * (cos(phi2)));
			n3[2] = (float)(sin(phi2));


			glBegin(GL_QUADS);
			glTexCoord2f(v3[0], v3[1]);
			glNormal3fv(n3);
			glVertex3fv(v3);

			glTexCoord2f(v2[0], v2[1]);
			glNormal3fv(n2);
			glVertex3fv(v2);


			glTexCoord2f(v1[0], v1[1]);
			glNormal3fv(n1);
			glVertex3fv(v1);


			glTexCoord2f(v0[0], v0[1]);
			glNormal3fv(n0);
			glVertex3fv(v0);

			glEnd();
		}
	}
}





vector<float>Torus::getNormals(){vector<float> res; return res;}