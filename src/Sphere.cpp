#include "Sphere.h"

Sphere::Sphere(vector<float> data, char *cullorder):Primitiva(data, cullorder)
{
	obj = gluNewQuadric();


}

void Sphere::draw()
{

	gluQuadricDrawStyle(obj, GLU_FILL);
	gluQuadricTexture(obj, GL_TRUE);
	gluQuadricNormals(obj, GLU_SMOOTH);


	gluSphere(obj, (double)data[0], (int)data[1], (int)data[2]);
}
