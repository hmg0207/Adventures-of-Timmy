#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <GL/glew.h>

class Shader
{
public:
    Shader();
    Shader ( const Shader& ) = delete;
    Shader& operator = ( const Shader& ) = delete;
    ~Shader();

public:
    void compile_shaders( const std::string& vs_file, const std::string& fs_file );
    void link_shaders();
    void bind_attribute( const std::string& attrib );
    void start();
    void stop();

private:
    GLuint load_shader( const std::string& filename, const unsigned type );

private:
    GLuint prog_id;
    GLuint vs_id;
    GLuint fs_id;

    unsigned num_attribs;

};

#endif /* SHADER_H_ */