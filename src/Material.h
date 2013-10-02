#ifndef MATERIAL_H
#define MATERIAL_H
#include <vector>
#include "Texture.h"
using namespace std;

class Material{

public:
	Material(char *id, vector<float> emissive, vector<float> ambient, vector<float> diffuse, vector<float> specular, float shininess, int text_s, int text_t);
	void setTexture(Texture *t);
	char *getId();

protected:
	vector<float> emissive, ambient, diffuse, specular;
	float shininess;
	char *id, *textref;
	int text_s, text_t;
	Texture *text;
};
#endif