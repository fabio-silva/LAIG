#include "Camera.h"

#include <string>

Camera::Camera(char *id)
{
	this->id = id;
}

char *Camera::getId()
{
	return id;
}