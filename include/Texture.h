#ifndef TEXTURE_H
#define TEXTURE_H

#include "CGFtexture.h"

class Texture:public CGFtexture{

public:
	Texture(char* id, char* file_path);
	char* getId();
	char* getFilePath();

private:
	char* id;
	char* file_path;

};

#endif