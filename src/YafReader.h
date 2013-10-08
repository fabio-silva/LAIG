#ifndef YAF_READER_H
#define YAF_READER_H

#include "tinyxml.h"
#include <math.h>
#include <iostream>
#include <string>
#include "Grafo.h"
#include "Cena.h"
#include "Texture.h"
#include "Material.h"
#include "Node.h"
#include "Primitiva.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "Torus.h"
using namespace std;

class YafReader
{
public:

	YafReader(char* filename);
	~YafReader();
	Cena scene;
protected:

	char* findTextureById(char* id);
	Node* findNodeById(char* id);

	TiXmlDocument* yafDocument;	
	TiXmlElement* globalsElement;
	TiXmlElement* camerasElement;
	TiXmlElement* lightingElement;
	TiXmlElement* texturesElement;
	TiXmlElement* appearancesElement;
	TiXmlElement* graphElement;
	//Grafo graph;
	vector<Texture*> textures;
	vector<Material*> materials;
	vector< vector <char*>> noderefs_vec;
	vector<Node *> graph;
	
};

#endif