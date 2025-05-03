#ifndef TILE_WRITER
#define TILE_WRITER

#include <filesystem>
#include <vector>
#include "../quantum/quantum_grid.hpp"
#include "../benchmarking/testing.hpp"
#include "../stb_image/src/stb_image_cpp.h"
#include "tile.hpp"

namespace fs = std::filesystem;

const int NUMBER_OF_TESTS = 5;

enum OUTPUT_MODE {
    ITERATION, // Iterates though grid and prints one out each time a tile is chosen also shows the entropy of a given tile by making it lighter
    GRID_ITERATION, // Same as before but an outline of the grid is shown
    WHOLE_TIME, // Prints the whole grid out quickly and prints a CSV of the given time
    WHOLE // Simply prints the grid when it's done
};

// Writes a series of tiles to an image
class TileWriter{
    public:
        TileWriter(fs::path output_dir, std::vector<Tile*> all_tiles,QuantumGrid* grid);
        void run_algo(std::string output_name, OUTPUT_MODE mode);
    private:
        int _img_x_size;
        int _img_y_size;
        int _tile_x_size;
        int _tile_y_size;
        int _tile_x_count;
        int _tile_y_count;
        int _iteration_id = 0;
        QuantumGrid* _grid;
        std::vector<Tile*> _tile_lookup;
        fs::path _out_dir;
        std::string _output_name;
        Image* _to_print;
        // Sets the image background to black
        void set_black_image();
        // Sets an outline grid on the image
        void set_outline_grid();
        // Prints the given ids of the tiles onto the image
        void update_tiles(int* tiles);
        // Paints a tile at an x and y offset.
        void paint_tile(Tile* tile, int x_offset, int y_offset);
        // Prints the entropy of the tiles onto the grid
        void update_entropy(int* tiles);
        // Paints a grey / white square
        void paint_tile_square(double brightness, int x_offset, int y_offset);
        // Performs an iterative collapse, printing at each stage
        void perform_iteration();
        // Benchmarks the quantum grid n times.
        void perform_benchmarking(int n);
        // Collapses the algorithm, simple and easy
        void perform_collapse();
};

#endif