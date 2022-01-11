#ifndef VERTEX_H_
#define VERTEX_H_

#include <GL/glew.h>

struct Position
{
    GLfloat x;
    GLfloat y;
};

struct Colour
{
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
};    

struct Vertex
{
    Position position;
    Colour   colour;
};


#endif /* VERTEX_H_ */