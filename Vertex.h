#ifndef VERTEX_H_
#define VERTEX_H_

#include <GL/glew.h>

struct Vertex
{
    struct Position
    {
        GLfloat x;
        GLfloat y;
    } position;

    struct Colour
    {
        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;
    } colour;
};


#endif /* VERTEX_H_ */