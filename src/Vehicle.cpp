#include "Vehicle.h"
GLfloat ctrlpoints[4][4][3] = {
	{{1.0, 1.0 , 3.0}, {2.0, 1.0, 1.0}, 
	 {3.0, 1.0, 1.0},  {4.0, 1.0, 3.0}},

	{{1.0, 1.0, 4.0}, {2.0, 1.0, 2.0}, 
	 {3.0, 1.0, 2.0}, {4.0, 1.0, 4.0}}, 

	{{1.0, 1.0, 5.0}, {2.0, 1.0, 3.0}, 
	 {3.0, 1.0, 3.0}, {4.0, 1.0, 5.0}}, 

	{{1.0, 1.0, 6.0}, {2.0, 1.0, 4.0}, 
	 {3.0, 1.0, 4.0}, {4.0, 1.0, 6.0}}
};


Vehicle::Vehicle(char *cullorder):Primitiva(data,cullorder)
{
	vector<float> defaultSettings(4,0.5);
	m = new Material(NULL,  defaultSettings, defaultSettings, defaultSettings, defaultSettings, 1, 1, 1, GL_FRONT_AND_BACK);
	m2 = new Material(NULL,  defaultSettings, defaultSettings, defaultSettings, defaultSettings, 1, 1, 1, GL_FRONT_AND_BACK);

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






}


void Vehicle::draw()
{
	glEnable(GL_TEXTURE_2D);
	m->setTexture(new Texture(NULL, "wood.jpg"));
	m2->setTexture(new Texture(NULL, "blue.jpg"));
	m->apply();
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,0, 1, 12, 4, &ctrlpoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);

	glPushMatrix();
	glScalef(0.3,0.3,0.3);
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

	glPopMatrix();

	m2->apply();
	//-----------Pano do balao
	glPushMatrix();
	glTranslatef(-3.5, 0.3, 5.0);
	glRotatef(-180, 1, 0, 0);
	glScalef(1.5,1.5,1.5);
	glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPopMatrix();


}


