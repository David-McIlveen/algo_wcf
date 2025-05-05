#include "tile_writer.hpp"

using namespace std;

TileWriter::TileWriter(fs::path output_dir, std::vector<Tile*> all_tiles, QuantumGrid* grid){
    if(!fs::is_directory(output_dir)) throw "Must input a directory!";
    if(all_tiles.empty()) throw "Must have at least one tile to build grid with!";
    _out_dir = output_dir;
    _grid = grid;
    _tile_lookup = all_tiles;
    _tile_x_size = all_tiles.at(0)->get_tile_data()->_x_size;
    _tile_y_size = all_tiles.at(0)->get_tile_data()->_y_size;
    _tile_x_count = grid->get_x();
    _tile_y_count = grid->get_y();
    _img_x_size = _tile_x_count * _tile_x_size;
    _img_y_size = _tile_y_count * _tile_y_size;
    // Assuming it's an RGBA PNG
    _to_print = new Image(_img_x_size, _img_y_size, 4);
}

void TileWriter::run_algo(string output_name, OUTPUT_MODE mode){
    _output_name = output_name;
    switch (mode){
        case ITERATION:
            set_black_image();
            perform_iteration();
            break;
        case GRID_ITERATION:
            set_black_image();
            set_outline_grid();
            perform_iteration();
            break;
        case WHOLE_TIME:
            perform_benchmarking(NUMBER_OF_TESTS);
            break;
        case WHOLE:
            perform_collapse();
            break;
        }
}

void TileWriter::set_black_image(){
    for (int y = 0; y < _img_y_size; y++){
        for (int x = 0; x < _img_x_size; x++){
            for (int c = 0; c < 4; c++){
                if(c == 3){
                    _to_print->set(1, x, y, c);
                } else {
                    _to_print->set(1, x, y, c);
                }
            } 
        }
    }
}

void TileWriter::set_outline_grid(){
    // for (int y = 0; y < _img_y_size; y++){
    //     if(y % _tile_y_size == 0 || y % _tile_y_size == _tile_y_size - 1) continue;
    //     for (int x = 0; x < _img_x_size; x++){
    //         if(x % _tile_x_size == 0 || x % _tile_x_size == _tile_x_size - 1) continue;
    //         for (int c = 0; c < 3; c++){
    //             _to_print->set(.5, x, y, c);
    //         }
    //     }
    // }
    for (int y = 0; y < _img_y_size; y++){
        if(y % 2 == 0) continue;
        for (int x = 0; x < _img_x_size; x++){
            for (int c = 0; c < 3; c++){
                _to_print->set(.5, x, y, c);
            }
        }
    }
}

void TileWriter::update_tiles(int* tiles){
    for (int y = 0; y < _tile_y_count; y++){
        for (int x = 0; x < _tile_x_count; x++){
            if(tiles[x + y * _tile_x_count] != DEFAULT_CHOSEN_TILE){
                Tile* tile = _tile_lookup.at(tiles[x + y * _tile_x_count]);
                paint_tile(tile, x * _tile_x_size, y * _tile_y_size);
            }
        }
    }
}

void TileWriter::paint_tile(Tile* tile, int x_offset, int y_offset){
    raw_tile_data* data = tile->get_tile_data();
    Image* tile_colors = data->color_vals;
    for (int y = 0; y < _tile_y_size; y++){
        for (int x = 0; x < _tile_x_size; x++){
            for (int c = 0; c < 4; c++){
                double v = 1;
                if(tile_colors->get_channels() > c){
                    v = tile_colors->at(x, y, c);
                };
                _to_print->set(v, x + x_offset, y + y_offset, c);
            }
        }
    }
}

void TileWriter::update_entropy(int* tiles){
    for (int y = 0; y < _tile_y_count; y++){
        for (int x = 0; x < _tile_x_count; x++){
            if(tiles[x + y * _tile_x_count] < _tile_lookup.size() || tiles[x + y * _tile_x_count] != 0){
                paint_tile_square((_tile_lookup.size() - tiles[x + y * _tile_x_count]) * 1.0 / _tile_lookup.size(), x * _tile_x_size, y * _tile_y_size);
            }
        } 
    }
}


void TileWriter::paint_tile_square(double brightness, int x_offset, int y_offset){
    for (int y = 0; y < _tile_y_size; y++){
        for (int x = 0; x < _tile_x_size; x++){
            for (int c = 0; c < 3; c++){
                _to_print->set(brightness, x + x_offset, y + y_offset, c);
            }
        }
    }
}

void TileWriter::perform_iteration(){
    _grid->collapse([this] (void) {
        update_entropy(_grid->get_entropy_grid());
        update_tiles(_grid->get_collapsed_grid());
        fs::path output = _out_dir / (_output_name  + "-" + std::to_string(_iteration_id) + ".png");
        _iteration_id += 1;
        _to_print->set_file(output);
        _to_print->save_image();
    });
}

void TileWriter::perform_benchmarking(int n){
    TimeTest test = TimeTest("WCF_test.csv");
    test.start_test("WCF");
    for (int i = 0; i < n; i++){
        string file_name = _output_name + "-" + std::to_string(i) + ".png";
        test.start();
        _grid->collapse();
        test.stop();
        update_tiles(_grid->get_collapsed_grid());
        _to_print->set_file(_out_dir / file_name);
        _to_print->save_image();
        _grid->reset();
    }
    test.next_test();
}

void TileWriter::perform_collapse(){
    _grid->collapse();
    update_tiles(_grid->get_collapsed_grid());
    _to_print->set_file(_out_dir / (_output_name + ".png"));
    _to_print->save_image();
}