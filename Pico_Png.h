#ifndef PICO_PNG_H_
#define PICO_PNG_H_

#include <vector>

extern int decodePNG( std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true );

#endif /* PICO_PNG_H_ */