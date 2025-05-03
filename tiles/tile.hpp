#ifndef TILE_TEMPLATE
#define TILE_TEMPLATE

#include "raw_tile_data.hpp"

// Contains color data as well as rules for tiles
class Tile{
    public:
        Tile(raw_tile_data* data);
        int get_id();
        raw_tile_data* get_tile_data();
        ~Tile();
    private:
        // Raw data for a given tile
        raw_tile_data* _data;
};

#endif