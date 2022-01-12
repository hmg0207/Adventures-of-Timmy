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

struct UV
{
    GLfloat u;
    GLfloat v;
};

struct Vertex
{
    Position position;
    Colour   colour;
    UV       uv;

    void set_position( const GLfloat x, const GLfloat y );
    void set_colour( const GLubyte r, const GLubyte g, const GLubyte b, const GLubyte a );
    void set_uv( const GLfloat u, const GLfloat v );
};


#endif /* VERTEX_H_ */