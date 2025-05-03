#include "rule_set.hpp"
#include <iostream>

TileRuleSet::TileRuleSet(int tile_c){
    _lookup = new bool[DIR_COUNT * tile_c * tile_c];
    _tile_c = tile_c;
    for (int i = 0; i < DIR_COUNT * DIR_COUNT * tile_c; i++){
        _lookup[i] = false;
    }
}

void TileRuleSet::set(bool value, int for_tile, int dir, int at){
    if(for_tile < 0 || for_tile >= _tile_c) throw "For Tile is out of range!";
    if(dir < 0 || dir >= DIR_COUNT) throw "Dir is out of range!";
    if(at < 0 || at >= _tile_c) throw "At is out of range!";
    _lookup[dir * (_tile_c * _tile_c) + for_tile * _tile_c + at] = value;
}

bool TileRuleSet::get(int for_tile, int dir, int at){
    if(for_tile < 0 || for_tile >= _tile_c) throw "For Tile is out of range!";
    if(dir < 0 || dir >= DIR_COUNT) throw "Dir is out of range!";
    if(at < 0 || at >= _tile_c) throw "At is out of range!";
    return _lookup[dir * (_tile_c * _tile_c) + for_tile * _tile_c + at];
}

TileRuleSet::~TileRuleSet(){
    delete[] _lookup;
}