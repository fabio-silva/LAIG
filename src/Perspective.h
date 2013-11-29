#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include "Camera.h"

class Perspective: public Camera{

public:
        Perspective(char *id, float near_, float far_, float angle,vector <float> position, vector<float> target);
        void render();

protected:
        char* id;
        float near_,far_,angle;
        vector <float> position;
        vector <float> target;        
};
#endif