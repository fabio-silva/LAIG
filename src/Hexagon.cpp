#include "Hexagon.h"

Hexagon::Hexagon(char* cullorder,int piece_type)
{
	this->cullorder = cullorder;
	this->piece_type = piece_type;
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

	if (piece_type == 0)
	{
		t = new CGFtexture("wood.jpg");
	}
	else if (piece_type == 1)
	{
		t = new CGFtexture("blue.jpg");
	}
	else if (piece_type == 2)
	{
		t = new CGFtexture("red.jpg");
	}
}

void Hexagon::draw()
{
	t->apply();
	if (strcmp(cullorder,"CCW") == 0)
	{
		glBegin(GL_POLYGON);
		glVertex2d(-0.5, 0);
		glVertex2d(-0.25, -0.5);
		glVertex2d(0.25, -0.5);
		glVertex2d(0.5, 0);
		glVertex2d(0.25, 0.5);
		glVertex2d(-0.25, 0.5);
		glEnd();
	}
	else if (strcmp(cullorder,"CW") == 0)
	{
		glBegin(GL_POLYGON);
		glVertex2d(-0.5, 0);
		glVertex2d(-0.25, 0.5);
		glVertex2d(0.25, 0.5);
		glVertex2d(0.5, 0);
		glVertex2d(0.25, -0.5);
		glVertex2d(-0.25, -0.5);
		glEnd();
	}
}