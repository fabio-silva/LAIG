#include "Material.h"
#include <iostream>
Material::Material(char *id, vector<float> emissive, vector<float> ambient, vector<float> diffuse, vector<float> specular, float shininess, int text_s, int text_t)
{
		
		this->id = id;
		this->emissive = emissive;
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->shininess = shininess;
		this->textref = textref;
		this->text_s = text_s;
		this->text_t = text_t;

		
	
}

void Material::setTexture(Texture *t)
{
	text = t;

	if(t != NULL) 
		{
			
			textura = new CGFtexture(t->getFilePath());
	}

}

char *Material::getId()
{
	return id;
}


void Material::apply()
{
	
 
	 glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &emissive[0]);
	 glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &diffuse[0]);
	 glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);
	 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &specular[0]);
  
	 

	// t->loadTexture(text->getFilePath());
	 //cout << "A aplicar textura " << textura->name() <<endl;
	 textura->apply();
 
     
}

Texture *Material::getTexture()
{
	return text;
}

int Material::get_s()
{
	return text_s;
}

int Material::get_t()
{
	return text_t;
}

vector<float> Material::getAmbient()
{
	return ambient;

}

vector<float> Material::getDiffuse()
{
	return diffuse;
}

float Material::getShininess()
{
	return shininess;
}

vector<float> Material::getEmissive()
{
	return emissive;
}

vector<float> Material::getSpecular()
{
	return specular;
}
