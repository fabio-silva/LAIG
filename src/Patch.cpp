#include "Patch.h"
Patch::Patch(int order, int u, int v, char *compute, char *cullorder):Primitiva(data, cullorder)
{
	this->order = order;
	this->u = u;
	this->v = v;
	this->compute = compute;
	iPos = 0;
	jPos = 0;

	ctrlPoints = (GLfloat ***)malloc(sizeof(GLfloat **) * (order+1));

	for (int i = 0 ;  i < (order+1); i++) 
	{
		ctrlPoints[i] = (GLfloat **)malloc(sizeof(GLfloat *) * (order+1));

		for (int j = 0; j < (order+1); j++)
			ctrlPoints[i][j] = (GLfloat *)malloc(sizeof(GLfloat) * 3);
	}





}

void Patch::addControPoint(GLfloat *ctrl)
{

	ctrlPoints[iPos][jPos] = ctrl;

	jPos++;

	if(jPos == (order + 1)) 
	{
		iPos++;
		jPos = 0;
	}

	
}

void Patch::draw()
{
	//glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, order+1, 0, 1, (order+1)*3, order+1, &ctrlpoints[0][0][0]);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 6, 4, &ctrlPoints[0][0][0]);
	glCullFace(GL_CW);
	glEnable(GL_AUTO_NORMAL);
	if(strcmp(cullorder, "CCW") == 0) glCullFace(GL_CCW);
	glEnable(GL_MAP2_NORMAL);

	glEnable(GL_MAP2_VERTEX_3);

	glMapGrid2f(u, 0.0, 1.0, v, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, u, 0, v); //Trocar GL_MODE

	/*for (int j = 0; j <= 8; j++) {
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 30; i++)
	glEvalCoord2f((GLfloat)i/30.0, (GLfloat)j/8.0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 30; i++)
	glEvalCoord2f((GLfloat)j/8.0, (GLfloat)i/30.0);
	glEnd();
	}*/

	//cout << ctrlPoints[1][1][0] << ", " << ctrlPoints[1][1][1] << ", " << ctrlPoints[1][1][2] << endl;
	//for(int i = 0 ; i < 2; i++) cout << "CTRL[i] = " << ctrlPoints[i][0][0] <<", " << ctrlPoints[i][0][1] << ", " << ctrlPoints[i][0][2] << endl;
}

void Patch::setControlPoints(GLfloat ***ctrl)
{
	ctrlPoints = ctrl;
}