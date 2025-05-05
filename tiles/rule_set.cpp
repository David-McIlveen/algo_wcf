#include "rule_set.hpp"
#include <iostream>

using namespace std;

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

void TileRuleSet::print(){
    for (int tile_id = 0; tile_id < _tile_c; tile_id++){
        cout << "Rules for tile: " << tile_id << endl;
        for (int dir = 0; dir < DIR_COUNT; dir++){
            string val = "UP";
            if(dir == 1) val = "DOWN";
            if(dir == 2) val = "LEFT";
            if(dir == 3) val = "RIGHT";
            cout << "  For direction: " << val << endl;
            for (int rule_id = 0; rule_id < _tile_c; rule_id++){
                cout << "    Tile ID: " << rule_id << " | " << get(tile_id, dir, rule_id) << endl;
            }
        }        
    }
}

TileRuleSet::~TileRuleSet(){
    delete[] _lookup;
}