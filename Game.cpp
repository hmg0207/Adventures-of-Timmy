#include "Game.h"

#include "Kerror.h"

Game::Game()
{
    this->window = nullptr;
    this->win_width = 1024;
    this->win_height = 768;

    this->state = GameState::PLAY;
}

Game::~Game()
{

}

void Game::init()
{
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        KERROR( "Failed to initialise SDL.\n ");
    }

    this->window = SDL_CreateWindow( "The Adventures of Timmy ",
                                     0, 0,
                                     this->win_width, this->win_height, 
                                     SDL_WINDOW_OPENGL
                                   );

    if ( this->window == NULL )
    {
        KERROR( "Failed to create SDL Window.\n ");
    }

}

void Game::run()
{
    this->init();
    this->loop();
}

void Game::loop()
{
    while ( this->state != GameState::EXIT )
    {
        this->handle_input();
    }
}


void Game::handle_input()
{
    SDL_Event ev;
    while ( SDL_PollEvent( &ev ) )
    {
        switch ( ev.type )
        {
            case SDL_QUIT:
                this->state = GameState::EXIT;
                break;

            case SDL_MOUSEMOTION:
                printf( "Mouse Pos: %d, %d\n ", ev.motion.x, ev.motion.y );
                break;
        };
    }
    
}