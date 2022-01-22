#include "Sprite_Batch.h"

#include <algorithm>

#include "Kerror.h"

Render_Batch::Render_Batch( GLuint offset_in, GLuint num_vertices_in, GLuint texture_in )
    :
    offset( offset_in ),
    num_vertices( num_vertices_in ),
    texture( texture_in )
{}

Render_Batch::~Render_Batch()
{}

Sprite_Batch::Sprite_Batch()
    :
    vao(0U),
    vbo(0U),
    glyph_sort_type( Glyph_Sort_Type::TEXTURE )
{


}

Sprite_Batch::~Sprite_Batch()
{
    for( auto& i : this->glyphs )
    {
        delete i;            
    }
    this->glyphs.clear();
}

void Sprite_Batch::init()
{
    this->create_vertex_array();
}

void Sprite_Batch::start( const Glyph_Sort_Type type )
{
    this->glyph_sort_type = type;
    this->render_batches.clear();
    this->glyphs.clear();
}

void Sprite_Batch::stop()
{
    this->sort_glyphs();
    this->create_render_batches();

}

void Sprite_Batch::draw( const glm::vec4& rect, const glm::vec4& uv_rect, const GLuint texture, const float depth, const Colour& c )
{
    Glyph* g = new Glyph;
    g->texture = texture;
    g->depth = depth;

    g->top_left.colour = c;
    g->top_left.set_position( rect.x, rect.y + rect.w );
    g->top_left.set_uv( uv_rect.x, uv_rect.y + uv_rect.w );

    g->btm_left.colour = c;
    g->btm_left.set_position( rect.x, rect.y );
    g->btm_left.set_uv( uv_rect.x, uv_rect.y );

    g->top_right.colour = c;
    g->top_right.set_position( rect.x + rect.z , rect.y + rect.w );      // Consider using array notation later. z and w looks a bit messy.
    g->top_right.set_uv( uv_rect.x + uv_rect.z, uv_rect.y + uv_rect.w );

    g->btm_right.colour = c;
    g->btm_right.set_position( rect.x + rect.z, rect.y );
    g->btm_right.set_uv( uv_rect.x + uv_rect.z, uv_rect.y );

    this->glyphs.push_back(g);

}

void Sprite_Batch::render_batch() const
{
    glBindVertexArray( this->vao );
    for( auto&i : this->render_batches )
    {
        glBindTexture( GL_TEXTURE_2D, i.texture );
        glDrawArrays( GL_TRIANGLES, i.offset, i.num_vertices );
    }
    glBindVertexArray( 0U );
}

void Sprite_Batch::create_render_batches()
{
    if ( glyphs.empty() )
    {
        return;
    }

    std::vector<Vertex> v;
    v.resize( this->glyphs.size() * 6U );

    unsigned i = 0U;
    unsigned offset = 0U;

    render_batches.emplace_back( offset, 6U, this->glyphs[0]->texture );

    v[i++] = this->glyphs[0]->top_left;
    v[i++] = this->glyphs[0]->btm_left;
    v[i++] = this->glyphs[0]->btm_right;
    v[i++] = this->glyphs[0]->btm_right;
    v[i++] = this->glyphs[0]->top_right;
    v[i++] = this->glyphs[0]->top_left;
    
    offset += 6U;

    for( unsigned g = 1U; g < this->glyphs.size(); g++ )
    {
        if ( this->glyphs[g]->texture != this->glyphs[ g-1 ]->texture )
        {
            render_batches.emplace_back( 0U, 6U, this->glyphs[g]->texture );
        }
        else
        {
            render_batches.back().num_vertices += 6U;
        }
        v[i++] = this->glyphs[g]->top_left;
        v[i++] = this->glyphs[g]->btm_left;
        v[i++] = this->glyphs[g]->btm_right;
        v[i++] = this->glyphs[g]->btm_right;
        v[i++] = this->glyphs[g]->top_right;
        v[i++] = this->glyphs[g]->top_left;

        offset += 6U;       
    }

    glBindBuffer( GL_ARRAY_BUFFER, this->vbo );
    glBufferData( GL_ARRAY_BUFFER, v.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW ); // Orphan the data
    glBufferSubData( GL_ARRAY_BUFFER, 0U, v.size() * sizeof( Vertex ), v.data() );

    glBindBuffer( GL_ARRAY_BUFFER, 0U );
}

void Sprite_Batch::create_vertex_array()
{
    if ( this->vao == 0U )
    {
        glGenVertexArrays( 1, &this->vao );
    }
    glBindVertexArray( this->vao );

    if ( this->vbo == 0U )
    {
        glGenBuffers( 1, &this->vbo );
    }
    glBindBuffer( GL_ARRAY_BUFFER, this->vbo );

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer( 0U, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof( Vertex, position ) );
    glVertexAttribPointer( 1U, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof( Vertex, colour ) );
    glVertexAttribPointer( 2U, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof( Vertex, uv ) );

    glBindVertexArray(0U);
}

void Sprite_Batch::sort_glyphs()
{
    switch ( this->glyph_sort_type )
    {
        case Glyph_Sort_Type::NONE:
            return;
            
        case Glyph_Sort_Type::FRONT_TO_BACK:
            std::stable_sort( this->glyphs.begin(), this->glyphs.end(), Sprite_Batch::compare_front_to_back );
            break;

        case Glyph_Sort_Type::BACK_TO_FRONT:
            std::stable_sort( this->glyphs.begin(), this->glyphs.end(), Sprite_Batch::compare_back_to_front );
            break;

        case Glyph_Sort_Type::TEXTURE:
            std::stable_sort( this->glyphs.begin(), this->glyphs.end(), Sprite_Batch::compare_texture );
            break;

        default:
            KERROR( "Unknown glyph sort type: %d!", this->glyph_sort_type)
            break;
    }
    
}


bool Sprite_Batch::compare_front_to_back( const Glyph* const a, const Glyph* const b )
{
    return ( a->depth < b->depth );
}

bool Sprite_Batch::compare_back_to_front( const Glyph* const a, const Glyph* const b )
{
    return ( a->depth > b->depth );
}

bool Sprite_Batch::compare_texture( const Glyph* const a, const Glyph* const b )
{
    return( a->texture < b->texture );
}