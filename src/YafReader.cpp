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

	TiXmlElement* yafElement = yafDocument->FirstChildElement("yaf");

	if (yafElement == NULL)
	{
		cout << "Main yaf block element not found! Exiting!\n";
		exit(1);
	}

	globalsElement = yafElement->FirstChildElement("globals");
	camerasElement = yafElement->FirstChildElement("cameras");
	lightingElement = yafElement->FirstChildElement("lighting");
	texturesElement = yafElement->FirstChildElement("textures");
	appearancesElement = yafElement->FirstChildElement("appearances");
	graphElement = yafElement->FirstChildElement("graph");


	//Globals tag parsing
	if (globalsElement == NULL)
	{
		cout << "Globals block element not found! Exiting!\n";
		exit(1);
	}
	else
	{
		cout << "Processing Globals block\n";

		char *background = NULL, *drawmode = NULL, *shading = NULL, *cullface = NULL, *cullorder = NULL;
		float backgroundR, backgroundG, backgroundB, backgroundAlpha;

		background = (char *) globalsElement->Attribute("background");

		if(background && sscanf(background,"%f %f %f %f",&backgroundR, &backgroundG, &backgroundB, &backgroundAlpha) == 4)
		{
			cout << "Background values: " << backgroundR << " " << backgroundG << " " << backgroundB << " " << backgroundAlpha <<  endl;
		}
		else
		{
			cout << "Error parsing the Background values" << endl;
			exit(1);
		}

		drawmode  =(char *) globalsElement->Attribute("drawmode");
		cout << "Drawmode value: " << drawmode << endl;

		shading  =(char *) globalsElement->Attribute("shading");
		cout << "Shading value: " << shading << endl;

		cullface  =(char *) globalsElement->Attribute("cullface");
		cout << "Cullface value: " << cullface << endl;

		cullorder  =(char *) globalsElement->Attribute("cullorder");
		cout << "Cullorder value: " << cullorder << endl;

	}

	printf ("-----------------------------------------\n");

	//Cameras tag parsing
	if (camerasElement == NULL)
	{
		cout << "Cameras block element not found! Exiting!\n";
		exit(1);
	}
	else
	{
		cout << "Processing Cameras block\n";

		char *initial = NULL;

		initial = (char *) camerasElement->Attribute("initial");

		cout << "Inital camera value: " << initial << endl;

		TiXmlElement* perspectiveElement = camerasElement->FirstChildElement();

		int i = 1;
		//Perspective tags parsing

		while(perspectiveElement)
		{
			if (strcmp(perspectiveElement->Value(),"perspective") == 0)
			{
				cout << "Processing Perspective block number " << i << "!" << endl;

				char *id = NULL, *pos = NULL, *target = NULL;
				float near, far, angle, posX, posY, posZ, targetX, targetY, targetZ;

				id = (char *) perspectiveElement->Attribute("id");

				cout << "Perspective id: " << id << endl;

				if (perspectiveElement->QueryFloatAttribute("near",&near)==TIXML_SUCCESS)
				{
					cout << "Near value: " << near << endl;
				}
				else
				{
					cout << "Error reading the Near value!Exiting" << endl;
					//exit(1);
				}

				if (perspectiveElement->QueryFloatAttribute("far",&far)==TIXML_SUCCESS)
				{
					cout << "Far value: " << far << endl;
				}
				else
				{
					cout << "Error reading the Far value!Exiting" << endl;
					//exit(1);
				}

				if (perspectiveElement->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS)
				{
					cout << "Angle value: " << angle << endl;
				}
				else
				{
					cout << "Error reading the Angle value!Exiting" << endl;
					//exit(1);
				}

				pos = (char *) perspectiveElement->Attribute("pos");

				if(pos && sscanf(pos,"%f %f %f",&posX, &posY, &posZ) == 3)
				{
					cout << "Position values: " << posX << " " << posY << " " << posZ <<  endl;
				}
				else
				{
					cout << "Error parsing the Position values" << endl;
					//exit(1);
				}

				target = (char *) perspectiveElement->Attribute("target");

				if(target && sscanf(target,"%f %f %f",&targetX, &targetY, &targetZ) == 3)
				{
					cout << "Target values: " << targetX << " " << targetY << " " << targetZ <<  endl;
				}
				else
				{
					cout << "Error parsing the Target values" << endl;
					//exit(1);
				}
			}

			i++;
			perspectiveElement = perspectiveElement->NextSiblingElement();
		}

		//Ortho tags processing

		i = 1;
		TiXmlElement* orthoElement = camerasElement->FirstChildElement("ortho");

		while(orthoElement)
		{
			if (strcmp(orthoElement->Value(),"ortho") == 0)
			{
				cout << "Processing Ortho block number " << i << "!" << endl;

				char *id = NULL;
				float near, far, left, right, top, bottom;

				id = (char *) orthoElement->Attribute("id");

				cout << "Id: " << id << endl;

				if (orthoElement->QueryFloatAttribute("near",&near)==TIXML_SUCCESS)
				{
					cout << "Near value: " << near << endl;
				}
				else
				{
					cout << "Error reading the Near value!Exiting" << endl;
					//exit(1);
				}

				if (orthoElement->QueryFloatAttribute("far",&far)==TIXML_SUCCESS)
				{
					cout << "Far value: " << far << endl;
				}
				else
				{
					cout << "Error reading the Far value!Exiting" << endl;
					//exit(1);
				}

				if (orthoElement->QueryFloatAttribute("left",&left)==TIXML_SUCCESS)
				{
					cout << "Left value: " << left << endl;
				}
				else
				{
					cout << "Error reading the Left value!Exiting" << endl;
					//exit(1);
				}

				if (orthoElement->QueryFloatAttribute("right",&right)==TIXML_SUCCESS)
				{
					cout << "Right value: " << right << endl;
				}
				else
				{
					cout << "Error reading the Right value!Exiting" << endl;
					//exit(1);
				}

				if (orthoElement->QueryFloatAttribute("top",&top)==TIXML_SUCCESS)
				{
					cout << "Top value: " << top << endl;
				}
				else
				{
					cout << "Error reading the Top value!Exiting" << endl;
					//exit(1);
				}

				if (orthoElement->QueryFloatAttribute("bottom",&bottom)==TIXML_SUCCESS)
				{
					cout << "Bottom value: " << bottom << endl;
				}
				else
				{
					cout << "Error reading the Bottom value!Exiting" << endl;
					//exit(1);
				}

				i++;
				orthoElement = orthoElement->NextSiblingElement();
			}
		}
	}

	printf ("-----------------------------------------\n");

	//Lighting tag processing

	if (lightingElement == NULL)
	{
		cout << "Lighting block element not found!Exiting" << endl;
		exit(1);
	}
	else
	{
		cout << "Processing Lighting block!" << endl;

		bool doublesided, local, enabled;
		char* ambient = NULL, *ds = NULL, *l = NULL, *e = NULL;
		float ambientR, ambientG, ambientB, ambientAlpha;

		ds = (char *) lightingElement->Attribute("doublesided");

		if (strcmp(ds,"true") == 0)
		{
			doublesided = true;
			cout << "Doublesided set as true!" << endl;
		}
		else if (strcmp(ds,"false") == 0)
		{
			doublesided = false;
			cout << "Doublesided set as false!" << endl;
		}
		else
		{
			cout << "Error processing the Doublesided attribute!Exiting!" << endl;
			//exit(1);
		}

		l = (char *) lightingElement->Attribute("local");

		if (strcmp(l,"true") == 0)
		{
			local = true;
			cout << "Local set as true!" << endl;
		}
		else if (strcmp(l,"false") == 0)
		{
			local = false;
			cout << "Local set as false!" << endl;
		}
		else
		{
			cout << "Error processing the Local attribute!Exiting!" << endl;
			//exit(1);
		}

		e = (char *) lightingElement->Attribute("enabled");

		if (strcmp(e,"true") == 0)
		{
			enabled = true;
			cout << "Lighting enabled!" << endl;
		}
		else if (strcmp(e,"false") == 0)
		{
			enabled = false;
			cout << "Lighting disabled!" << endl;
		}
		else
		{
			cout << "Error processing the Enabled attribute!Exiting!" << endl;
			//exit(1);
		}

		ambient = (char *) lightingElement->Attribute("ambient");

		if(ambient && sscanf(ambient,"%f %f %f %f",&ambientR, &ambientG, &ambientB, &ambientAlpha) == 4)
		{
			cout << "Ambient values: " << ambientR << " " << ambientG << " " << ambientB << " " << ambientAlpha << endl;
		}
		else
		{
			cout << "Error parsing the Ambient values" << endl;
			//exit(1);
		}

		//Omni tags processing

		int i = 1;
		TiXmlElement* omniElement = lightingElement->FirstChildElement("omni");

		while(omniElement)
		{
			if (strcmp(omniElement->Value(),"omni") == 0)
			{
				cout << "Processing Omni Light number " << i << "!" << endl;

				bool enabled;
				char *id = NULL, *e = NULL, *location = NULL, *ambient = NULL, *diffuse = NULL, *specular = NULL;
				float locationX, locationY, locationZ, ambientR, ambientG, ambientB, ambientAlpha, diffuseR, diffuseB,
					diffuseG, diffuseAlpha, specularR, specularG, specularB, specularAlpha;

				id = (char *) omniElement->Attribute("id");

				cout << "Id: " << id << endl;

				e = (char *) omniElement->Attribute("enabled");

				if (strcmp(e,"true") == 0)
				{
					enabled = true;
					cout << "Omni light number " << i << " enabled!" << endl;
				}
				else if (strcmp(e,"false") == 0)
				{
					enabled = false;
					cout << "Omni light number " << i << " disabled" << endl;
				}
				else
				{
					cout << "Error processing the Enabled attribute!Exiting!" << endl;
					//exit(1);
				}

				location = (char *) omniElement->Attribute("location");

				if(location && sscanf(location,"%f %f %f",&locationX, &locationY, &locationZ) == 3)
				{
					cout << "Location values: " << locationX << " " << locationY << " " << locationZ << endl;
				}
				else
				{
					cout << "Error parsing the Location values!Exiting!" << endl;
					//exit(1);
				}

				ambient = (char *) omniElement->Attribute("ambient");

				if(ambient && sscanf(ambient,"%f %f %f %f",&ambientR, &ambientG, &ambientB, &ambientAlpha) == 4)
				{
					cout << "Ambient values: " << ambientR << " " << ambientG << " " << ambientB << " " << ambientAlpha << endl;
				}
				else
				{
					cout << "Error parsing the Ambient values!Exiting!" << endl;
					//exit(1);
				}

				diffuse = (char *) omniElement->Attribute("diffuse");

				if(diffuse && sscanf(diffuse,"%f %f %f %f",&diffuseR, &diffuseG, &diffuseB, &diffuseAlpha) == 4)
				{
					cout << "Diffuse values: " << diffuseR << " " << diffuseG << " " << diffuseB << " " << diffuseAlpha << endl;
				}
				else
				{
					cout << "Error parsing the Diffuse values!Exiting!" << endl;
					//exit(1);
				}

				specular = (char *) omniElement->Attribute("specular");

				if(specular && sscanf(specular,"%f %f %f %f",&specularR, &specularG, &specularB, &specularAlpha) == 4)
				{
					cout << "Specular values: " << specularR << " " << specularG << " " << specularB << " " << specularAlpha << endl;
				}
				else
				{
					cout << "Error parsing the Specular values!Exiting!" << endl;
					//exit(1);
				}
			}

			i++;
			omniElement = omniElement->NextSiblingElement();
		}

		//Spot tags processing

		i = 1;
		TiXmlElement* spotElement = lightingElement->FirstChildElement("spot");

		while(spotElement)
		{
			if (strcmp(spotElement->Value(),"spot") == 0)
			{
				cout << "Processing Spot Light number " << i << "!" << endl;

				bool enabled;
				char * id = NULL, *e = NULL, *location = NULL, *ambient = NULL, *diffuse = NULL, *specular = NULL, *direction = NULL;
				float locationX, locationY, locationZ, ambientR, ambientG, ambientB, ambientAlpha, diffuseR, diffuseB,
					diffuseG, diffuseAlpha, specularR, specularG, specularB, specularAlpha, angle, exponent, directionX,
					directionY, directionZ;

				id = (char *) spotElement->Attribute("id");

				cout << "Id: " << id << endl;

				e = (char *) spotElement->Attribute("enabled");

				if (strcmp(e,"true") == 0)
				{
					enabled = true;
					cout << "Spot light number " << i << " enabled!" << endl;
				}
				else if (strcmp(e,"false") == 0)
				{
					enabled = false;
					cout << "Spot light number " << i << " disabled" << endl;
				}
				else
				{
					cout << "Error processing the Enabled attribute!Exiting!" << endl;
					//exit(1);
				}

				location = (char *) spotElement->Attribute("location");

				if(location && sscanf(location,"%f %f %f",&locationX, &locationY, &locationZ) == 3)
				{
					cout << "Location values: " << locationX << " " << locationY << " " << locationZ << endl;
				}
				else
				{
					cout << "Error parsing the Location values!Exiting!" << endl;
					//exit(1);
				}

				ambient = (char *) spotElement->Attribute("ambient");

				if(ambient && sscanf(ambient,"%f %f %f %f",&ambientR, &ambientG, &ambientB, &ambientAlpha) == 4)
				{
					cout << "Ambient values: " << ambientR << " " << ambientG << " " << ambientB << " " << ambientAlpha << endl;
				}
				else
				{
					cout << "Error parsing the Ambient values!Exiting!" << endl;
					//exit(1);
				}

				diffuse = (char *) spotElement->Attribute("diffuse");

				if(diffuse && sscanf(diffuse,"%f %f %f %f",&diffuseR, &diffuseG, &diffuseB, &diffuseAlpha) == 4)
				{
					cout << "Diffuse values: " << diffuseR << " " << diffuseG << " " << diffuseB << " " << diffuseAlpha << endl;
				}
				else
				{
					cout << "Error parsing the Diffuse values!Exiting!" << endl;
					//exit(1);
				}

				specular = (char *) spotElement->Attribute("specular");

				if(specular && sscanf(specular,"%f %f %f %f",&specularR, &specularG, &specularB, &specularAlpha) == 4)
				{
					cout << "Specular values: " << specularR << " " << specularG << " " << specularB << " " << specularAlpha << endl;
				}
				else
				{
					cout << "Error parsing the Specular values!Exiting!" << endl;
					//exit(1);
				}

				if (spotElement->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS)
				{
					cout << "Angle value: " << angle << endl;
				}
				else
				{
					cout << "Error reading the Angle value!Exiting" << endl;
					//exit(1);
				}

				if (spotElement->QueryFloatAttribute("exponent",&exponent)==TIXML_SUCCESS)
				{
					cout << "Exponent value: " << exponent << endl;
				}
				else
				{
					cout << "Error reading the Exponent value!Exiting" << endl;
					//exit(1);
				}

				direction = (char *) spotElement->Attribute("direction");

				if(direction && sscanf(direction,"%f %f %f",&directionX, &directionY, &directionZ) == 3)
				{
					cout << "Direction values: " << directionX << " " << directionY << " " << directionZ << endl;
				}
				else
				{
					cout << "Error parsing the Direction values!Exiting!" << endl;
					//exit(1);
				}
			}

			i++;
			spotElement = spotElement->NextSiblingElement();
		}
	}

	//Textures tag processing
}