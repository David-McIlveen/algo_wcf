#ifndef QUANTUM_GRID
#define QUANTUM_GRID

#include "../tiles/tile.hpp"
#include "quantum_tile.hpp"

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

class QuantumGrid{
    public:
        // Desired x and y size, along with the tiles to fill that.
        QuantumGrid(int x, int y, int tile_count, bool*** ruleset);
        // Collapses the Grid all at once goes faster
        void collapse();
        // Collapses the Grid with a callback every time a tile is collapsed successfully
        void collapse(void (*callback)());
        // Deletes all Quantum tiles and resets the board.        
        void reset();
        // Gets the current entropy, updates when called
        int* get_entropy_grid();
        // Gets the current collapsed grid, updates when called.
        int* get_collapsed_grid();
        int get_x();
        int get_y();
        ~QuantumGrid();
    private:
        int _tile_count;
        int _x_size;
        int _y_size;
        bool*** _ruleset;
        // An array of X * Y tiles;
        QuantumTile** _tiles;
        // A grid with the IDs of all collapsed tiles
        int* _collapsed_grid;
        // A grid of the current entropy
        int* _entropy_grid;
        // Links tiles with one another
        void link_tiles();
        // Destroys all Quantum Tiles
        void destroy_all_tiles();
        // Populate all Quantum Tiles
        void populate_tiles();
        // Update the entropy tiles
        void update_entropy();
        // Update chosen tiles
        void update_choosen();
        // Gets a tile at a given x and y, returns nullptr if out of range
        QuantumTile* get_tile(int x, int y);
        void (*iterative_callback)(int* collapsed_grid, int* entropy_grid);
};

#endif