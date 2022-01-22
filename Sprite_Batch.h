#ifndef SPRITE_BATCH_H_
#define SPRITE_BATCH_H_

#include <vector>
#include <GL/glew.h>
#include "glm/glm.hpp"

#include "Vertex.h"

enum class Glyph_Sort_Type { NONE, FRONT_TO_BACK, BACK_TO_FRONT, TEXTURE };

struct Glyph
{
    GLuint texture;
    float depth;

    Vertex top_left;
    Vertex top_right;
    Vertex btm_left;
    Vertex btm_right;
};

class Render_Batch
{
public:
    Render_Batch( GLuint offset_in, GLuint num_vertices_in, GLuint texture_in );
    //Render_Batch ( const Render_Batch& ) = delete;
    //Render_Batch& operator = ( const Render_Batch& ) = delete;
    ~Render_Batch();

public:
    GLuint offset;
    GLuint num_vertices;
    GLuint texture;
private:


};

class Sprite_Batch
{
public:    
    Sprite_Batch();
    Sprite_Batch ( const Sprite_Batch& ) = delete;
    Sprite_Batch& operator = ( const Sprite_Batch& ) = delete;
    ~Sprite_Batch();

public:
    void init();

    void start( const Glyph_Sort_Type type = Glyph_Sort_Type::TEXTURE );
    void stop();

    void draw( const glm::vec4& rect, const glm::vec4& uv_rect, const GLuint texture, const float depth, const Colour& c );   // Make Color optional, default = white later on.

    void render_batch() const;

private:
    void create_render_batches();
    void create_vertex_array();
    void sort_glyphs();

    static bool compare_front_to_back( const Glyph* const a, const Glyph* const b );
    static bool compare_back_to_front( const Glyph* const a, const Glyph* const b );
    static bool compare_texture( const Glyph* const a, const Glyph* const b );

private:
    GLuint vao;
    GLuint vbo;

    Glyph_Sort_Type glyph_sort_type;

    std::vector<Glyph*> glyphs;
    std::vector<Render_Batch> render_batches;

};



#endif /* SPRITE_BATCH_H_ */