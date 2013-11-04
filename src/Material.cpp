#include "Material.h"

#include <iostream>

Material::Material(char *id, vector<float> emissive, vector<float> ambient, vector<float> diffuse, vector<float> specular, float shininess, int text_s, int text_t, GLenum cullface)
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
	this->cullface = cullface;
	text = NULL;
}

void Material::setTexture(Texture *t)
{
	text = t;

	if(t != NULL) textura = new CGFtexture(t->getFilePath());
	
	
}

char *Material::getId()
{
	return id;
}


void Material::apply()
{
	glMaterialfv(cullface, GL_AMBIENT, &ambient[0]);
	glMaterialfv(cullface, GL_EMISSION, &emissive[0]);
	glMaterialfv(cullface, GL_DIFFUSE, &diffuse[0]);
	glMaterialfv(cullface, GL_SHININESS, &shininess);
	glMaterialfv(cullface, GL_SPECULAR, &specular[0]);

	if(text != NULL ) textura->apply();
	
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
