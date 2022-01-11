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
    vd[0].position.x = this->x + this->width;  vd[0].position.y = this->y + this->height;
    vd[1].position.x = this->x;                vd[1].position.y = this->y + this->height;
    vd[2].position.x = this->x;                vd[2].position.y = this->y;

    vd[3].position.x = this->x;                vd[3].position.y = this->y;
    vd[4].position.x = this->x + this->width;  vd[4].position.y = this->y;
    vd[5].position.x = this->x + this->width;  vd[5].position.y = this->y + this->height;

    for ( GLuint i = 0U; i < 6U; i++ )
    {
        vd[i].colour.r = 255U;
        vd[i].colour.g =   0U;
        vd[i].colour.b = 255U;
        vd[i].colour.a = 255U;
    }

    vd[1].colour.r = 255U;
    vd[1].colour.g =   0U;
    vd[1].colour.b =   0U;
    vd[1].colour.a = 255U;

    vd[4].colour.r =   0U;
    vd[4].colour.g = 255U;
    vd[4].colour.b =   0U;
    vd[4].colour.a = 255U;        


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

    glDrawArrays( GL_TRIANGLES, 0, 6 );

    glDisableVertexAttribArray(0);
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}