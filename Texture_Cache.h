#ifndef TEXTURE_CACHE_H_
#define TEXTURE_CACHE_H_

#include <string>
#include <map>
#include "Texture.h"

class Texture_Cache
{
public:    
    Texture_Cache();
    Texture_Cache ( const Texture_Cache& ) = delete;
    Texture_Cache& operator = ( const Texture_Cache& ) = delete;
    ~Texture_Cache();

public:
    Texture get_texture( const std::string tex_path );

private:
    std::map<std::string, Texture> texture_map;
};



#endif /* TEXTURE_CACHE_H_ */