#include "tile_parser.hpp"
#include <fstream>
#include "../quantum/quantum_grid.hpp"
#include "../quantum/quantum_tile.hpp"

TileParser::TileParser(fs::path image, fs::path config){
    _rule_image = new Image(image);
    parse_config(config);
    _tile_x_size = _rule_image->get_width() / _tile_x_count;
    _tile_y_size = _rule_image->get_height() / _tile_y_count;
    _tile_c_size = _rule_image->get_channels();
    cout << "Parseing tiles..." << endl;
    parse_tiles();
    cout << "Setting ruleset..." << endl;
    set_ruleset();
    cout << "Assembling tiles..." << endl;
    generate_tiles();

    // Cleanup!
    delete _rule_image;
    _rule_image = nullptr;
}

void TileParser::parse_config(fs::path config){
    std::ifstream file = std::ifstream(config);
    
    // Check if file was opened successfully
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + config.string());
    }
    
    std::string line1, line2;
    bool success = false;
    
    // Try to read the first line
    if (std::getline(file, line1)) {
        // Try to read the second line
        if (std::getline(file, line2)) {
            try {
                // Convert the strings to integers
                _tile_x_count = std::stoi(line1);
                _tile_y_count = std::stoi(line2);
                success = true;
            } catch (const std::invalid_argument&) {
                // Conversion failed - one of the lines wasn't an integer
                std::cerr << "Error: One or both lines are not valid integers." << std::endl;
            } catch (const std::out_of_range&) {
                // Conversion failed - integer is out of range
                std::cerr << "Error: One or both integers are out of range." << std::endl;
            }
        } else {
            std::cerr << "Error: File contains only one line." << std::endl;
        }
    } else {
        std::cerr << "Error: File is empty." << std::endl;
    }
    file.close();
    if(!success) throw "There was an error!";
}

std::vector<Tile*> TileParser::get_tiles(){
    return tiles;
}

TileRuleSet* TileParser::get_rule_set(){
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
            raw_tile_data* data = get_tile_data(x * _tile_x_size, y * _tile_y_size);
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
    //cout << "Rule Image: " << _rule_image->get_width() << " | " << _rule_image->get_height() << endl;
    raw_tile_data* ret_val = new raw_tile_data;
    ret_val->_c_size = _tile_c_size;
    ret_val->_x_size = _tile_x_size;
    ret_val->_y_size = _tile_y_size;
    ret_val->color_vals = new Image(_tile_x_size, _tile_y_size, _tile_c_size);
    for (int y = 0; y < _tile_y_size; y++){
        for (int x = 0; x < _tile_x_size; x++){
            for (int c = 0; c < _tile_c_size; c++){
                //cout << "Lookup at: " << x_off + x << " | " << y_off + y << endl;
                double v = _rule_image->at(x_off + x, y_off + y, c);
                ret_val->color_vals->set(v, x, y, c);
            }
        }
    }
    return ret_val;
}

void TileParser::set_ruleset(){
    // cout << "Printing IDs" << endl;
    // for (int y = 0; y < _tile_y_count; y++){
    //     for (int x = 0; x < _tile_x_count; x++){
    //         cout << id_at(x, y) << ",";
    //     }
    //     cout << endl;
    // }
    
    _master_ruleset = new TileRuleSet(_raw_tiles.size());
    for (int y = 0; y < _tile_y_count; y++){
        for (int x = 0; x < _tile_x_count; x++){
            int this_id = id_at(x, y);
            int up = id_at(x, y - 1);
            int down = id_at(x, y + 1);
            int left = id_at(x - 1, y);
            int right = id_at(x + 1, y);
            if(up != -1){
                _master_ruleset->set(true, this_id, 0, up);
            }
            if(down != -1){
                _master_ruleset->set(true, this_id, 1, down);
            }
            if(left != -1){
                _master_ruleset->set(true, this_id, 2, left);
            }
            if(right != -1){
                _master_ruleset->set(true, this_id, 3, right);
            }
        }
    }
    //_master_ruleset->print();
}

void TileParser::generate_tiles(){
    for (int i = 0; i < _raw_tiles.size(); i++){
        raw_tile_data* data = _raw_tiles.at(i);
        Tile* tile = new Tile(data);
        tiles.push_back(tile);
    }
}