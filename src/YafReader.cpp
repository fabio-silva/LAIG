#include "YafReader.h"

Node* YafReader::findNodeById(char* id)
{

	for (unsigned int i = 0; i < graph.size(); i++)
		if (strcmp(graph[i]->getId(),id) == 0) return graph[i];


	return NULL;
}

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
				float near, far, angle, posX, posY, posZ, targetX, targetY, targetZ;

				id = (char *) perspectiveElement->Attribute("id");


				if (perspectiveElement->QueryFloatAttribute("near",&near)==TIXML_SUCCESS)
				{
				}
				else
				{
					cout << "Error reading the Near value!Exiting" << endl;
					exit(1);
				}

				if (perspectiveElement->QueryFloatAttribute("far",&far)==TIXML_SUCCESS)
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



				Perspective* p = new Perspective(id,near,far,angle,position,tar);


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
				float near, far, left, right, top, bottom;

				id = (char *) orthoElement->Attribute("id");


				if (orthoElement->QueryFloatAttribute("near",&near)==TIXML_SUCCESS)
				{
				}
				else
				{
					cout << "Error reading the Near value!Exiting" << endl;
					exit(1);
				}

				if (orthoElement->QueryFloatAttribute("far",&far)==TIXML_SUCCESS)
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

				Ortho* o = new Ortho(id,near,far,left,right,top,bottom);

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

	//Graph tag processing



	if (graphElement == NULL)
	{
		cout << "Graph block element not found!Exiting" << endl;
		exit(1);
	}
	else
	{
		char *rootId = NULL;
		rootId = (char *) graphElement->Attribute("rootid");
		int i = 1;
		TiXmlElement* nodeElement = graphElement->FirstChildElement("node");

		if(nodeElement == false)
		{
			cout << "No nodes found!Exiting..." << endl;
			exit(1);
		}

		while(nodeElement)
		{
			char *nodeId = NULL;
			char *displaylist = NULL;

			nodeId = (char *) nodeElement->Attribute("id");
			displaylist = (char *) nodeElement->Attribute("displaylist");



			Node *nd;

			if(strcmp(rootId, nodeId) == 0) nd = new Node(nodeId, true);

			else nd = new Node(nodeId, false);

			if(displaylist != NULL)
			{
				if(strcmp(displaylist, "true") == 0) nd->useDisplayList(true);
				cout << "No " << nodeId << "com lista" << endl;

			}


			TiXmlElement* childrenElemenent = nodeElement->FirstChildElement("transforms");

			if (childrenElemenent == NULL)
			{
				cout << "Failed to find transforms tag on Node " << nodeId << ",exiting!" << endl;
				exit(1);
			}
			else
			{
				while(childrenElemenent)
				{

					if (strcmp(childrenElemenent->Value(), "transforms") == 0)
					{
						float m[16] = {0};
						glLoadIdentity();


						TiXmlElement* transformTypeElement = childrenElemenent->FirstChildElement();

						while(transformTypeElement)
						{
							if (strcmp(transformTypeElement->Value(),"translate") == 0)
							{
								char *translate = NULL;
								float translateX, translateY, translateZ;


								translate = (char *) transformTypeElement->Attribute("to");

								if(translate && sscanf(translate,"%f %f %f",&translateX, &translateY, &translateZ) == 3) 
								{
								}


								glTranslatef(translateX, translateY, translateZ);
							}

							if (strcmp(transformTypeElement->Value(),"rotate") == 0)
							{
								char *axis = NULL;
								float angle;
								float pi = acos(-1.0);
								float deg2rad = pi / 180.0;

								axis = (char *) transformTypeElement->Attribute("axis");

								if ((strcmp(axis,"x") != 0) && (strcmp(axis,"y") != 0) && (strcmp(axis,"z") != 0))
								{
									cout << "Invalid input on the axis field on Node " << nodeId << ",exiting!" << endl;
									exit(1);
								}

								if (transformTypeElement->QueryFloatAttribute("angle",&angle) == TIXML_SUCCESS)
								{
								}
								else
								{
									cout << "Error processing the Rotate Angle value on Node " << nodeId << ",exiting!" << endl;
								}

								if (strcmp(axis,"x") == 0) glRotatef(angle,1,0,0);

								else if (strcmp(axis,"y") == 0) glRotatef(angle, 0, 1, 0);

								else if (strcmp(axis,"z") == 0) glRotatef(angle, 0,0,1);


							}

							if (strcmp(transformTypeElement->Value(),"scale") == 0)
							{
								char *scale = NULL;
								float scaleX, scaleY, scaleZ;

								scale = (char *) transformTypeElement->Attribute("factor");

								if(scale && sscanf(scale,"%f %f %f",&scaleX, &scaleY, &scaleZ) == 3) 
								{
								}

								glScalef(scaleX, scaleY, scaleZ);	
							}





							transformTypeElement = transformTypeElement->NextSiblingElement();
						}



						glGetFloatv(GL_MODELVIEW_MATRIX,m);
						nd->setMatrix(m);
					}

					if (strcmp(childrenElemenent->Value(),"appearanceref") == 0)
					{

						char *id = NULL;

						id = (char *) childrenElemenent->Attribute("id");

						for( unsigned int i = 0; i<materials.size(); i++)
							if( strcmp(materials[i]->getId(), id) == 0)	nd->setMaterial(materials[i]);




					}

					if (strcmp(childrenElemenent->Value(),"children") == 0)
					{

						TiXmlElement* childrenTypeElement = childrenElemenent->FirstChildElement();

						if(childrenTypeElement == NULL)
						{
							cout << "No children block found on Node" <<nodeId <<",exiting..." << endl;
							exit(1);
						}

						while(childrenTypeElement)
						{

							bool hasElement = false;
							vector<float> data;


							if (strcmp(childrenTypeElement->Value(),"rectangle") == 0)
							{


								hasElement = true;
								char *xy1 = NULL, *xy2 = NULL;
								float xy1X, xy1Y, xy2X, xy2Y;

								xy1 = (char *) childrenTypeElement->Attribute("xy1");

								if(xy1 && sscanf(xy1,"%f %f",&xy1X, &xy1Y) == 2) 
								{
								}

								xy2 = (char *) childrenTypeElement->Attribute("xy2");

								if(xy2 && sscanf(xy2,"%f %f",&xy2X, &xy2Y) == 2) 
								{
								}




								data.push_back((float)xy1X);
								data.push_back((float)xy1Y);
								data.push_back((float)xy2X);
								data.push_back((float)xy2Y);

								Rectangle *r = new Rectangle(data, cullorder, shading);

								nd->addPrimitiva(r);


							}

							if (strcmp(childrenTypeElement->Value(),"triangle") == 0)
							{
								hasElement = true;
								char *xyz1 = NULL, *xyz2 = NULL, *xyz3 = NULL;
								float xyz1X, xyz1Y, xyz1Z, xyz2X, xyz2Y, xyz2Z, xyz3X, xyz3Y, xyz3Z;

								xyz1 = (char *) childrenTypeElement->Attribute("xyz1");

								if(xyz1 && sscanf(xyz1,"%f %f %f",&xyz1X, &xyz1Y, &xyz1Z) == 3) 
								{
								}

								xyz2 = (char *) childrenTypeElement->Attribute("xyz2");

								if(xyz2 && sscanf(xyz2,"%f %f %f",&xyz2X, &xyz2Y, &xyz2Z) == 3) 
								{
								}

								xyz3 = (char *) childrenTypeElement->Attribute("xyz3");

								if(xyz3 && sscanf(xyz3,"%f %f %f",&xyz3X, &xyz3Y, &xyz3Z) == 3) 
								{
								}

								data.push_back(xyz1X);
								data.push_back(xyz1Y);
								data.push_back(xyz1Z);

								data.push_back(xyz2X);
								data.push_back(xyz2Y);
								data.push_back(xyz2Z);

								data.push_back(xyz3X);
								data.push_back(xyz3Y);
								data.push_back(xyz3Z);

								Triangle *t = new Triangle(data, cullorder, shading);

								nd->addPrimitiva(t);

							}

							if (strcmp(childrenTypeElement->Value(),"cylinder") == 0)
							{
								hasElement = true;

								float base, top, height;
								int slices, stacks;

								if (childrenTypeElement->QueryFloatAttribute("base",&base) == TIXML_SUCCESS)
								{
								}

								if (childrenTypeElement->QueryFloatAttribute("top",&top) == TIXML_SUCCESS)
								{
								}
								else
								{
									cout << "Error processing the Cylinder Top value on Node " << nodeId <<",exiting!" << endl;
									exit(1);
								}

								if (childrenTypeElement->QueryFloatAttribute("height",&height) == TIXML_SUCCESS)
								{
								}

								if (childrenTypeElement->QueryIntAttribute("slices",&slices) == TIXML_SUCCESS)
								{
								}

								if (childrenTypeElement->QueryIntAttribute("stacks",&stacks) == TIXML_SUCCESS)
								{
								}

								data.push_back(base);
								data.push_back(top);
								data.push_back(height);
								data.push_back((float)slices);
								data.push_back((float)stacks);

								Cylinder *c = new Cylinder(data, cullorder);

								nd->addPrimitiva(c);
							}

							if (strcmp(childrenTypeElement->Value(),"sphere") == 0)
							{
								hasElement = true;

								float radius;
								int slices, stacks;

								if (childrenTypeElement->QueryFloatAttribute("radius",&radius) == TIXML_SUCCESS)
								{
								}

								if (childrenTypeElement->QueryIntAttribute("slices",&slices) == TIXML_SUCCESS)
								{
								}

								if (childrenTypeElement->QueryIntAttribute("stacks",&stacks) == TIXML_SUCCESS)
								{
								}

								data.push_back(radius);
								data.push_back((float)slices);
								data.push_back((float)stacks);

								Sphere *s = new Sphere(data, cullorder);

								nd->addPrimitiva(s);
							}

							if (strcmp(childrenTypeElement->Value(),"torus") == 0)
							{
								hasElement = true;

								float inner, outer;
								int slices, loops;

								if (childrenTypeElement->QueryFloatAttribute("inner",&inner) == TIXML_SUCCESS)
								{
								}

								if (childrenTypeElement->QueryFloatAttribute("outer",&outer) == TIXML_SUCCESS)
								{
								}

								if (childrenTypeElement->QueryIntAttribute("slices",&slices) == TIXML_SUCCESS)
								{
								}

								if (childrenTypeElement->QueryIntAttribute("loops",&loops) == TIXML_SUCCESS)
								{
								}

								data.push_back(inner);
								data.push_back(outer);
								data.push_back((float)slices);
								data.push_back((float)loops);

								Torus *t = new Torus(data, cullorder);

								nd->addPrimitiva(t);
							}

							if (strcmp(childrenTypeElement->Value(),"noderef") == 0)
							{
								hasElement = true;
								char *id = NULL;

								id = (char *) childrenTypeElement->Attribute("id");


								//Vetor refs, contém o nome do nó na 1ª posição, e o id do noderef na 2ª
								vector <char*> refs;
								refs.push_back(nodeId);
								refs.push_back(id);

								//Vetor noderefs, contém todos os nodes que teem a tag noderef
								noderefs_vec.push_back(refs);

							}

							if (strcmp(childrenTypeElement->Value(),"plane") == 0)
							{
								hasElement = true;

								int parts;

								if (childrenTypeElement->QueryIntAttribute("parts",&parts) == TIXML_SUCCESS)
								{
									Plane *p = new Plane(parts);
									nd->addPrimitiva(p);
								}
							}

							if(strcmp(childrenTypeElement->Value(), "patch") == 0)
							{
								hasElement = true;
								int order, partsU, partsV;
								char *compute;

								if (childrenTypeElement->QueryIntAttribute("order",&order) == TIXML_SUCCESS &&
									childrenTypeElement->QueryIntAttribute("partsU",&partsU) == TIXML_SUCCESS &&
									childrenTypeElement->QueryIntAttribute("partsV",&partsV) == TIXML_SUCCESS)
								{
									compute = (char *) childrenTypeElement->Attribute("compute");

									Patch *p = new Patch(order, partsU, partsV, compute, cullorder);

									TiXmlElement* ctrlElement = childrenTypeElement->FirstChildElement();

									if (ctrlElement == NULL)
									{
										printf("Seu burro do caralho, poe pontos de controlo!\n");
										exit(1);
									}
									else
									{
										while(ctrlElement)
										{
											if (strcmp(ctrlElement->Value(),"controlpoint") == 0)
											{
												float x,y,z;

												if (ctrlElement->QueryFloatAttribute("x",&x) == TIXML_SUCCESS &&
													ctrlElement->QueryFloatAttribute("y",&y) == TIXML_SUCCESS &&
													ctrlElement->QueryFloatAttribute("z",&z) == TIXML_SUCCESS)
												{
													GLfloat point[] = {x,y,z};

													p->addControPoint(point);
												}
											}

											ctrlElement = ctrlElement->NextSiblingElement();
										}
									}
									nd->addPrimitiva(p);
								}


							}




							childrenTypeElement = childrenTypeElement->NextSiblingElement();

							if(!hasElement)
							{
								cout << "Children block empty on Node " << nodeId << ",exiting..." << endl;
								exit(1);
							}
						}


					}

					childrenElemenent = childrenElemenent->NextSiblingElement();
				}
			}

			i++;
			nodeElement = nodeElement->NextSiblingElement();

			graph.push_back(nd);
		}
	}


	for (unsigned int i = 0; i < noderefs_vec.size(); i++)
	{

		Node* no_referenciado = findNodeById(noderefs_vec[i][0]);


		Node* no_referencia = findNodeById(noderefs_vec[i][1]);


		if(no_referencia == NULL)
		{
			cout << "No node " << noderefs_vec[i][1] << ", referenced by " << noderefs_vec[i][0] <<", found.Exiting..." << endl;
			exit(1);
		}
		no_referenciado->addChild(no_referencia);



	}

	cout << endl << "Terminated parsing the .yaf file!" << endl ;

	scene.setGraph(graph);

}




YafReader::~YafReader()
{
	delete(yafDocument);
}