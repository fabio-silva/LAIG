#include "Triangle.h"

Triangle::Triangle(vector <float> data,  char *cullorder) : Primitiva(data,cullorder)
{
}

vector<float> Triangle::getNormals()
{
	vector<float> res;
	float normal_x = 0;
	float normal_y = 0;
	float normal_z = 0;

	normal_x = ((data[1] - data[4]) * (data[2] + data[5]) + ((data[4] - data[7]) * (data[5] + data[8])) + ((data[7] - data[1]) * (data[8] + data[2])));
	normal_y = ((data[2] - data[5]) * (data[0] + data[3]) + ((data[5] - data[8]) * (data[3] + data[6])) + ((data[8] - data[2]) * (data[6] + data[0])));
	normal_z = ((data[0] - data[3]) * (data[1] + data[4]) + ((data[3] - data[6]) * (data[4] + data[7])) + ((data[6] - data[0]) * (data[7] + data[1])));

	//Normalize

	float temp = (float) sqrt((normal_x * normal_x) + (normal_y * normal_y) + (normal_z * normal_z));

	normal_x /= temp;
	normal_y /= temp;
	normal_z /= temp;

	res.push_back(normal_x);
	res.push_back(normal_y);
	res.push_back(normal_z);

	return res;
}

void Triangle::draw()
{
	glBegin(GL_POLYGON);

	if(strcmp(cullorder, "CW") == 0)
	{
		glNormal3f(getNormals()[0], getNormals()[1], getNormals()[2]);
		glTexCoord2d(0.5, 1);
		glVertex3f(data[0], data[1], data[2]);

		glTexCoord2d(1, 0);
		glVertex3f(data[3], data[4], data[5]);

		glTexCoord2d(0, 0);
		glVertex3f(data[6], data[7], data[8]);
	}

	else
	{
		//glNormal3f(getNormals()[0], getNormals()[1], getNormals()[2]);
		glTexCoord2d(0, 0);
		glVertex3f(data[6], data[7], data[8]);
				
		glTexCoord2d(1, 0);
		glVertex3f(data[3], data[4], data[5]);

		glTexCoord2d(0.5, 1);
		glVertex3f(data[0], data[1], data[2]);


	}

	glEnd();
}

