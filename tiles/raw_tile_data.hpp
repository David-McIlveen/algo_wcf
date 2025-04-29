#ifndef RAW_TILE_DATA
#define RAW_TILE_DATA

#include "../stb_image/src/stb_image_cpp.h"

// Contains data about the tile's size, as well as the colors that it contains
// It also has the tile's given ID
struct raw_tile_data{
    Image* color_vals;
    int _x_size;
    int _y_size;
    int _c_size;  
    int _id;
};

#endif