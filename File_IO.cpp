#include "File_IO.h"

#include <fstream>

#include "Kerror.h"

File_Manager::File_Manager()
{
    KNOTICE( "File Manager Created." );
}

File_Manager::~File_Manager()
{
    KNOTICE( "File Manager Destroyed." );
}

bool File_Manager::read_file_to_buffer( std::string filename , std::vector<unsigned char>& buffer )
{
    std::ifstream ifs( filename, std::ios::binary );
    if ( ifs.fail() )
    {
        KWARNING( "Failed to open file: \"%s\" in binary read mode", filename.c_str() );
        return false;
    }

    // -- Determine filesize
    ifs.seekg( 0, std::ios::end );
    size_t size = ifs.tellg();
    ifs.seekg( 0, std::ios::beg );
    size -= ifs.tellg();            // Reduce file size by any header bytes.

    buffer.resize( size );
    ifs.read( (char *)&(buffer[0]), size );

    ifs.close();
    return true;
}
