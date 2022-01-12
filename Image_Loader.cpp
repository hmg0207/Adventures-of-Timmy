#include "Image_Loader.h"
#include "Pico_Png.h"
#include "File_IO.h"
#include "Kerror.h"

Image_Loader::Image_Loader()
{
    KNOTICE( "Image Loader Created.a" );
}

Image_Loader::~Image_Loader()
{
    KNOTICE( "Image Loader Destroyed." );
}

Texture Image_Loader::load_png( std::string filename )
{
    Texture tex = {};

    std::vector<unsigned char> in;
    std::vector<unsigned char> out;
    unsigned long w, h;

    if ( File_Manager::read_file_to_buffer( filename, in ) == false )
    {
        KERROR( "Failed to read png file \"%s\" to buffer.", filename.c_str() );
    }

    int err = decodePNG( out, w, h, &in[0], in.size(), true);
    if ( err != 0 )
    {
        KERROR( "Failed to decode png file. Error: %d.", std::to_string( err ) );
    }

    tex.width = w;
    tex.height = h;

    glGenTextures( 1U, &tex.id );
    glBindTexture( GL_TEXTURE_2D, tex.id );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,GL_RGBA, GL_UNSIGNED_BYTE, &out[0] );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

    glGenerateMipmap( GL_TEXTURE_2D );

    glBindTexture( GL_TEXTURE_2D, 0U );



    return tex;
}