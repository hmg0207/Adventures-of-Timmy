#include "Game.h"

#include "Kerror.h"

Game::Game()
    :
    window( nullptr ),
    gfx_ctx( nullptr ),
    win_width( 1024 ),
    win_height( 768 ),
    state( GameState::PLAY ),
    timer( 0.0f ),
    max_fps( 60.0f )
{
    this->camera.init( this->win_width, this->win_height );
}


Game::~Game()
{
    for( auto& i : this->sprites )
    {
        if ( i != nullptr )
        {
            delete i;
        }
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

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE,    8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,  8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,   8 );
    SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE,  8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, SDL_TRUE );

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK,  SDL_GL_CONTEXT_PROFILE_CORE );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL,    SDL_TRUE );

    if ( ( this->window = SDL_CreateWindow( "The Adventures of Timmy ", 0, 0, this->win_width, this->win_height, SDL_WINDOW_OPENGL ) ) == nullptr )
    {
        KERROR( "Failed to create SDL Window." );
    }

    if ( ( this->gfx_ctx = SDL_GL_CreateContext( this->window ) ) == nullptr )
    {
        KERROR( "Failed to create GL Context." );
    }

    int a,b;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &a);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &b);
    KNOTICE( "Using OpenGL Version %s", glGetString(GL_VERSION) );
    KNOTICE( "Using OpenGL Context Version %d.%d\n",a,b);

    SDL_GL_SetSwapInterval(1);

    glewExperimental = true;
    if ( glewInit() != GLEW_OK )
    {
        KERROR( "Failed to initialise GL Extension Wrangler (GLEW) Library." );
    }
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
    this->sprites.back()->init( 0, 0, this->win_width/2, this->win_width/2, "./Dev_Res/Images/happy-test-screen.png" );

    this->sprites.push_back( new Sprite() );
    this->sprites.back()->init( this->win_width/2, 0, this->win_width/2, this->win_width/2, "./Dev_Res/Images/happy-test-screen.png" );

    this->loop();
}

void Game::loop()
{
    static const float max_fps_ms = 1000.0f / this->max_fps;
    while ( this->state != GameState::EXIT )
    {
        float start_ticks = (float)SDL_GetTicks();

        this->handle_input();
        this->timer += 0.01f;

        this->camera.update();

        this->draw();
        this->calculate_fps();
        //printf("%.5f\n", this->fps );

        float frame_ticks = (float)SDL_GetTicks() - start_ticks;
        if ( max_fps_ms > frame_ticks )
        {
            SDL_Delay( max_fps_ms - frame_ticks );
        }
    }
    KNOTICE( "Exiting Game..." );
    
}


void Game::handle_input()
{
    SDL_Event ev;
    static constexpr float CAM_SPEED = 10.0f;
    static constexpr float CAM_SCALE = 0.1f;

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

            case SDL_KEYDOWN:
                switch(ev.key.keysym.sym)
                {
                    case SDLK_w:
                        this->camera.set_position( this->camera.get_position() + glm::vec2( 0.0f, CAM_SPEED ) );
                    break;

                    case SDLK_s:
                        this->camera.set_position( this->camera.get_position() + glm::vec2( 0.0f, -CAM_SPEED ) );
                    break;

                    case SDLK_a:
                        this->camera.set_position( this->camera.get_position() + glm::vec2( -CAM_SPEED, 0.0f) );
                    break;

                    case SDLK_d:
                        this->camera.set_position( this->camera.get_position() + glm::vec2( CAM_SPEED, 0.0f ) );
                    break;    

                    case SDLK_q:
                        this->camera.set_scale( this->camera.get_scale() - CAM_SCALE );
                    break;

                    case SDLK_e:
                        this->camera.set_scale( this->camera.get_scale() + CAM_SCALE );
                    break;                     

                }
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

    GLuint ortho_proj_mat_loc = this->test_shader.get_uniform_id( "ortho_proj_mat" );
    if ( ortho_proj_mat_loc == GL_INVALID_INDEX )
    {
        KERROR( "Failed to get uniform id." );
    }
    glm::mat4 c_mat = this->camera.get_cam_matrix();
    glUniformMatrix4fv( ortho_proj_mat_loc, 1, GL_FALSE, &c_mat[0][0] );

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

 void Game::calculate_fps()
 {
    static constexpr unsigned NUM_SAMPLES = 10U;
    static float samples[ NUM_SAMPLES ]   = { 0.0f };
    static float prev_ticks               = (float)SDL_GetTicks();
    static unsigned cur_frame             = 0U;
    
    float ticks = (float)SDL_GetTicks();   
    this->frame_time = ticks - prev_ticks;
    
    samples[ cur_frame % NUM_SAMPLES ] = this->frame_time;
    cur_frame++;
    if ( cur_frame >= NUM_SAMPLES )
    {
        cur_frame = 0U;
    }

    float average_ticks = 0.0f;
    for ( unsigned i = 0U; i < NUM_SAMPLES; i++ )
    {
        average_ticks += samples[i];
    }
    average_ticks /= NUM_SAMPLES;

    if ( average_ticks > 0.0f )
    {
        this->fps = 1000.0f / average_ticks;   // milliseconds per second / average_ticks
    }
     
    prev_ticks = ticks;
 }