#pragma once

#include "tinyxml.h"
#include <iostream>
#include <string>

using namespace std;

class YafReader
{
public:

	YafReader(char* filename);

protected:

	TiXmlDocument* yafDocument;
	
	TiXmlElement* yafElement;
	TiXmlElement* globalsElement;
	TiXmlElement* camerasElement;
	TiXmlElement* lightingElement;
	TiXmlElement* texturesElement;
	TiXmlElement* appearancesElement;
	TiXmlElement* graphElement;
};