#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>
#include "Texture.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include "CGFtexture.h"
#include "GL\gl.h"
using namespace std;

class Material{

public:
	Material(char *id, vector<float> emissive, vector<float> ambient, vector<float> diffuse, vector<float> specular, float shininess, int text_s, int text_t, GLenum cullface);
	void setTexture(Texture *t);
	char *getId();
	void apply();
	Texture *getTexture();
	int get_s();
	int get_t();
	vector<float> getEmissive();
	vector<float> getAmbient();
	vector<float> getDiffuse();
	vector<float> getSpecular();
	float getShininess();

protected:
	vector<float> emissive, ambient, diffuse, specular;
	float shininess;
	char *id, *textref;
	int text_s, text_t;
	Texture *text;
	CGFtexture *textura;
	GLenum cullface;
};
#endif