#include "Texture_Cache.h"
#include "Image_Loader.h"
#include "Kerror.h"


Texture_Cache::Texture_Cache()
{
    KNOTICE( "Texture Cache Created." );
}

Texture_Cache::~Texture_Cache()
{
    KNOTICE( "Texture Cache Destroyed." );
}


Texture Texture_Cache::get_texture( const std::string tex_path )
{
    auto it = this->texture_map.find( tex_path );
   
    if ( it == this->texture_map.end() )
    {        
        KNOTICE( "Adding %s to Texture Cache.", tex_path.c_str() );
        Texture tex = Image_Loader::load_png( tex_path );
        
        this->texture_map.insert( std::make_pair( tex_path, tex ) );
        
        return tex;
    }
    KNOTICE( "Loaded %s from Texture Cache.", tex_path.c_str() );
    return it->second;
}