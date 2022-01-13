#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include "Texture_Cache.h"

class Resource_Manager
{
public:    
    Resource_Manager();
    Resource_Manager ( const Resource_Manager& ) = delete;
    Resource_Manager& operator = ( const Resource_Manager& ) = delete;
    ~Resource_Manager();

public:
    static Texture get_texture( const std::string tex_path );    

private:
    static Texture_Cache texture_cache;

};


#endif /* RESOURCE_MANAGER_H_ */