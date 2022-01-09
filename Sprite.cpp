#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
    if ( this->vbo != 0U )
    {
        glDeleteBuffers( 1, &this->vbo );
    }
}

void Sprite::init( const int xi, const int yi, const int wi, const int hi )
{
    this->x      = xi;
    this->y      = yi;
    this->width  = wi;
    this->height = hi;

    if ( this->vbo == 0U )
    {
        glGenBuffers( 1, &this->vbo );
    }
    
    // Two Triangles with 3 points, each point has 2 vertices = 2 * 3 * 2 = 12 in total.    
    GLfloat vertex_data[ 2 * 3 * 2 ] =
    {
        this->x + this->width, this->y + this->height,  // T1 TR
        this->x,               this->y + this->height,  // T1 TL
        this->x,               this->y,                 // T1 BL

        this->x,               this->y,                 // T2 BL
        this->x + this->width, this->y,                 // T2 BR
        this->x + this->width, this->y + this->height   // T2 TR
    };

    glBindBuffer( GL_ARRAY_BUFFER, this->vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void Sprite::draw() const
{
    glBindBuffer( GL_ARRAY_BUFFER, this->vbo );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer( 0U, 2, GL_FLOAT, GL_FALSE, 0, 0 );

    glDrawArrays( GL_TRIANGLES, 0, 6 );

    glDisableVertexAttribArray(0);
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}