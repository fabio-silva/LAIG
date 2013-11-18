#include <GL/glew.h>
#include "WaterLine.h"

WaterLine::WaterLine(char *frag, char *vert, char *bmp, char *text):Primitiva(data,NULL)
{




	init(vert, frag);




	p = new Plane(20);

	time = 0;



	CGFshader::bind();

	

	bump = new CGFtexture(bmp);
	texture = new CGFtexture(text);

	GLint textureImage = glGetUniformLocation(id(), "texture");

	glUniform1i(textureImage, 0);

	GLint blue = glGetUniformLocation(id(), "blue");

	glUniform1i(blue, 1);

	timeLoc = glGetUniformLocation(id(), "time");


	

}


void WaterLine::bind()
{
	CGFshader::bind();

	glActiveTexture(GL_TEXTURE0);

	bump->apply();

	glActiveTexture(GL_TEXTURE1);

	texture->apply();
}


void WaterLine::draw()
{
	
	glPushMatrix();
	bind();
	glRotatef(-90,0,1,0);
	glRotatef(-90,1,0,0); 
	glScalef(20,10,30);

	
	glUniform1f(timeLoc, time);
	time += 0.01;

	
	if(time == 0.1) time = 0;
	
	p->draw();

	unbind();
	glPopMatrix();

	

}