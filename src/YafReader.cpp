#include "YafReader.h"




char* YafReader::findTextureById(char* id)
{
	for (int i = 0; i < textures.size(); i++)
	{
		if (strcmp(textures[i]->getId(),id) == 0)
		{
			return textures[i]->getId();
		}
	}
}

Node* YafReader::findNodeById(char* id)
{
	for (int i = 0; i < graph.size(); i++)
	{
		if (strcmp(graph[i]->getId(),id) == 0)
		{
			return graph[i];
		}
	}

	return NULL;
}

YafReader::YafReader(char* filename)
{
	yafDocument = new TiXmlDocument(filename);
	glMatrixMode(GL_MODELVIEW);
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

		scene.setGlobals(backgroundR, backgroundG, backgroundB, backgroundAlpha, drawmode, shading, cullface, cullorder);
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

		vector<float> ambience(4);
		ambience.push_back(ambientR);
		ambience.push_back(ambientG);
		ambience.push_back(ambientB);
		ambience.push_back(ambientAlpha);
		Light *ambient_light = new Light(doublesided, local, enabled, ambience);

		scene.setAmbient(ambient_light);

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
					std::cout << "Error parsing the Ambient values!Exiting!" << endl;
					//exit(1);
				}

				diffuse = (char *) omniElement->Attribute("diffuse");

				if(diffuse && sscanf(diffuse,"%f %f %f %f",&diffuseR, &diffuseG, &diffuseB, &diffuseAlpha) == 4)
				{
					std::cout << "Diffuse values: " << diffuseR << " " << diffuseG << " " << diffuseB << " " << diffuseAlpha << endl;
				}
				else
				{
					std::cout << "Error parsing the Diffuse values!Exiting!" << endl;
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

				Omni* omni_light = new Omni(location_vec, ambient_vec, diffuse_vec, specular_vec, id, enabled);

				scene.addOmni(omni_light);
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

				Spot* spot_light = new Spot(location_vec, ambient_vec, diffuse_vec, specular_vec, direction_vec, id, enabled, angle, exponent);

				scene.addSpot(spot_light);
			}

			i++;
			spotElement = spotElement->NextSiblingElement();
		}
	}

	//Textures tag processing

	cout << endl<< "---------------------------------------" <<endl<< "Processing Textures block!" << endl;
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
			cout << "Processing texture number " << i << endl;
			char *id = (char *)textElement->Attribute("id");
			char *textFile = (char *)textElement->Attribute("file");

			cout << "Textures id: " << id << endl;

			cout << "File : " << textFile << endl;

			Texture* texture = new Texture(id, textFile);

			textures.push_back(texture);
		}
	}

	//Appearances tag processing

	cout << endl<< "---------------------------------------" <<endl<< "Processing Appearance block!" << endl;

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
			float textRef, textL_S, textL_T;

			id = (char *)appElement->Attribute("id");

			cout <<endl << endl << "Processing texture number " << i << ", id = " << id << endl;
			emissive = (char *)appElement->Attribute("emissive");
			ambient = (char *)appElement->Attribute("ambient");
			diffuse = (char *)appElement->Attribute("diffuse");
			specular = (char *)appElement->Attribute("specular");
			shininess = (char *)appElement->Attribute("shininess");
			textureref = (char *)appElement->Attribute("textureref");
			texlength_s = (char *)appElement->Attribute("texlength_s");
			texlength_t = (char *)appElement->Attribute("texlength_t");


			if(emissive && sscanf(emissive,"%f %f %f %f",&emA, &emB, &emC, &emD) == 4) 
				cout << "Emissive values: " << emA << " " << emB << " " << emC << " " << emD << endl;

			if(ambient && sscanf(ambient,"%f %f %f %f",&ambR, &ambG, &ambB, &ambAlpha) == 4) 
				cout << "Ambient values: " << ambR << " " << ambG << " " << ambB << " " << ambAlpha << endl;

			if(diffuse && sscanf(diffuse,"%f %f %f %f",&difA, &difB, &difC, &difD) == 4) 
				cout << "Diffuse values: " << difA << " " << difB << " " << difC << " " << difD << endl;

			if(specular && sscanf(specular,"%f %f %f %f",&specA, &specB, &specC, &specD) == 4) 
				cout << "Specular values: " << specA << " " << specB << " " << specC << " " << specD << endl;

			if(shininess && sscanf(shininess,"%f",&shin) == 1) 
				cout << "Shininess values: " <<shin << endl;

			textureref = (char *)appElement -> Attribute("textureref");



			if(texlength_s && sscanf(texlength_s,"%f",&textL_S) == 1) 
				cout << "Length_s value: " <<texlength_s << endl;

			if(texlength_t && sscanf(texlength_t,"%f",&textL_T) == 1) 
				cout << "Length_t value: " <<texlength_t << endl;

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

			Material *mat = new Material(id, emission, ambience, diff, spec, shin, textL_S, textL_S);

			if(textureref != NULL) 
			{
				//cout << "Texture reference: " << textureref << endl;

				for(int i = 0; i<textures.size() ; i++)

					if( strcmp(textures[i]->getId(), textureref) == 0) 
						{
							/*cout << "Textura : " << id << " -> " << textureref << endl;
							getchar();*/
							mat->setTexture(textures[i]);
							
					}


			}

			materials.push_back(mat);

		}
	}

	//Graph tag processing

	cout << endl<< "---------------------------------------" << endl;
	cout << "Processing Graph block!" << endl;

	if (graphElement == NULL)
	{
		cout << "Graph block element not found!Exiting" << endl;
		//exit(1);
	}
	else
	{
		char *rootId = NULL;
		rootId = (char *) graphElement->Attribute("rootid");
		cout << "Root id: " << rootId << endl;
		int i = 1;
		TiXmlElement* nodeElement = graphElement->FirstChildElement("node");
		Node *rt = new Node(rootId, true);
		//Node tags processing
		graph.push_back(rt);

		while(nodeElement)
		{
			char *nodeId = NULL;

			nodeId = (char *) nodeElement->Attribute("id");

			cout << "Processing Node number " << i << " id: " << nodeId << endl << endl;

			Node *nd = new Node(nodeId, false);

			//Children tags(transforms, appearances, primitives, etc.) processing



			TiXmlElement* childrenElemenent = nodeElement->FirstChildElement("transforms");

			if (childrenElemenent == NULL)
			{
				cout << "Failed to find transforms tag!Exiting!" << endl;
				//exit(1);
			}
			else
			{
				while(childrenElemenent)
				{
					
					if (strcmp(childrenElemenent->Value(), "transforms") == 0)
					{
						float m[16] = {0};
						glLoadIdentity();
						cout << "Processing the Transformations!" << endl << endl;

						//check which one is the first transform tag to appear and then process each transformation in the following while loop

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
									cout << "Translate values: " << translateX << " " << translateY << " " << translateZ << endl;
								}

								m[0] = 1; 
								m[1] = 0;
								m[2] = 0;
								m[3] = translateX;
								m[4] = 0;
								m[5] = 1;
								m[6] = 0;
								m[7] = translateY;
								m[8] = 0;
								m[9] = 0;
								m[10] = 1;
								m[11] = translateZ;
								m[12] = 0;
								m[13] = 0;
								m[14] = 0;
								m[15] = 1;
								
								glTranslatef(translateX, translateY, translateZ);

								

								
								//nd->translate(m);
								//Chamar função de translação aqui
							}

							if (strcmp(transformTypeElement->Value(),"rotate") == 0)
							{
								char *axis = NULL;
								float angle;
								float m[16];
								float pi = acos(-1.0);
								float deg2rad = pi / 180.0;

								axis = (char *) transformTypeElement->Attribute("axis");

								if ((strcmp(axis,"x") != 0) && (strcmp(axis,"y") != 0) && (strcmp(axis,"z") != 0))
								{
									cout << "Invalid input on the axis field!Exiting!" << endl;
									//exit(1);
								}

								if (transformTypeElement->QueryFloatAttribute("angle",&angle) == TIXML_SUCCESS)
								{
									cout << "Rotate Angle value: " << angle << endl;
								}
								else
								{
									cout << "Error processing the Rotate Angle value!Exiting!" << endl;
									//exit(1);
								}

								//site com as matrizes http://www.cprogramming.com/tutorial/3d/rotationMatrices.html
								if (strcmp(axis,"x") == 0)
								{
									if (angle > 0)
									{
										m[0] = 1;
										m[1] = 0;
										m[2] = 0;
										m[3] = 0;
										m[4] = 0;
										m[5] = cos(angle*deg2rad); 
										m[6] = sin(angle*deg2rad);
										m[7] = 0;
										m[8] = 0;
										m[9] = -sin(angle*deg2rad);
										m[10] = cos(angle*deg2rad);
										m[11] = 0;
										m[12] = 0;
										m[13] = 0;
										m[14] = 0;
										m[15] = 1;

										
									}
									else
									{
										m[0] = 1;
										m[1] = 0;
										m[2] = 0;
										m[3] = 0;
										m[4] = 0;
										m[5] = cos(angle*deg2rad); 
										m[6] = -sin(angle*deg2rad);
										m[7] = 0;
										m[8] = 0;
										m[9] = sin(angle*deg2rad);
										m[10] = cos(angle*deg2rad);
										m[11] = 0;
										m[12] = 0;
										m[13] = 0;
										m[14] = 0;
										m[15] = 1;
									}

									glRotatef(angle,1,0,0);
								}
								else if (strcmp(axis,"y") == 0)
								{

									if (angle > 0)
									{
										m[0] = cos(angle*deg2rad);
										m[1] = 0;
										m[2] = -sin(angle*deg2rad);
										m[3] = 0;
										m[4] = 0;
										m[5] = 1; 
										m[6] = 0;
										m[7] = 0;
										m[8] = sin(angle*deg2rad);
										m[9] = 0;
										m[10] = cos(angle*deg2rad);
										m[11] = 0;
										m[12] = 0;
										m[13] = 0;
										m[14] = 0;
										m[15] = 1;
									}
									else
									{
										m[0] = cos(angle*deg2rad);
										m[1] = 0;
										m[2] = sin(angle*deg2rad);
										m[3] = 0;
										m[4] = 0;
										m[5] = 1; 
										m[6] = 0;
										m[7] = 0;
										m[8] = -sin(angle*deg2rad);
										m[9] = 0;
										m[10] = cos(angle*deg2rad);
										m[11] = 0;
										m[12] = 0;
										m[13] = 0;
										m[14] = 0;
										m[15] = 1;
									}

									glRotatef(angle, 0, 1, 0);
								}
								else if (strcmp(axis,"z") == 0)
								{
									if (angle > 0)
									{
										m[0] = cos(angle*deg2rad);
										m[1] = sin(angle*deg2rad);
										m[2] = 0;
										m[3] = 0;
										m[4] = -sin(angle*deg2rad);
										m[5] = cos(angle*deg2rad); 
										m[6] = 0;
										m[7] = 0;
										m[8] = 0;
										m[9] = 0;
										m[10] = 1;
										m[11] = 0;
										m[12] = 0;
										m[13] = 0;
										m[14] = 0;
										m[15] = 1;
									}
									else
									{
										m[0] = cos(angle*deg2rad);
										m[1] = -sin(angle*deg2rad);
										m[2] = 0;
										m[3] = 0;
										m[4] = sin(angle*deg2rad);
										m[5] = cos(angle*deg2rad); 
										m[6] = 0;
										m[7] = 0;
										m[8] = 0;
										m[9] = 0;
										m[10] = 1;
										m[11] = 0;
										m[12] = 0;
										m[13] = 0;
										m[14] = 0;
										m[15] = 1;
									}
									glRotatef(angle, 0,0,1);
									
								}

								//Chamar função de rotação aqui

								//nd->rotate(m);
								
							}

							if (strcmp(transformTypeElement->Value(),"scale") == 0)
							{
								char *scale = NULL;
								float scaleX, scaleY, scaleZ;
								float m[16];

								scale = (char *) transformTypeElement->Attribute("factor");

								if(scale && sscanf(scale,"%f %f %f",&scaleX, &scaleY, &scaleZ) == 3) 
								{
									cout << "Scale values: " << scaleX << " " << scaleY << " " << scaleZ << endl;
								}

								m[0] = scaleX;
								m[1] = 0;
								m[2] = 0;
								m[3] = 0;
								m[4] = 0;
								m[5] = scaleY;
								m[6] = 0;
								m[7] = 0;
								m[8] = 0;
								m[9] = 0;
								m[10] = scaleZ;
								m[11] = 0;
								m[12] = 0;
								m[13] = 0;
								m[14] = 0;
								m[15] = 1;

								glScalef(scaleX, scaleY, scaleZ);	
								//nd->scale(m);
							}

							//Chamar função de escalamento aqui

							

							//nd->setMatrix(m);

							transformTypeElement = transformTypeElement->NextSiblingElement();
						}
						
						
						
						glGetFloatv(GL_MODELVIEW_MATRIX,m);
						nd->setMatrix(m);
					}

					if (strcmp(childrenElemenent->Value(),"appearanceref") == 0)
					{
						cout <<endl << "Processing the Appearance!" << endl << endl;

						char *id = NULL;

						id = (char *) childrenElemenent->Attribute("id");

						for(int i = 0; i<materials.size(); i++)
						{
							if( strcmp(materials[i]->getId(), id) == 0)
							{
								/*for(int j = 0; j<nd->getPrimitivas().size();j++)
									nd->getPrimitivas()[j]->setMaterial(materials[i]);*/

								nd->setMaterial(materials[i]);
							}

						}

						cout << "Appearance id: " << id << endl;
					}

					if (strcmp(childrenElemenent->Value(),"children") == 0)
					{
						cout <<endl << "Processing the Children!" << endl;

						TiXmlElement* childrenTypeElement = childrenElemenent->FirstChildElement();

						//Process each children child (all the several primitives and the noderefs) in the following while loop

						while(childrenTypeElement)
						{
							char *cullorder = (char*)malloc(sizeof(char) * 20);
							vector<float> data;
							if( strcmp(scene.getCullOrder(), "CW") == 0) cullorder = "CW";
							else cullorder = "CCW";

							if (strcmp(childrenTypeElement->Value(),"rectangle") == 0)
							{
								

								cout << endl << "Rectangle tag!" << endl;

								char *xy1 = NULL, *xy2 = NULL;
								float xy1X, xy1Y, xy2X, xy2Y;

								xy1 = (char *) childrenTypeElement->Attribute("xy1");

								if(xy1 && sscanf(xy1,"%f %f",&xy1X, &xy1Y) == 2) 
								{
									cout << "Xy1 values: " << xy1X << " " << xy1Y << endl;
								}

								xy2 = (char *) childrenTypeElement->Attribute("xy2");

								if(xy2 && sscanf(xy2,"%f %f",&xy2X, &xy2Y) == 2) 
								{
									cout << "Xy2 values: " << xy2X << " " << xy2Y << endl;
								}




								data.push_back(xy1X);
								data.push_back(xy1Y);
								data.push_back(xy2X);
								data.push_back(xy2Y);

								Rectangle *r = new Rectangle(data, cullorder);

								nd->addPrimitiva(r);


							}

							if (strcmp(childrenTypeElement->Value(),"triangle") == 0)
							{
								cout << endl << "Triangle tag!" << endl;

								char *xyz1 = NULL, *xyz2 = NULL, *xyz3 = NULL;
								float xyz1X, xyz1Y, xyz1Z, xyz2X, xyz2Y, xyz2Z, xyz3X, xyz3Y, xyz3Z;

								xyz1 = (char *) childrenTypeElement->Attribute("xyz1");

								if(xyz1 && sscanf(xyz1,"%f %f %f",&xyz1X, &xyz1Y, &xyz1Z) == 3) 
								{
									cout << "Xyz1 values: " << xyz1X << " " << xyz1Y << " " << xyz1Z << endl;
								}

								xyz2 = (char *) childrenTypeElement->Attribute("xyz2");

								if(xyz2 && sscanf(xyz2,"%f %f %f",&xyz2X, &xyz2Y, &xyz2Z) == 3) 
								{
									cout << "Xyz2 values: " << xyz2X << " " << xyz2Y << " " << xyz2Z << endl;
								}

								xyz3 = (char *) childrenTypeElement->Attribute("xyz3");

								if(xyz3 && sscanf(xyz3,"%f %f %f",&xyz3X, &xyz3Y, &xyz3Z) == 3) 
								{
									cout << "Xyz3 values: " << xyz3X << " " << xyz3Y << " " << xyz3Z << endl;
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

								Triangle *t = new Triangle(data, cullorder);

								nd->addPrimitiva(t);

							}

							if (strcmp(childrenTypeElement->Value(),"cylinder") == 0)
							{
								cout << endl << "Cylinder tag!" << endl;

								float base, top, height;
								int slices, stacks;

								if (childrenTypeElement->QueryFloatAttribute("base",&base) == TIXML_SUCCESS)
								{
									cout << "Cylinder Base value: " << base << endl;
								}
								else
								{
									cout << "Error processing the Cylinder Base value!Exiting!" << endl;
									//exit(1);
								}

								if (childrenTypeElement->QueryFloatAttribute("top",&top) == TIXML_SUCCESS)
								{
									cout << "Cylinder Top value: " << top << endl;
								}
								else
								{
									cout << "Error processing the Cylinder Top value!Exiting!" << endl;
									//exit(1);
								}

								if (childrenTypeElement->QueryFloatAttribute("height",&height) == TIXML_SUCCESS)
								{
									cout << "Cylinder Height value: " << height << endl;
								}
								else
								{
									cout << "Error processing the Cylinder Height value!Exiting!" << endl;
									//exit(1);
								}

								if (childrenTypeElement->QueryIntAttribute("slices",&slices) == TIXML_SUCCESS)
								{
									cout << "Cylinder Slices value: " << slices << endl;
								}
								else
								{
									cout << "Error processing the Cylinder Slices value!Exiting!" << endl;
									//exit(1);
								}

								if (childrenTypeElement->QueryIntAttribute("stacks",&stacks) == TIXML_SUCCESS)
								{
									cout << "Cylinder Stacks value: " << stacks << endl;
								}
								else
								{
									cout << "Error processing the Cylinder Stacks value!Exiting!" << endl;
									//exit(1);
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
								cout << endl << "Sphere tag!" << endl;
								
								float radius;
								int slices, stacks;

								if (childrenTypeElement->QueryFloatAttribute("radius",&radius) == TIXML_SUCCESS)
								{
									cout << "Sphere Radius value: " << radius << endl;
								}
								else
								{
									cout << "Error processing the Sphere Radius value!Exiting!" << endl;
									//exit(1);
								}

								if (childrenTypeElement->QueryIntAttribute("slices",&slices) == TIXML_SUCCESS)
								{
									cout << "Sphere Slices value: " << slices << endl;
								}
								else
								{
									cout << "Error processing the Sphere Slices value!Exiting!" << endl;
									//exit(1);
								}

								if (childrenTypeElement->QueryIntAttribute("stacks",&stacks) == TIXML_SUCCESS)
								{
									cout << "Sphere Stacks value: " << stacks << endl;
								}
								else
								{
									cout << "Error processing the Sphere Stacks value!Exiting!" << endl;
									//exit(1);
								}

								data.push_back(radius);
								data.push_back((float)slices);
								data.push_back((float)stacks);

								Sphere *s = new Sphere(data, cullorder);

								nd->addPrimitiva(s);
							}

							if (strcmp(childrenTypeElement->Value(),"torus") == 0)
							{
								cout << endl << "Torus tag!" << endl;
								float inner, outer;
								int slices, loops;

								if (childrenTypeElement->QueryFloatAttribute("inner",&inner) == TIXML_SUCCESS)
								{
									cout << "Torus Inner value: " << inner << endl;
								}
								else
								{
									cout << "Error processing the Torus Inner value!Exiting!" << endl;
									//exit(1);
								}

								if (childrenTypeElement->QueryFloatAttribute("outer",&outer) == TIXML_SUCCESS)
								{
									cout << "Torus Outer value: " << outer << endl;
								}
								else
								{
									cout << "Error processing the Torus Outer value!Exiting!" << endl;
									//exit(1);
								}

								if (childrenTypeElement->QueryIntAttribute("slices",&slices) == TIXML_SUCCESS)
								{
									cout << "Torus Slices value: " << slices << endl;
								}
								else
								{
									cout << "Error processing the Torus Slices value!Exiting!" << endl;
									//exit(1);
								}

								if (childrenTypeElement->QueryIntAttribute("loops",&loops) == TIXML_SUCCESS)
								{
									cout << "Torus Loops value: " << loops << endl;
								}
								else
								{
									cout << "Error processing the Torus Loops value!Exiting!" << endl;
									//exit(1);
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
								cout << endl << "Noderef tag!" << endl;

								char *id = NULL;

								id = (char *) childrenTypeElement->Attribute("id");

								/*Node *child = new Node(id, false);
								nd->addChild(child);*/

								//Vetor refs, contém o nome do nó na 1ª posição, e o id do noderef na 2ª
								vector <char*> refs;
								refs.push_back(nodeId);
								refs.push_back(id);

								//Vetor noderefs, contém todos os nodes que teem a tag noderef
								noderefs_vec.push_back(refs);

								cout << "Noderef id: " << id << endl;
							}

						
							

							childrenTypeElement = childrenTypeElement->NextSiblingElement();
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

	for (int i = 0; i < noderefs_vec.size(); i++)
	{
		//No que tem um noderef
		Node* no_referenciado = findNodeById(noderefs_vec[i][0]);

		//No do noderef
		Node* no_referencia = findNodeById(noderefs_vec[i][1]);

		

		//no_refenciado->setPrimitiva(no_referencia->getId(), no_referencia->getData(), no_referencia->getCullOrder());

		no_referenciado->addChild(no_referencia);

		
	}

	scene.setGraph(graph);
	cout << endl << "Terminated parsing the .yaf file!" << endl << "Press Enter key to exit..";

	for(int i  = 0;i<graph.size();i++) 
	{
		if(graph[i]->getParentId() == NULL && !graph[i]->isRoot())
		{
			for(int j = 0; j<graph.size();j++)
			{
				if(graph[j]->isRoot()) graph[j]->addChild(graph[i]);
			}
		}
	}


	/*for(int i = 0; i < graph.size(); i++)
	{
		cout <<  " NO : " <<graph[i]->getId()<< " -> " ; 
		if(graph[i]->getMaterial() != NULL)  cout << graph[i]->getMaterial()->getTexture()->getFilePath() << endl;
		else cout << "Nulo " << endl;
		getchar();
	}*/

	
}




YafReader::~YafReader()
{
	delete(yafDocument);
}