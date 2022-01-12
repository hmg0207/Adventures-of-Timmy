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
    GLvoid compile_shaders( const std::string& vs_file, const std::string& fs_file );
    GLvoid bind_attribute( const std::string& attrib );    
    GLvoid start() const noexcept;
    GLvoid stop() const noexcept;

    GLint get_uniform_id( const std::string& name ) const;

private:
    GLuint load_shader( const std::string& filename, const unsigned type ) const;

private:
    GLuint prog_id;
    GLuint vs_id;
    GLuint fs_id;

    unsigned num_attribs;

};

#endif /* SHADER_H_ */