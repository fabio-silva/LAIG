#include "Ortho.h"

Ortho::Ortho(char *id, float near, float far, float left, float right, float top, float bottom)
{
	strcpy(this->id, id);
	this->near = near;
	this->far = far;
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
}