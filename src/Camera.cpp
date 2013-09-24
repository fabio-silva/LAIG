#include "Camera.h"
#include <string>

Camera::Camera()
{
	strcpy(this->id, id);
	this->near = near;
	this->far = far;

	tipo = NULL;
}