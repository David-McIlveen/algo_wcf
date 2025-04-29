#include "tile_parser.hpp"

TileParser::TileParser(fs::path image, fs::path config){

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

double TileParser::get_color_crc(double* vals){
    double total = 0;
    for (int i = 0; i < _tile_x_size * _tile_y_size * _tile_c_size; i++){
        if(i % 5 == 0){
            total += vals[i] * .5;
        } else if (i % 7 == 0){
            total += vals[i] * .4;
        } else if (i % 13 == 0){
            total += vals[i] * .3;
        } else if (i % 19 == 0){
            total += vals[i] * .2;
        }
    }
    return total;
}

int TileParser::id_at(int x, int y){
    if(x < 0 || x >= _tile_x_count) throw "X out of range in id Grid!";
    if(y < 0 || y >= _tile_y_count) throw "Y out of range in id Grid!";

}

void TileParser::parse_tiles(){

}

void TileParser::set_ruleset(){

}

void TileParser::generate_tiles(){

}