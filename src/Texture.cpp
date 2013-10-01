#include "Texture.h"

Texture::Texture(char* id, char* file_path)
{
	this->id = id;
	this->file_path = file_path;
}

char* Texture::getId()
{
	return id;
}

char* Texture::getFilePath()
{
	return file_path;
}