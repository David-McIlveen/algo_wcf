#ifndef TILE_TEMPLATE
#define TILE_TEMPLATE

#include "raw_tile_data.hpp"

// Contains color data as well as rules for tiles
class Tile{
    public:
        Tile(raw_tile_data* data, bool** tile_rule_set);
        int get_id();
        raw_tile_data* get_tile_data();
        bool** get_rule_table();
        ~Tile();
    private:
        // Raw data for a given tile
        raw_tile_data* _data;
        // A 4 x T bool table, where 0 = Up, 1 = Down, 2 = Left, 3 = Right
        bool** _tile_rule_set;
};

#endif