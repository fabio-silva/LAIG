#include "Ortho.h"

Ortho::Ortho(char *id, float near, float far, float left, float right, float top, float bottom):Camera(id)
{
	this->near = near;
	this->far = far;
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
}

void Ortho::render()
{
	glMatrixMode( GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left,right,bottom,top,near,far);
	glMatrixMode(GL_MODELVIEW);
}