#include "quantum_tile.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

int random_int(int max){
    std::srand(std::time(0));
    return std::rand() % max;
}

QuantumTile::QuantumTile(int no_of_tiles, TileRuleSet* rule_book){
    _no_of_tiles = no_of_tiles;
    _rule_book = rule_book;
    _entropy = no_of_tiles;
    _choices = new bool[no_of_tiles];
    for (int i = 0; i < no_of_tiles; i++){
        _choices[i] = true;
    }
    _adjacent_tiles = new QuantumTile*[NUMBER_OF_DIRECTIONS];
    for (int i = 0; i < NUMBER_OF_DIRECTIONS; i++){
        _adjacent_tiles[i] = nullptr;
    }
}

QuantumTile::~QuantumTile(){
    delete[] _choices;
    delete[] _adjacent_tiles;
}

void QuantumTile::set_tile_adjacent(int placement, QuantumTile* tile){
    if(placement < 0 || placement >= NUMBER_OF_DIRECTIONS) throw "Tile Index out of range!";
    _adjacent_tiles[placement] = tile;
}

void QuantumTile::alter_ruleset(int for_tile, int dir){
    // If already collapsed there's no reason to alter it
    if(_chosen_tile != DEFAULT_CHOSEN_TILE) return;

    for (int i = 0; i < _no_of_tiles; i++){
        // If the choice is available and it cannot be anymore:
        if(_choices[i] && _rule_book->get(for_tile, dir, i)){
            _choices[i] = false;
            _entropy -= 1;
        }
    }  
}

int QuantumTile::get_entropy(){
    return _entropy;
}

void QuantumTile::collapse(){
    if(is_collapsed()) return;
    collapse_affect();
    order_adj_tiles();
    for (int i = 0; i < to_collapse.size(); i++){
        if(to_collapse.at(i)->is_collapsed()) continue;
        std::cout << "Calling for collapse..." << std::endl;
        to_collapse.at(i)->collapse();
    }
}

void QuantumTile::collapse(std::function<void(void)> callback){
    if(_chosen_tile != DEFAULT_CHOSEN_TILE) return;
    collapse_affect();
    order_adj_tiles();
    callback(); //Sneak the update callback in there ;3
    for (int i = 0; i < to_collapse.size(); i++){
        to_collapse.at(i)->collapse(callback);
    }
}

bool QuantumTile::is_collapsed(){
    return _chosen_tile != DEFAULT_CHOSEN_TILE;
}

void QuantumTile::collapse_affect(){
    make_choice();
    //std::cout << "Choice Made" << std::endl;
    _entropy = 0;
    // Set the rules of the other tiles around us.
    for (size_t i = 0; i < NUMBER_OF_DIRECTIONS; i++){
        if(_adjacent_tiles[i] != nullptr){
            _adjacent_tiles[i]->alter_ruleset(_chosen_tile, i);
        }
    }
}

// This is O(1), as it's not dependent on N always 16 loops at most
void QuantumTile::order_adj_tiles(){
    //std::cout << "Ordering" << std::endl;
    // Arrage by entropy
    to_collapse = std::vector<QuantumTile*>();
    std::vector<QuantumTile*> to_collapse_unordered = std::vector<QuantumTile*>();
    for (int i = 0; i < NUMBER_OF_DIRECTIONS; i++){
        if(_adjacent_tiles[i] == nullptr) continue;
        to_collapse_unordered.push_back(_adjacent_tiles[i]);
    }
    
    if(to_collapse_unordered.empty()){
        std::cerr << "Tile was unlinked, cannot collapse." << std::endl;
    }

    while(!to_collapse_unordered.empty()){
        int least_i = -1;
        int least_v = _no_of_tiles + 1;
        for (size_t i = 0; i < to_collapse_unordered.size(); i++){
            if(to_collapse_unordered.at(i) == nullptr) continue;
            if(to_collapse_unordered.at(i)->_entropy < least_v){
                least_v = to_collapse_unordered.at(i)->_entropy;
                least_i = i;
            }
        }
        to_collapse.push_back(to_collapse_unordered.at(least_i));
        to_collapse_unordered.erase(to_collapse_unordered.begin() + least_i);
    }
}

void QuantumTile::make_choice(){
    // Assemble choices
    std::vector<int> tiles_to_choose_from;
    for (size_t i = 0; i < _no_of_tiles; i++){
        if(_choices[i]) tiles_to_choose_from.push_back(i);
    }


    // ERROR! NOT ENOUGH TILE DATA!
    if(tiles_to_choose_from.empty()){
        _chosen_tile = 0;
        std::cerr << "Tile rule set was not well defined enough" << std::endl;
        return;
    } 

    // Make a choice
    int choice_index = random_int(tiles_to_choose_from.size());
    _chosen_tile = tiles_to_choose_from.at(choice_index);
}

int QuantumTile::get_chosen_tile(){
    return _chosen_tile;
}