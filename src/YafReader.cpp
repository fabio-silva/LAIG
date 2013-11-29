#include "YafReader.h"

YafReader::YafReader(char* filename)
{
	yafDocument = new TiXmlDocument(filename);
	glMatrixMode(GL_MODELVIEW);
	bool loadSuccessful = yafDocument->LoadFile();
	char *shading = NULL;
	char *background = NULL, *drawmode = NULL, *cullface = NULL, *cullorder = NULL;
	if (loadSuccessful)
	{
		cout << "Loaded the file successfully!\n";
	}
	else
	{
		cout << "Error loading file!\n";
		exit(1);
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
	animationElement = yafElement->FirstChildElement("animations");


	//Globals tag parsing
	if (globalsElement == NULL)
	{
		cout << "Globals block element not found! Exiting!\n";
		exit(1);
	}
	else
	{


		float backgroundR, backgroundG, backgroundB, backgroundAlpha;

		background = (char *) globalsElement->Attribute("background");

		if(background && sscanf(background,"%f %f %f %f",&backgroundR, &backgroundG, &backgroundB, &backgroundAlpha) == 4)
		{
		}
		else
		{
			cout << "Error parsing the Background values" << endl;
			exit(1);
		}

		drawmode  =(char *) globalsElement->Attribute("drawmode");

		shading  =(char *) globalsElement->Attribute("shading");

		cullface  =(char *) globalsElement->Attribute("cullface");

		cullorder  =(char *) globalsElement->Attribute("cullorder");

		scene.setGlobals(backgroundR, backgroundG, backgroundB, backgroundAlpha, drawmode, shading, cullface, cullorder);
	}


	//Cameras tag parsing
	if (camerasElement == NULL)
	{
		cout << "Cameras block element not found! Exiting!\n";
		exit(1);
	}
	else
	{
		bool hasCameras = false;
		char *initial = NULL;

		initial = (char *) camerasElement->Attribute("initial");

		scene.setInitialCameraId(initial);


		TiXmlElement* perspectiveElement = camerasElement->FirstChildElement();

		int i = 1;
		//Perspective tags parsing

		while(perspectiveElement)
		{
			if (strcmp(perspectiveElement->Value(),"perspective") == 0)
			{
				hasCameras = true;

				char *id = NULL, *pos = NULL, *target = NULL;
				float near_,far_, angle, posX, posY, posZ, targetX, targetY, targetZ;

				id = (char *) perspectiveElement->Attribute("id");


				if (perspectiveElement->QueryFloatAttribute("near",&near_)==TIXML_SUCCESS)
				{
				}
				else
				{
					cout << "Error reading the Near value!Exiting" << endl;
					exit(1);
				}

				if (perspectiveElement->QueryFloatAttribute("far",&far_)==TIXML_SUCCESS)
				{

				}
				else
				{
					cout << "Error reading the Far value!Exiting" << endl;
					exit(1);
				}

				if (perspectiveElement->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS)
				{
				}
				else
				{
					cout << "Error reading the Angle value!Exiting" << endl;
					exit(1);
				}

				pos = (char *) perspectiveElement->Attribute("pos");

				if(pos && sscanf(pos,"%f %f %f",&posX, &posY, &posZ) == 3)
				{
				}
				else
				{
					cout << "Error parsing the Position values" << endl;
					exit(1);
				}

				target = (char *) perspectiveElement->Attribute("target");

				if(target && sscanf(target,"%f %f %f",&targetX, &targetY, &targetZ) == 3)
				{
				}
				else
				{
					cout << "Error parsing the Target values" << endl;
					exit(1);
				}

				vector<float> position;
				vector<float> tar;

				position.push_back(posX);
				position.push_back(posY);
				position.push_back(posZ);

				tar.push_back(targetX);
				tar.push_back(targetY);
				tar.push_back(targetZ);



				Perspective* p = new Perspective(id,near_,far_,angle,position,tar);


				scene.addSceneCamera(p);


				if (strcmp(id,scene.getInitialCameraId()) == 0)	scene.setActiveCamera(p);


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
				hasCameras = true;

				char *id = NULL;
				float near_,far_, left, right, top, bottom;

				id = (char *) orthoElement->Attribute("id");


				if (orthoElement->QueryFloatAttribute("near",&near_)==TIXML_SUCCESS)
				{
				}
				else
				{
					cout << "Error reading the Near value!Exiting" << endl;
					exit(1);
				}

				if (orthoElement->QueryFloatAttribute("far",&far_)==TIXML_SUCCESS)
				{
				}
				else
				{
					cout << "Error reading the Far value!Exiting" << endl;
					exit(1);
				}

				if (orthoElement->QueryFloatAttribute("left",&left)==TIXML_SUCCESS)
				{
				}
				else
				{
					cout << "Error reading the Left value!Exiting" << endl;
					exit(1);
				}

				if (orthoElement->QueryFloatAttribute("right",&right)==TIXML_SUCCESS)
				{
				}
				else
				{
					cout << "Error reading the Right value!Exiting" << endl;
					exit(1);
				}

				if (orthoElement->QueryFloatAttribute("top",&top)==TIXML_SUCCESS)
				{
				}
				else
				{
					cout << "Error reading the Top value!Exiting" << endl;
					exit(1);
				}

				if (orthoElement->QueryFloatAttribute("bottom",&bottom)==TIXML_SUCCESS)
				{
				}
				else
				{
					cout << "Error reading the Bottom value!Exiting" << endl;
					exit(1);
				}

				Ortho* o = new Ortho(id,near_,far_,left,right,top,bottom);

				scene.addSceneCamera(o);


				if (strcmp(id,scene.getInitialCameraId()) == 0) scene.setActiveCamera(o);

				i++;
				orthoElement = orthoElement->NextSiblingElement();
			}
		}

		if(!hasCameras)
		{
			cout << "No Cameras found, exiting..." << endl;
			exit(1);
		}

	}


	//Lighting tag processing

	int nrlights = 0;
	vector<char*> ids;

	if (lightingElement == NULL)
	{
		cout << "Lighting block element not found!Exiting" << endl;
		exit(1);
	}
	else
	{
		bool hasLights = false;

		bool doublesided, local, enabled;
		char* ambient = NULL, *ds = NULL, *l = NULL, *e = NULL;
		float ambientR, ambientG, ambientB, ambientAlpha;

		ds = (char *) lightingElement->Attribute("doublesided");

		if (strcmp(ds,"true") == 0) doublesided = true;

		else if (strcmp(ds,"false") == 0) doublesided = false;

		else
		{
			cout << "Error processing the Doublesided attribute!Exiting!" << endl;
			exit(1);
		}

		l = (char *) lightingElement->Attribute("local");

		if (strcmp(l,"true") == 0) local = true;

		else if (strcmp(l,"false") == 0) local = false;

		else
		{
			cout << "Error processing the Local attribute!Exiting!" << endl;
			exit(1);
		}

		e = (char *) lightingElement->Attribute("enabled");

		if (strcmp(e,"true") == 0) enabled = true;

		else if (strcmp(e,"false") == 0) enabled = false;

		else
		{
			cout << "Error processing the Enabled attribute!Exiting!" << endl;
			exit(1);
		}

		ambient = (char *) lightingElement->Attribute("ambient");

		if(ambient && sscanf(ambient,"%f %f %f %f",&ambientR, &ambientG, &ambientB, &ambientAlpha) == 4)
		{
		}
		else
		{
			cout << "Error parsing the Ambient values" << endl;
			exit(1);
		}


		vector<float> ambience;
		ambience.push_back(ambientR);
		ambience.push_back(ambientG);
		ambience.push_back(ambientB);
		ambience.push_back(ambientAlpha);


		AmbientLight *ambient_light = new AmbientLight(doublesided, local, enabled, ambience);

		scene.setAmbient(ambient_light);

		//Omni tags processing

		int i = 1;
		TiXmlElement* omniElement = lightingElement->FirstChildElement("omni");

		while(omniElement)
		{
			if (strcmp(omniElement->Value(),"omni") == 0)
			{
				hasLights = true;

				bool enabled;
				char *id = NULL, *e = NULL, *location = NULL, *ambient = NULL, *diffuse = NULL, *specular = NULL;
				float locationX, locationY, locationZ, ambientR, ambientG, ambientB, ambientAlpha, diffuseR, diffuseB,
					diffuseG, diffuseAlpha, specularR, specularG, specularB, specularAlpha;

				id = (char *) omniElement->Attribute("id");

				ids.push_back(id);

				e = (char *) omniElement->Attribute("enabled");

				if (strcmp(e,"true") == 0) enabled = true;

				else if (strcmp(e,"false") == 0) enabled = false;

				else
				{
					cout << "Error processing the Enabled attribute!Exiting!" << endl;
					exit(1);
				}

				location = (char *) omniElement->Attribute("location");

				if(location && sscanf(location,"%f %f %f",&locationX, &locationY, &locationZ) == 3)
				{
				}
				else
				{
					cout << "Error parsing the Location values!Exiting!" << endl;
					exit(1);
				}

				ambient = (char *) omniElement->Attribute("ambient");

				if(ambient && sscanf(ambient,"%f %f %f %f",&ambientR, &ambientG, &ambientB, &ambientAlpha) == 4)
				{
				}
				else
				{
					cout << "Error parsing the Ambient values!Exiting!" << endl;
					exit(1);
				}

				diffuse = (char *) omniElement->Attribute("diffuse");

				if(diffuse && sscanf(diffuse,"%f %f %f %f",&diffuseR, &diffuseG, &diffuseB, &diffuseAlpha) == 4)
				{
				}
				else
				{
					cout << "Error parsing the Diffuse values!Exiting!" << endl;
					exit(1);
				}

				specular = (char *) omniElement->Attribute("specular");

				if(specular && sscanf(specular,"%f %f %f %f",&specularR, &specularG, &specularB, &specularAlpha) == 4)
				{
				}
				else
				{
					cout << "Error parsing the Specular values!Exiting!" << endl;
					exit(1);
				}

				vector<float> location_vec;
				location_vec.push_back(locationX);
				location_vec.push_back(locationY);
				location_vec.push_back(locationZ);

				vector<float> ambient_vec;
				ambient_vec.push_back(ambientR);
				ambient_vec.push_back(ambientG);
				ambient_vec.push_back(ambientB);
				ambient_vec.push_back(ambientAlpha);

				vector<float> diffuse_vec;
				diffuse_vec.push_back(diffuseR);
				diffuse_vec.push_back(diffuseG);
				diffuse_vec.push_back(diffuseB);
				diffuse_vec.push_back(diffuseAlpha);

				vector<float> specular_vec;
				specular_vec.push_back(specularR);
				specular_vec.push_back(specularG);
				specular_vec.push_back(specularB);
				specular_vec.push_back(specularAlpha);

				if(nrlights < 7)
				{
					Omni* omni_light = new Omni(location_vec, ambient_vec, diffuse_vec, specular_vec, id, enabled);

					switch(nrlights)
					{
					case 0:
						omni_light->setLightnr(GL_LIGHT0);
						break;
					case 1:
						omni_light->setLightnr(GL_LIGHT1);
						break;
					case 2:
						omni_light->setLightnr(GL_LIGHT2);
						break;
					case 3:
						omni_light->setLightnr(GL_LIGHT3);
						break;
					case 4:
						omni_light->setLightnr(GL_LIGHT4);
						break;
					case 5:
						omni_light->setLightnr(GL_LIGHT5);
						break;
					case 6:
						omni_light->setLightnr(GL_LIGHT6);
						break;
					case 7:
						omni_light->setLightnr(GL_LIGHT7);
						break;
					}
					scene.addOmni(omni_light);
					nrlights++;
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

				hasLights = true;

				bool enabled;
				char * id = NULL, *e = NULL, *location = NULL, *ambient = NULL, *diffuse = NULL, *specular = NULL, *direction = NULL;
				float locationX, locationY, locationZ, ambientR, ambientG, ambientB, ambientAlpha, diffuseR, diffuseB,
					diffuseG, diffuseAlpha, specularR, specularG, specularB, specularAlpha, angle, exponent, directionX,
					directionY, directionZ;

				id = (char *) spotElement->Attribute("id");

				ids.push_back(id);

				e = (char *) spotElement->Attribute("enabled");

				if (strcmp(e,"true") == 0) enabled = true;

				else if (strcmp(e,"false") == 0) enabled = false;

				else
				{
					cout << "Error processing the Enabled attribute!Exiting!" << endl;
					exit(1);
				}

				location = (char *) spotElement->Attribute("location");

				if(location && sscanf(location,"%f %f %f",&locationX, &locationY, &locationZ) == 3)
				{
				}
				else
				{
					cout << "Error parsing the Location values!Exiting!" << endl;
					exit(1);
				}

				ambient = (char *) spotElement->Attribute("ambient");

				if(ambient && sscanf(ambient,"%f %f %f %f",&ambientR, &ambientG, &ambientB, &ambientAlpha) == 4)
				{
				}
				else
				{
					cout << "Error parsing the Ambient values!Exiting!" << endl;
					exit(1);
				}

				diffuse = (char *) spotElement->Attribute("diffuse");

				if(diffuse && sscanf(diffuse,"%f %f %f %f",&diffuseR, &diffuseG, &diffuseB, &diffuseAlpha) == 4)
				{
				}
				else
				{
					cout << "Error parsing the Diffuse values!Exiting!" << endl;
					exit(1);
				}

				specular = (char *) spotElement->Attribute("specular");

				if(specular && sscanf(specular,"%f %f %f %f",&specularR, &specularG, &specularB, &specularAlpha) == 4)
				{
				}
				else
				{
					cout << "Error parsing the Specular values!Exiting!" << endl;
					exit(1);
				}

				if (spotElement->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS)
				{
				}
				else
				{
					cout << "Error reading the Angle value!Exiting" << endl;
					exit(1);
				}

				if (spotElement->QueryFloatAttribute("exponent",&exponent)==TIXML_SUCCESS)
				{
				}
				else
				{
					cout << "Error reading the Exponent value!Exiting" << endl;
					exit(1);
				}

				direction = (char *) spotElement->Attribute("direction");

				if(direction && sscanf(direction,"%f %f %f",&directionX, &directionY, &directionZ) == 3)
				{
				}
				else
				{
					cout << "Error parsing the Direction values!Exiting!" << endl;
					exit(1);
				}

				vector<float> location_vec;
				location_vec.push_back(locationX);
				location_vec.push_back(locationY);
				location_vec.push_back(locationZ);

				vector<float> ambient_vec;
				ambient_vec.push_back(ambientR);
				ambient_vec.push_back(ambientG);
				ambient_vec.push_back(ambientB);
				ambient_vec.push_back(ambientAlpha);

				vector<float> diffuse_vec;
				diffuse_vec.push_back(diffuseR);
				diffuse_vec.push_back(diffuseG);
				diffuse_vec.push_back(diffuseB);
				diffuse_vec.push_back(diffuseAlpha);

				vector<float> specular_vec;
				specular_vec.push_back(specularR);
				specular_vec.push_back(specularG);
				specular_vec.push_back(specularB);
				specular_vec.push_back(specularAlpha);

				vector<float> direction_vec;
				direction_vec.push_back(directionX);
				direction_vec.push_back(directionY);
				direction_vec.push_back(directionZ);

				if(nrlights < 7)
				{

					Spot* spot_light = new Spot(location_vec, ambient_vec, diffuse_vec, specular_vec, direction_vec, id, enabled, angle, exponent);

					switch(nrlights)
					{
					case 0:
						spot_light->setLightnr(GL_LIGHT0);
						break;
					case 1:
						spot_light->setLightnr(GL_LIGHT1);
						break;
					case 2:
						spot_light->setLightnr(GL_LIGHT2);
						break;
					case 3:
						spot_light->setLightnr(GL_LIGHT3);
						break;
					case 4:
						spot_light->setLightnr(GL_LIGHT4);
						break;
					case 5:
						spot_light->setLightnr(GL_LIGHT5);
						break;
					case 6:
						spot_light->setLightnr(GL_LIGHT6);
						break;
					case 7:
						spot_light->setLightnr(GL_LIGHT7);
						break;
					}
					scene.addSpot(spot_light);
					nrlights++;
				}
			}

			i++;
			spotElement = spotElement->NextSiblingElement();
		}

		if(!hasLights)
		{
			cout << "No lights found!Exiting..." << endl;
			exit(1);
		}

		for(unsigned int i = 0; i < ids.size(); i++)
			for(unsigned int j = i;j < ids.size(); j++)
				if(strcmp(ids[i],ids[j]) == 0 && i != j)
				{
					cout << "Same light id's : " << ids[i] << endl;
					exit(1);
				}
	}

	//Textures tag processing

	if(texturesElement == NULL)
	{
		cout << "Textures block element not found!Exiting" << endl;
		exit(1);
	}
	else
	{
		TiXmlElement* textElement = texturesElement->FirstChildElement("texture");

		for(int i = 1; textElement != NULL ; i++, textElement = textElement->NextSiblingElement())
		{
			char *id = (char *)textElement->Attribute("id");
			char *textFile = (char *)textElement->Attribute("file");

			Texture* texture = new Texture(id, textFile);

			textures.push_back(texture);
		}
	}

	//Appearances tag processing

	if(appearancesElement == NULL)
	{
		cout << "Appearance block element not found!Exiting" << endl;
		exit(1);
	}
	else
	{
		TiXmlElement* appElement = appearancesElement->FirstChildElement("appearance");

		for(int i = 1; appElement != NULL; appElement = appElement->NextSiblingElement(), i++)
		{
			char *id = NULL;
			char *emissive = NULL, *ambient = NULL, *diffuse = NULL, *specular = NULL;
			char *shininess = NULL, *textureref = NULL, *texlength_s = NULL, *texlength_t = NULL;

			float emA ,emB, emC, emD;
			float ambR, ambG, ambB, ambAlpha;
			float difA, difB, difC, difD;
			float specA, specB, specC, specD;
			float shin;
			float textL_S = 0, textL_T = 0;

			id = (char *)appElement->Attribute("id");

			emissive = (char *)appElement->Attribute("emissive");
			ambient = (char *)appElement->Attribute("ambient");
			diffuse = (char *)appElement->Attribute("diffuse");
			specular = (char *)appElement->Attribute("specular");
			shininess = (char *)appElement->Attribute("shininess");
			textureref = (char *)appElement->Attribute("textureref");
			texlength_s = (char *)appElement->Attribute("texlength_s");
			texlength_t = (char *)appElement->Attribute("texlength_t");


			if(emissive && sscanf(emissive,"%f %f %f %f",&emA, &emB, &emC, &emD) == 4) 
			{
			}

			if(ambient && sscanf(ambient,"%f %f %f %f",&ambR, &ambG, &ambB, &ambAlpha) == 4) 
			{
			}

			if(diffuse && sscanf(diffuse,"%f %f %f %f",&difA, &difB, &difC, &difD) == 4) 
			{
			}

			if(specular && sscanf(specular,"%f %f %f %f",&specA, &specB, &specC, &specD) == 4) 
			{
			}

			if(shininess && sscanf(shininess,"%f",&shin) == 1) 
			{
			}

			textureref = (char *)appElement -> Attribute("textureref");



			if(texlength_s && sscanf(texlength_s,"%f",&textL_S) == 1) 
			{
			}

			if(texlength_t && sscanf(texlength_t,"%f",&textL_T) == 1) 
			{
			}

			vector<float> emission, ambience, diff, spec;
			emission.push_back(emA);
			emission.push_back(emB);
			emission.push_back(emC);
			emission.push_back(emD);
			ambience.push_back(ambR);
			ambience.push_back(ambG);
			ambience.push_back(ambB);
			ambience.push_back(ambAlpha);
			diff.push_back(difA);
			diff.push_back(difB);
			diff.push_back(difC);
			diff.push_back(difD);
			spec.push_back(specA);
			spec.push_back(specB);
			spec.push_back(specC);
			spec.push_back(specD);

			GLenum clFace;
			if(strcmp(cullface, "front") == 0) clFace = GL_FRONT;
			else if(strcmp(cullface, "back") == 0) clFace = GL_BACK;
			else if(strcmp(cullface, "both") == 0) clFace = GL_FRONT_AND_BACK;
			else clFace = GL_NONE;

			Material *mat = new Material(id, emission, ambience, diff, spec, shin, textL_S, textL_S, clFace);

			bool textureFound = false;
			if(textureref != NULL) 
			{
				for(unsigned int i = 0; i<textures.size() ; i++)

					if( strcmp(textures[i]->getId(), textureref) == 0) 	
					{
						mat->setTexture(textures[i]);
						textureFound = true;
						break;
					}
			}

			if(!textureFound && textureref != NULL)
			{
				cout << "No texture " << textureref << ",referenced on Appearance " <<id <<", found.Exiting..." << endl;
				exit(1);
			}
			materials.push_back(mat);
		}
	}
}

YafReader::~YafReader()
{
	delete(yafDocument);
}