#ifndef IMAGE_LOADER_H_
#define IMAGE_LOADER_H_

#include <string>   

#include "Texture.h"

class Image_Loader
{
public:
    Image_Loader();
    Image_Loader ( const Image_Loader& ) = delete;
    Image_Loader& operator = ( const Image_Loader& ) = delete;
    ~Image_Loader();

public:
    static Texture load_png( std::string filename );
};  


#endif /* IMAGE_LOADER_H_ */