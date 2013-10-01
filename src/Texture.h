#ifndef TEXTURE_H
#define TEXTURE_H

class Texture{
public:
	Texture(char* id, char* file_path);
	char* getId();
	char* getFilePath();
private:
	char* id;
	char* file_path;
};
#endif