#ifndef FILE_IO_H_
#define FILE_IO_H_

#include <vector>
#include <string>

class File_Manager
{
public:    
    File_Manager();
    File_Manager ( const File_Manager& ) = delete;
    File_Manager& operator = (const File_Manager& ) = delete;
    ~File_Manager();

public:
    static bool read_file_to_buffer( std::string filename , std::vector<unsigned char>& buffer );
private:

};

#endif /* FILE_IO_H_ */ 