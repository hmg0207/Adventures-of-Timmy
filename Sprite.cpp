#include "Sprite.h"
#include "Vertex.h"

#include <cstddef>


Sprite::Sprite()
    :
    vbo(0U)
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
    
    // Two Triangles with 3 points. Do Index Buffers later...
    Vertex vd[ 6 ];
    vd[0].set_position( this->x + this->width, this->y + this->height );
    vd[0].set_uv( 1.0f, 1.0f );

    vd[1].set_position( this->x, this->y + this->height );
    vd[1].set_uv( 0.0f, 1.0f );

    vd[2].set_position( this->x, this->y );
    vd[2].set_uv( 0.0f, 0.0f );

    vd[3].set_position( this->x, this->y );
    vd[3].set_uv( 0.0f, 0.0f );

    vd[4].set_position( this->x + this->width, this->y );
    vd[4].set_uv( 1.0f, 0.0f );

    vd[5].set_position( this->x + this->width, this->y + this->height );
    vd[5].set_uv( 1.0f, 1.0f );

    for ( GLuint i = 0U; i < 6U; i++ )
    {
        vd[i].set_colour( 255U, 0U, 255U, 255U );
    }

    vd[1].set_colour( 255U, 0U, 0U,   255U );
    vd[4].set_colour( 0U,   0U, 255U, 255U );

    glBindBuffer( GL_ARRAY_BUFFER, this->vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vd), vd, GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void Sprite::draw() const
{
    glBindBuffer( GL_ARRAY_BUFFER, this->vbo );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer( 0U, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof( Vertex, position ) );
    glVertexAttribPointer( 1U, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof( Vertex, colour ) );
    glVertexAttribPointer( 2U, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof( Vertex, uv ) );

    glDrawArrays( GL_TRIANGLES, 0, 6 );

    glDisableVertexAttribArray(0);
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}