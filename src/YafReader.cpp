#include "YafReader.h"

YafReader::YafReader(char* filename)
{
	yafDocument = new TiXmlDocument(filename);

	bool loadSuccessful = yafDocument->LoadFile();

	if (loadSuccessful)
	{
		cout << "Loaded the file successfully!\n";
	}
	else
	{
		cout << "Error loading file!\n";
	}

	yafElement = yafDocument->FirstChildElement("yaf");

	
	if (yafElement == NULL)
	{
		cout << "Main yaf block element not found! Exiting!\n";
		exit(1);
	}

	globalsElement = yafDocument->FirstChildElement("globals");
	/*camerasElement = yafDocument->FirstChildElement("cameras");
	lightingElement = yafDocument->FirstChildElement("lighting");
	texturesElement = yafDocument->FirstChildElement("textures");
	appearancesElement = yafDocument->FirstChildElement("appearances");
	graphElement = yafDocument->FirstChildElement("graph");*/

	if (globalsElement = NULL)
	{
		cout << "Globals block element not found! Exiting!\n";
	}
	else
	{
		cout << "Processing globals block\n";

		TiXmlElement* backgroundElement = globalsElement->FirstChildElement("background");

		if (backgroundElement)
		{
			char *background, *backgroundR, *backgroundG, *backgroundB, *backgroundAlpha, *drawmode, *shading, *cullface, *cullorder;

			background = (char *) globalsElement->Attribute("background");

			if(background && sscanf(background,"%f %f %f %f",&backgroundR, &backgroundG, &backgroundB, &backgroundAlpha) == 4)
			{
				cout << "Background values: " << backgroundR << " " << backgroundG << " " << backgroundR << " " << backgroundAlpha <<  endl;
			}
			else
			{
				cout << "Error parsing the background values\n";
			}

			drawmode  =(char *) globalsElement->Attribute("drawmode");

			if(drawmode && sscanf(drawmode,"%s",&drawmode)==1)
			{
				cout << "Drawmode value: " << drawmode << endl;
			}
			else
			{
				cout << "Error parsing drawmode\n";
			}

			shading  =(char *) globalsElement->Attribute("shading");

			if(shading && sscanf(shading,"%s",&shading)==1)
			{
				cout << "Shading value: " << shading << endl;
			}
			else
			{
				cout << "Error parsing shading\n";
			}

			cullface  =(char *) globalsElement->Attribute("cullface");

			if(cullface && sscanf(cullface,"%s",&cullface)==1)
			{
				cout << "Cullface value: " << cullface << endl;
			}
			else
			{
				cout << "Error parsing cullface\n";
			}

			cullorder  =(char *) globalsElement->Attribute("cullorder");

			if(cullorder && sscanf(cullorder,"%s",&cullorder)==1)
			{
				cout << "Cullorder value: " << cullorder << endl;
			}
			else
			{
				cout << "Error parsing cullorder\n";
			}
		}
	}
}