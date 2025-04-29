#include "quantum_grid.hpp"

QuantumGrid::QuantumGrid(int x, int y, int tile_count, bool*** ruleset){
    _tile_count = tile_count;
    _x_size = x;
    _y_size = y;
    _tiles = new QuantumTile* [x * y];
    populate_tiles();
}

QuantumGrid::~QuantumGrid(){
    destroy_all_tiles();
    delete _tiles;
}

void QuantumGrid::collapse(){
    int rand_x = random_int(_x_size);
    int rand_y = random_int(_y_size);
    get_tile(rand_x, rand_y)->collapse();
}

void QuantumGrid::collapse(void (*callback)()){
    int rand_x = random_int(_x_size);
    int rand_y = random_int(_y_size);
    get_tile(rand_x, rand_y)->collapse(callback);
}

int* QuantumGrid::get_entropy_grid(){
    update_entropy();
    return _entropy_grid;
}

void QuantumGrid::update_entropy(){
    for (int i = 0; i < _x_size * _y_size; i++){
        _entropy_grid[i] = _tiles[i]->get_entropy();
    }    
}

int* QuantumGrid::get_collapsed_grid(){
    update_choosen();
    return _collapsed_grid;
} 

void QuantumGrid::update_choosen(){
    for (int i = 0; i < _x_size * _y_size; i++){
        _collapsed_grid[i] = _tiles[i]->get_chosen_tile();
    }
}

void QuantumGrid::reset(){
    destroy_all_tiles();
    populate_tiles();
}

void QuantumGrid::link_tiles(){
    for (int y = 0; y < _y_size; y++){
        for (int x = 0; x < _x_size; x++){
            QuantumTile* this_tile = get_tile(x, y);
            this_tile->set_tile_adjacent(UP, get_tile(x, y + 1));
            this_tile->set_tile_adjacent(DOWN, get_tile(x, y - 1));
            this_tile->set_tile_adjacent(LEFT, get_tile(x - 1, y));
            this_tile->set_tile_adjacent(RIGHT, get_tile(x + 1, y));
        }
    }
}

void QuantumGrid::destroy_all_tiles(){
    for (int i = 0; i < _x_size * _y_size; i++){
        delete _tiles[i];
    }
}

void QuantumGrid::populate_tiles(){
    for (int i = 0; i < _x_size * _y_size; i++){
        _tiles[i] = new QuantumTile(_tile_count, _ruleset);
    }
}

QuantumTile* QuantumGrid::get_tile(int x, int y){
    if(x < 0, y < 0) return nullptr;
    if(x >= _x_size || y >= _y_size) return nullptr;
    return _tiles[x + y * _x_size];
}

int QuantumGrid::get_x(){
    return _x_size;
}

int QuantumGrid::get_y(){
    return _y_size;
}