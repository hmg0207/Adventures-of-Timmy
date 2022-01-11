#include "Shader.h"

#include <fstream>
#include <sstream>

#include "Kerror.h"

Shader::Shader()
    :
    prog_id(0U),
    vs_id(0U),
    fs_id(0U),
    num_attribs(0U)
{

}

Shader::~Shader()
{

}

void Shader::compile_shaders( const std::string& vs_file, const std::string& fs_file )
{
    this->vs_id    = this->load_shader( vs_file, GL_VERTEX_SHADER );
    this->fs_id    = this->load_shader( fs_file, GL_FRAGMENT_SHADER );
    this->prog_id  = glCreateProgram();
    
    glAttachShader( this->prog_id, this->vs_id );
    glAttachShader( this->prog_id, this->fs_id );

    this->bind_attribute( "vPos" );
    this->bind_attribute( "vCol" );    

    int success    = -1; 
    glLinkProgram(  this->prog_id) ;
    glGetProgramiv( this->prog_id, GL_LINK_STATUS, &success );
    if(!success)
    {
        GLint len = 0;
        glGetProgramiv( this->prog_id, GL_INFO_LOG_LENGTH, &len );

        char log[len];
        glGetProgramInfoLog( this->prog_id, len, &len, log );

        glDeleteProgram( this->prog_id );

        KERROR( "Program failed to link.\n\t%s", log );
    }

    glDetachShader( this->prog_id, this->vs_id );
    glDetachShader( this->prog_id, this->fs_id );

    glDeleteShader(this->vs_id);
    glDeleteShader(this->fs_id);

}

void Shader::link_shaders()
{

}

GLuint Shader::load_shader( const std::string& filename, const unsigned type )
{
    std::string code;
    std::ifstream ifs;
    ifs.exceptions( std::ifstream::failbit | std::ifstream::badbit );

    try
    {
        ifs.open( filename );
        std::stringstream ss;
        ss << ifs.rdbuf();
        ifs.close();
        code = ss.str();
    }
    catch ( std::ifstream::failure e )
    {
        KERROR( "There was a problem reading the file \"%s\".\n\tifstream error: %s.", filename.c_str(), e.what() );
    }

    GLuint id          = 0U;
    int success        = -1;    ;
    const char* sc     = code.c_str();
    char info_log[512];

    if ( ( id = glCreateShader( type ) ) == 0U )
    {
        KERROR( "Failed to create shader ID for file %s.", filename );     
    }

    glShaderSource( id, 1U, &sc, NULL );
    glCompileShader( id );
    glGetShaderiv( id, GL_COMPILE_STATUS, &success );
    if ( success == GL_FALSE )
    {        
        GLint len = 0;
        glGetShaderiv( id, GL_INFO_LOG_LENGTH, &len );

        char log[len];
        glGetShaderInfoLog( id, len, &len, log );

        glDeleteShader( id );

        KERROR( "Compilation failed for shader file %s.\n\t%s", filename, log );
    }
    return id;
}

void Shader::bind_attribute( const std::string& attrib )
{
    glBindAttribLocation( this->prog_id, this->num_attribs, attrib.c_str() );
    this->num_attribs++;
}

void Shader::start()
{
    glUseProgram( this->prog_id );
    for ( GLuint i = 0U; i < this->num_attribs; i++ )
    {
        glEnableVertexAttribArray(i);
    }
}

void Shader::stop()
{
    glUseProgram( 0U );
    for ( GLuint i = 0U; i < this->num_attribs; i++ )
    {
        glDisableVertexAttribArray(i);
    }    
}