#include "Patch.h"

Patch::Patch(int order, int u, int v, char *compute, char *cullorder):Primitiva(data, cullorder)
{
	this->order = order;
	this->u = u;
	this->v = v;
	this->compute = compute;
	matrixPos = 0;

	ctrlPoints = (GLfloat **)malloc(sizeof(GLfloat*) * (order+1) * (order+1));
	for(int i = 0; i < (order+1)*(order+1); i++)
	{
		ctrlPoints[i] = (GLfloat *)malloc(sizeof(GLfloat) * 3);

		
	}


	/*	switch(order)
	{
	case 1:
	glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, 4, &ctrlPoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3);
	break;

	case 2:
	glEnable(GL_MAP2_NORMAL);
	glCullFace(GL_CW);
	glEnable(GL_AUTO_NORMAL);

	if(strcmp(cullorder, "CCW") == 0) glCullFace(GL_CCW);
	glMap2f(GL_MAP1_VERTEX_3, 0, 1, 3, 2, 0, 1, (u * 3) , 2, &ctrlPoints[0][0]);
	break;

	case 3:
	glEnable(GL_MAP2_NORMAL);
	glCullFace(GL_CW);
	glEnable(GL_AUTO_NORMAL);

	if(strcmp(cullorder, "CCW") == 0) glCullFace(GL_CCW);
	break;
	}*/


}

void Patch::addControPoint(GLfloat *ctrl)
{
	memcpy(ctrlPoints[matrixPos], ctrl, sizeof(GLfloat) * 3);
	matrixPos++;
}

void Patch::draw()
{
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 0, order + 1, 0, 1, 3, order + 1, &ctrlPoints[0][0]);

	glCullFace(GL_CW);
	glEnable(GL_AUTO_NORMAL);
	if(strcmp(cullorder, "CCW") == 0) glCullFace(GL_CCW);
	glEnable(GL_MAP2_NORMAL);

	glEnable(GL_MAP2_VERTEX_3);

	glMapGrid2f(u, 0, 1, v, 0, 1);
	glEvalMesh2(GL_FILL, 0, u, 0, v); //Trocar GL_MODE
}