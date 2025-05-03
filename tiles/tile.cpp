#include "tile.hpp"

Tile::Tile(raw_tile_data* data){
    _data = data;
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