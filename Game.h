#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <GL/glew.h>

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
    void init();
    void handle_input();
    void loop();


private:
    SDL_Window* window;
    int win_width;
    int win_height;

    GameState state;

};



#endif /* GAME_H_ */