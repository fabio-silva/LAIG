#include "Primitiva.h"

Primitiva::Primitiva(vector<float> data, char *cullorder)
{
	this->data = data;
	this->cullorder = cullorder;
	material = NULL;
}

void Primitiva::setMaterial(Material *m)
{
	material = m;
}

vector<float> Primitiva::getNormals()
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
	for (unsigned int i=0; i<data.size(); i++)
	{
		int j = (i+1)%data.size();

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