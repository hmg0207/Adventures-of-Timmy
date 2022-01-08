#include "Game.h"

#include "Kerror.h"

Game::Game()
{
    this->window = nullptr;
    this->gfx_ctx = nullptr;

    this->win_width = 1024;
    this->win_height = 768;

    this->state = GameState::PLAY;
}

Game::~Game()
{
    SDL_GL_DeleteContext( this->gfx_ctx );
}

void Game::init()
{
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        KERROR( "Failed to initialise SDL.\n " );
    }

    if ( ( this->window = SDL_CreateWindow( "The Adventures of Timmy ", 0, 0, this->win_width, this->win_height, SDL_WINDOW_OPENGL ) ) == nullptr )
    {
        KERROR( "Failed to create SDL Window." );
    }

    if ( ( this->gfx_ctx = SDL_GL_CreateContext( this->window ) ) == nullptr )
    {
        KERROR( "Failed to create GL Context." );
    }

    if ( glewInit() != GLEW_OK )
    {
        KERROR( "Failed to initialise GL Extension Wrangler (GLEW) Library." );
    }

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, SDL_TRUE );



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
        this->draw();
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


void Game::draw() const
{
    glClearDepth( 1.0 );
    glClearColor( 0.0f, 0.0f, 1.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Horrible Test Code
    glEnableClientState( GL_COLOR_ARRAY );
    glBegin( GL_TRIANGLES );
        
        glColor3f( 1.0f, 0.0f, 0.0f );
        glVertex2f( -0.5f, -0.5f );
        glVertex2f(  0.5f, -0.5f );
        glVertex2f(  0.5f,  0.5f );

        glColor3f( 0.0f, 1.0f, 0.0f );
        glVertex2f(  0.5f,  0.5f );
        glVertex2f( -0.5f,  0.5f );
        glVertex2f( -0.5f, -0.5f );

    glEnd();
    glDisableClientState( GL_COLOR_ARRAY );

    SDL_GL_SwapWindow( this->window );
}