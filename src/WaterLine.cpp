#include <GL/glew.h>
#include "WaterLine.h"

WaterLine::WaterLine()
{




	init("vertexShader.vert", "fragmentShader.frag");


	cout << "TUDO OK" << endl;



	p = new Plane(20);




	CGFshader::bind();

	bump = new CGFtexture("watermap.jpg");
	texture = new CGFtexture("water.jpg");

	GLint textureImage = glGetUniformLocation(id(), "texture");

	glUniform1i(textureImage, 0);

	GLint blue = glGetUniformLocation(id(), "blue");

	glUniform1i(blue, 1);


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
	glTranslatef(0,0,10);
	glRotatef(-90,1,0,0); 
	glScalef(20,10,30);
	bind();

	p->draw();

	unbind();

	glPopMatrix();
}