#include "Perspective.h"

Perspective::Perspective(char *id, float near_, float far_, float angle, vector<float> position, vector<float> target):Camera(id)
{        
        this->near_ = near_;
        this->far_ = far_;
        this->angle = angle;
        this->position = position;
        this->target = target;
}

void Perspective::render()
{
        glViewport (0, 0, 1280, 720);
        glMatrixMode( GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(angle,1280/720,near_,far_);
        gluLookAt(position[0],position[1],position[2],target[0],target[1],target[2],0,1,0);
        glMatrixMode(GL_MODELVIEW);
}