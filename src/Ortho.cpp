#include "Ortho.h"

Ortho::Ortho(char *id, float near_, float far_, float left, float right, float top, float bottom):Camera(id)
{
        this->near_ = near_;
        this->far_ = far_;
        this->left = left;
        this->right = right;
        this->top = top;
        this->bottom = bottom;
}

void Ortho::render()
{
        glMatrixMode( GL_PROJECTION);
        glLoadIdentity();
        glOrtho(left,right,bottom,top,near_,far_);
        glMatrixMode(GL_MODELVIEW);
}