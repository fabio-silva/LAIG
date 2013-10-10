#include "Rectangle.h"


Rectangle::Rectangle(vector <float> data, char *cullorder, char* shading) : Primitiva(data, cullorder)
{
	this->shading = shading;
}

vector<float> Rectangle::getNormals()
{
	vector< vector<float> > vertices;
	vector<float> v1; v1.push_back(data[0]) ; v1.push_back(data[1]);v1.push_back(0);
	vector<float> v2; v2.push_back(data[2]) ; v2.push_back(data[1]);v2.push_back(0);
	vector<float> v3; v3.push_back(data[2]) ; v3.push_back(data[3]);v3.push_back(0);
	vector<float> v4; v4.push_back(data[2]) ; v4.push_back(data[0]);v4.push_back(0);

	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);

	vector<float> normal;
	float normal_x = 0;
	float normal_y = 0;
	float normal_z = 0;
	for (int i=0; i<4; i++)
	{
		int j = (i+1)%4;

		normal_x += (vertices[i][1] - vertices[j][1])
			*(vertices[i][2] + vertices[j][2]);
		normal_y += (vertices[i][2] - vertices[j][2])
			*(vertices[i][0] + vertices[j][0]);
		normal_z += (vertices[i][0] - vertices[j][0])
			*(vertices[i][1] + vertices[j][1]);
	}

	normal.push_back(normal_x);
	normal.push_back(normal_y);
	normal.push_back(normal_z);

	float l = sqrt(normal[0]*normal[0] + normal[1] * normal[1] + normal[2] * normal[2] );
	normal[0] /= l;
	normal[1] /= l;
	normal[2] /= l;

	return normal;
}

void Rectangle::draw()
{

	glBegin(GL_POLYGON);
	if(strcmp(cullorder, "CW") == 0 )
	{ 


		if(strcmp(shading, "flat")==0) glNormal3f(getNormals()[0],getNormals()[1],getNormals()[2]);
		glTexCoord2d(0,1);
		if(strcmp(shading,"gouraud") == 0)glNormal3f(0,0,-1);
		glVertex2d(data[0],data[3]);

		glTexCoord2d(1,1);
		if(strcmp(shading,"gouraud") == 0)glNormal3f(0,0,-1);
		glVertex2d(data[2], data[3]);

		glTexCoord2d(1,0);
		if(strcmp(shading,"gouraud") == 0)glNormal3f(0,0,-1);
		glVertex2d(data[2], data[1]);

		glTexCoord2d(0,0);
		if(strcmp(shading,"gouraud") == 0)glNormal3f(0,0,-1);
		glVertex2d(data[0], data[1]);

	}

	else 
	{


		if(strcmp(shading, "flat")==0) glNormal3f(getNormals()[0],getNormals()[1],getNormals()[2]);
		if(strcmp(shading,"gouraud") == 0)glNormal3f(0,0,1); //glNormal3f(vertexNormal(data[0],data[3],0)[0], vertexNormal(data[0],data[3],0)[1], vertexNormal(data[0],data[3],0)[2]);

		glTexCoord2d(0,1);
		//	
		glVertex2d(data[0],data[3]);

		if(strcmp(shading,"gouraud") == 0) glNormal3f(0,0,1);//glNormal3f(vertexNormal(data[0],data[1],0)[0], vertexNormal(data[0],data[1],0)[1], vertexNormal(data[0],data[1],0)[2]);

		glTexCoord2d(0,0);
		//glNormal3f(0,0,1);
		glVertex2d(data[0], data[1]); 
		if(strcmp(shading,"gouraud") == 0) glNormal3f(0,0,1);//glNormal3f(vertexNormal(data[2],data[1],0)[0], vertexNormal(data[2],data[1],0)[1], vertexNormal(data[2],data[1],0)[2]);

		glTexCoord2d(1,0);
		//glNormal3f(0,0,1);
		glVertex2d(data[2], data[1]);
		if(strcmp(shading,"gouraud") == 0)glNormal3f(0,0,1);// glNormal3f(vertexNormal(data[1],data[1],0)[0], vertexNormal(data[1],data[1],0)[1], vertexNormal(data[1],data[1],0)[2]);

		glTexCoord2d(1,1);
		//	glNormal3f(0,0,1);
		glVertex2d(data[2], data[3]);
	}

	glEnd();

}