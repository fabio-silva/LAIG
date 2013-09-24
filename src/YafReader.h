#ifndef YAF_READER_H
#define YAF_READER_H

#include "tinyxml.h"
#include <iostream>
#include <string>
#include "Grafo.h"
using namespace std;

class YafReader
{
public:

	YafReader(char* filename);
	~YafReader();
protected:

TiXmlDocument* yafDocument;
	
	TiXmlElement* globalsElement;
	TiXmlElement* camerasElement;
	TiXmlElement* lightingElement;
	TiXmlElement* texturesElement;
	TiXmlElement* appearancesElement;
	TiXmlElement* graphElement;

	Grafo graph;
};

#endif