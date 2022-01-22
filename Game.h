#ifndef GAME_H_
#define GAME_H_

#include <vector>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Shader.h"
#include "Texture.h"
#include "Camera_2D.h"
#include "Sprite_Batch.h"

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
    void calculate_fps();


private:
    SDL_Window* window;
    SDL_GLContext gfx_ctx;

    int win_width;
    int win_height;

    GameState state;
    Camera_2D camera;

    Sprite_Batch sprite_batch;
    
    Shader test_shader;

    float max_fps;
    float fps;
    float frame_time;    

    float timer;

};



#endif /* GAME_H_ */