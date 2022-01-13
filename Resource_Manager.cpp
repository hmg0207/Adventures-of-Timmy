#include "Resource_Manager.h"
#include "Kerror.h"

Resource_Manager::Resource_Manager()
{
    KNOTICE( "Resource Manager Created." );
}


Resource_Manager::~Resource_Manager()
{
    KNOTICE( "Resource Manager Destroyed." );
}

Texture_Cache Resource_Manager::texture_cache;

Texture Resource_Manager::get_texture( const std::string tex_path )
{
    return texture_cache.get_texture( tex_path );
}