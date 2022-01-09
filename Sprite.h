#ifndef SPRITE_H_
#define SPRITE_H_

#include <GL/glew.h>

class Sprite
{
public:
    Sprite();
    Sprite ( const Sprite& ) = delete;
    Sprite& operator = ( const Sprite& ) = delete;
    ~Sprite();

public:
    void init( const int xi, const int yi, const int wi, const int hi );
    void draw() const;

private:
    int x;
    int y;
    int width;
    int height;

    GLuint vbo;
};





#endif /* SPRITE_H_ */