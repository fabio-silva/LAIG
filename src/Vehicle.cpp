#include "Vehicle.h"



Vehicle::Vehicle(char *cullorder):Primitiva(data,cullorder)
{
	vector<float> defaultSettings(4,0.5);
	m = new Material(NULL,  defaultSettings, defaultSettings, defaultSettings, defaultSettings, 1, 1, 1, GL_FRONT_AND_BACK);
	

	vector<float> data;
	data.push_back(-BALLOON_SIDE/2.0);
	data.push_back(-BALLOON_SIDE/2.0);
	data.push_back(BALLOON_SIDE/2.0);
	data.push_back(BALLOON_SIDE/2.0);
	
	f1 = new Rectangle(data, cullorder, "flat");
	f2 = new Rectangle(data, cullorder, "flat");
	f3 = new Rectangle(data, cullorder, "flat");
	f4 = new Rectangle(data, cullorder, "flat");
	f5 = new Rectangle(data, cullorder, "flat");




	p = new Patch(3, 10, 10, "fill", "CCW");

	GLfloat controlPoints[16][3] = {
		{0.0,  10.0, 0.0},
		{5.0,  10.0, 0.0},
		{10.0, 10.0, 0.0},
		{15.0, 10.0, 0.0},

		{0.0,  10.0, 5.0},
		{5.0,  10.0, 5.0},
		{10.0, 10.0, 5.0},
		{15.0, 10.0, 5.0},

		{0.0,  10.0, 10.0},
		{5.0,  10.0, 10.0},
		{10.0, 10.0, 10.0},
		{15.0, 10.0, 10.0},

		{0.0,  10.0, 15.0},
		{5.0,  10.0, 15.0},
		{10.0, 10.0, 15.0},
		{15.0, 10.0, 15.0},


	};

	p->addControPoint(controlPoints[0]);
	p->addControPoint(controlPoints[1]);
	p->addControPoint(controlPoints[2]);
	p->addControPoint(controlPoints[3]);
	p->addControPoint(controlPoints[4]);
	p->addControPoint(controlPoints[5]);
	p->addControPoint(controlPoints[6]);
	p->addControPoint(controlPoints[7]);
	p->addControPoint(controlPoints[8]);
	p->addControPoint(controlPoints[9]);
	p->addControPoint(controlPoints[10]);
	p->addControPoint(controlPoints[11]);
	p->addControPoint(controlPoints[12]);
	p->addControPoint(controlPoints[13]);
	p->addControPoint(controlPoints[14]);
	p->addControPoint(controlPoints[15]);


}


void Vehicle::draw()
{
	glEnable(GL_TEXTURE_2D);
	m->setTexture(new Texture(NULL, "wood.jpg"));
	m->apply();
	
	
	//-----------------------Parte de baixo do balao----------------------
	glPushMatrix();
	
	glTranslatef(0, -9.0, 0);
	glScalef(0.2,0.3,0.2);

	glPushMatrix();
	glTranslatef(0, 0, BALLOON_SIDE/2.0);
	f1->draw();	
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -BALLOON_SIDE/2.0);
	f2->draw();	
	glPopMatrix();

	glPushMatrix();
	glTranslatef(BALLOON_SIDE/2.0, 0, 0);
	glRotatef(90, 0, 1, 0);
	f3->draw();	
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-BALLOON_SIDE/2.0, 0, 0);
	glRotatef(-180, 1, 0, 0);
	glRotatef(-90, 0, 1, 0);
	f4->draw();	
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -BALLOON_SIDE/2.0, 0);
	glRotatef(270, 1, 0, 0);
	f5->draw();	
	glPopMatrix();

	glPopMatrix();

	//-----------Cordas
	glLineWidth(1.0); 
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_LINES);
	glVertex3f(-1.0, -7.5, 1.0);
	glVertex3f(-0.7, -5.0, 0.8);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(-1.0, -7.5, -1.0);
	glVertex3f(-0.7, -5.0, -0.7);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(1.0, -7.5, -1.0);
	glVertex3f(0.7, -5.0, -0.7);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(1.0, -7.5, 1.0);
	glVertex3f(0.7, -5.0, 0.8);
	glEnd();

	glDisable(GL_COLOR_MATERIAL);

	//-----------Pano do balao
	/*glPushMatrix();
	glTranslatef(0.0, 5.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	glScalef(5.0,5.0,5.0);
	p->draw();
	glPopMatrix();*/

	
}


