#ifndef YAF_READER_H
#define YAF_READER_H

#include "tinyxml.h"
#include <math.h>
#include <iostream>
#include <string>
#include "Cena.h"
#include "Texture.h"
#include "Material.h"
#include "AmbientLight.h"
using namespace std;

class YafReader
{
public:
	YafReader(char* filename);
	~YafReader();
	Cena scene;
	
protected:
	char* findTextureById(char* id);
	TiXmlDocument* yafDocument;	
	TiXmlElement* globalsElement;
	TiXmlElement* camerasElement;
	TiXmlElement* lightingElement;
	TiXmlElement* texturesElement;
	TiXmlElement* appearancesElement;
	TiXmlElement* graphElement;
	TiXmlElement* animationElement;
	vector<Texture*> textures;
	vector<Material*> materials;
	vector< vector <char*>> noderefs_vec;
};

#endif