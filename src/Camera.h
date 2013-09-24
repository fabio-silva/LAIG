#ifndef CAMERA_H
#define CAMERA_H

#include <string>

class Camera{

public:
	Camera();

protected:
	char *id;
	float near,far;
	char *tipo;
};
#endif