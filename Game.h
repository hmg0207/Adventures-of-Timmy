#ifndef GAME_H_
#define GAME_H_

#include <vector>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Sprite.h"
#include "Shader.h"
#include "Texture.h"

enum class GameState { PLAY , EXIT };

class Game
{
public:
    Game();
    Game (const Game& ) = delete;
    Game& operator = ( const Game& ) = delete;
    ~Game();

public:
    void run();

private:
    void init_systems();
    void init_shaders();
    void handle_input();
    void loop();
    void draw();


private:
    SDL_Window* window;
    SDL_GLContext gfx_ctx;

    int win_width;
    int win_height;

    GameState state;

    std::vector<Sprite*> sprites;
    
    Shader test_shader;
    

    float timer;    

};



#endif /* GAME_H_ */