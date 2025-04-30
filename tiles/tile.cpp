#include "tile.hpp"

Tile::Tile(raw_tile_data* data, bool** tile_rule_set){
    _data = data;
    _tile_rule_set = tile_rule_set;
}

Tile::~Tile(){
    delete _data->color_vals;
    delete _data;
}

int Tile::get_id(){
    return _data->_id;
}

raw_tile_data* Tile::get_tile_data(){
    return _data;
}

bool** Tile::get_rule_table(){
    return _tile_rule_set;
}