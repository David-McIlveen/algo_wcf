#include "tile_parser.hpp"
#include "../quantum/quantum_grid.hpp";
#include "../quantum/quantum_tile.hpp";

TileParser::TileParser(fs::path image, fs::path config){
    _rule_image = new Image(image);
    parse_config(config);
    parse_tiles();
    set_ruleset();
    generate_tiles();

    // Cleanup!
    delete _rule_image;
    _rule_image = nullptr;
}

TileParser::~TileParser(){
    for (int i = 0; i < tiles.size(); i++){
        delete tiles.at(i);
    }
    delete _master_ruleset;
}

std::vector<Tile*> TileParser::get_tiles(){
    return tiles;
}

bool*** TileParser::get_ruleset(){
    return _master_ruleset;
}

int TileParser::id_at(int x, int y){
    if(x < 0 || x >= _tile_x_count) return -1;
    if(y < 0 || y >= _tile_y_count) return -1;
    return _id_grid[x + y * _tile_x_count];
}

void TileParser::parse_tiles(){
    _id_grid = new int[_tile_y_count * _tile_x_count];
    for (int y = 0; y < _tile_y_count; y++){
        for (int x = 0; x < _tile_x_count; x++){
            raw_tile_data* data = get_tile_data(_tile_x_count * _tile_x_size, _tile_y_count * _tile_y_size);
            double color_crc = data->color_vals->get_color_sum();
            if(_data_map.count(color_crc)){
                int id = _data_map.at(color_crc)->_id;
                _id_grid[x + y * _tile_x_count] = id;
                delete data;
            } else {
                data->_id = current_id;
                current_id++;
                _data_map.emplace(color_crc, data);
                _raw_tiles.push_back(data);
                _id_grid[x + y * _tile_x_count] = data->_id;
            }
        }
    }
}

raw_tile_data* TileParser::get_tile_data(int x_off, int y_off){
    raw_tile_data* ret_val = new raw_tile_data;
    ret_val->_c_size = _tile_c_size;
    ret_val->_x_size = _tile_x_size;
    ret_val->_y_size = _tile_y_size;
    ret_val->color_vals = new Image(_tile_x_count, _tile_y_count, _tile_c_size);
    for (int y = 0; y < _tile_y_size; y++){
        for (int x = 0; x < _tile_x_size; x++){
            for (int c = 0; c < _tile_c_size; c++){
                double v = _rule_image->at(x_off + x, y_off + y, c);
            }
        }
    }
}

void TileParser::set_ruleset(){
    _master_ruleset = TileRuleSet(_raw_tiles.size());
    
}

void TileParser::generate_tiles(){
    for (int i = 0; i < _data_map.size(); i++){
        raw_tile_data* data = _data_map.at(i);
        Tile* tile = new Tile(data, _master_ruleset[i]);
        tiles.push_back(tile);
    }
}