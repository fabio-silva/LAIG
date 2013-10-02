#include "Material.h"

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
	this->text = t;
}

char *Material::getId()
{
	return id;
}
