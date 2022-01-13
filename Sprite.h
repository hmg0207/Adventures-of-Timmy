#ifndef SPRITE_H_
#define SPRITE_H_

#include <string>
#include <GL/glew.h>

#include "Texture.h"

class Sprite
{
public:
    Sprite();
    //Sprite ( const Sprite& ) = delete;
    Sprite& operator = ( const Sprite& ) = delete;
    ~Sprite();

public:
    void init( const int xi, const int yi, const int wi, const int hi, const std::string tex_path );
    void draw() const;

private:
    int x;
    int y;
    int width;
    int height;

    GLuint vbo;

    Texture texture;
};





#endif /* SPRITE_H_ */