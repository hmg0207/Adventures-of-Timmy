#include "Game.h"

#include "Kerror.h"

Game::Game()
    :
    window( nullptr ),
    gfx_ctx( nullptr ),
    win_width( 1024 ),
    win_height( 768 ),
    state( GameState::PLAY ),
    timer( 0.0f )
{}


Game::~Game()
{
    for( auto& i : this->sprites )
    {
        delete i;
        this->sprites.pop_back();
    }
    SDL_GL_DeleteContext( this->gfx_ctx );
}

void Game::init_systems()
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

    glewExperimental = true;
    if ( glewInit() != GLEW_OK )
    {
        KERROR( "Failed to initialise GL Extension Wrangler (GLEW) Library." );
    }

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, SDL_TRUE );
}

void Game::init_shaders()
{
    this->test_shader.compile_shaders( "./Shaders/basic_shader.vert", "./Shaders/basic_shader.frag" );
}

void Game::run()
{
    this->init_systems();
    this->init_shaders();    

    this->sprites.push_back( new Sprite() );
    this->sprites.back()->init( -1, -1, 1, 1, "./Dev_Res/Images/happy-test-screen.png" );

    this->sprites.push_back( new Sprite() );
    this->sprites.back()->init( 0, -1, 1, 1, "./Dev_Res/Images/happy-test-screen.png" );

    this->sprites.push_back( new Sprite() );
    this->sprites.back()->init( -1, 0, 1, 1, "./Dev_Res/Images/happy-test-screen.png" );

    this->loop();
}

void Game::loop()
{
    while ( this->state != GameState::EXIT )
    {
        this->handle_input();
        this->timer += 0.01f;
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
                //printf( "Mouse Pos: %d, %d\n ", ev.motion.x, ev.motion.y );
                break;
        };
    }
    
}


void Game::draw()
{
    glClearDepth( 1.0 );
    glClearColor( 0.0f, 0.0f, 1.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    this->test_shader.start();
    glActiveTexture( GL_TEXTURE0 );
    
    GLuint timer_loc = this->test_shader.get_uniform_id( "timer" );
    if ( timer_loc == GL_INVALID_INDEX )
    {
        KERROR( "Failed to get uniform id." );
    }
    glUniform1f( timer_loc, this->timer );

    GLuint tex_loc = this->test_shader.get_uniform_id( "tex" );
    if ( tex_loc == GL_INVALID_INDEX )
    {
        KERROR( "Failed to get uniform id." );
    }
    glUniform1i( tex_loc, 0 );
    
    
    for( auto& i : this->sprites )
    {
        i->draw();
    }    

    this->test_shader.stop();

    glBindTexture( GL_TEXTURE_2D, 0U );

    SDL_GL_SwapWindow( this->window );
}