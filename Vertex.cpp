#include "Vertex.h"

void Vertex::set_position( const GLfloat x, const GLfloat y )
{
    position.x = x;
    position.y = y;
}

void Vertex::set_colour( const GLubyte r, const GLubyte g, const GLubyte b, const GLubyte a )
{
    colour.r = r;
    colour.g = g;
    colour.b = b;
    colour.a = a;
}
 
void Vertex::set_uv( const GLfloat u, const GLfloat v )
{
    uv.u = u;
    uv.v = v;
}