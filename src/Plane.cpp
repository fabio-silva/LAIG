#include "Plane.h"
#include <GL/glu.h>
#include "CGFtexture.h"

GLfloat ctrl_points[4][3] = {
	{0,1,0},
	{0,0,0},
	{1,1,0},
	{1,0,0}

};

GLfloat normal_points[4][3] = {
	{0,0,1},
	{0,0,1},
	{0,0,1},
	{0,0,1}
};

GLfloat text_points[4][2] = {

	{0,0},
	{0,1},
	{1,0},
	{1,1}


};

GLfloat color_points[4][4]={
	{0.0, 0.7, 0.7, 0.0},
	{0.0, 0.0, 0.7, 0.0},
	{0.0, 0.7, 0.0, 0.0},
	{0.7, 0.0, 0.0, 0.0}
};

Plane::Plane(int div):Primitiva(data,cullorder)
{
	

	divisions = div;
	

}

void Plane::draw()
{

	GLfloat em[] = {0.5, 0.5, 0.5, 0.5};
	GLfloat df[] = {0.5, 0.5, 0.5, 0.5};
	GLfloat sp[] = {0.5, 0.5, 0.5, 0.5};
	GLfloat am[] = {0.5, 0.5, 0.5, 0.5};
	GLfloat sh = 5.f;

	glMaterialfv(GL_NONE, GL_EMISSION, em);
	glMaterialfv(GL_NONE, GL_DIFFUSE, df);
	glMaterialfv(GL_NONE, GL_SHININESS, &sh);
	glMaterialfv(GL_NONE, GL_SPECULAR, sp);
	glMaterialfv(GL_NONE, GL_AMBIENT, am);

	//CGFtexture *t = new CGFtexture("bush.jpg");

	//glColor3f(1.0,1.0,1.0);
	//glEnable(GL_COLOR_MATERIAL);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2, 0.0, 1.0, 6, 2, &ctrl_points[0][0]);
	glMap2f(GL_MAP2_NORMAL, 0.0, 1.0, 3, 2, 0.0, 1.0, 6, 2, &normal_points[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2, &text_points[0][0]);
	//glMap2f(GL_MAP2_COLOR_4, 0.0, 1.0, 4, 2, 0.0, 1.0, 8, 2, &color_points[0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glEnable(GL_MAP2_COLOR_4);

	glMapGrid2f(divisions, 0.0, 1.0, divisions, 0.0, 1.0);

	//t->apply();

	//glScalef(15.0, 15.0, 15.0);

	//glRotatef(90, 1, 0 ,0);
	glEvalMesh2(GL_FILL, 0, divisions, 0, divisions);


}