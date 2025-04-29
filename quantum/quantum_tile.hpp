#ifndef QUANTUM_TILE
#define QUANTUM_TILE

#include <vector>

const int DEFAULT_CHOSEN_TILE = -1;
const int NUMBER_OF_DIRECTIONS = 4;

class QuantumTile{
    public:
        // Number of tiles has the range of all ids from 0 to T - 1
        QuantumTile(int no_of_tiles, bool*** rule_book);
        // Sets a reference to the adjacent tiles
        void set_tile_adjacent(int placement, QuantumTile* tile);
        // How many tiles are left to choose from, 0 when collapsed
        int get_entropy();
        // Collapses tile and sets the new entropy / rule set of the ones around it
        // Does nothing and returns false if collapsed already, returns true if it collapses
        void collapse();
        // Collapses the tile, but if it does it calls the callback function
        void collapse(void (*callback)());
        // Returns the ID of the chosen tile, errors if not collapsed
        int get_chosen_tile();
        // Delete choices (Grid will delete all tiles)
        ~QuantumTile();
    private:
        // Alters the choices of the tile, errors if already collapsed
        void alter_ruleset(bool* ruleset);
        // Makes a choice from the available selections
        void make_choice();
        // Does the selection and update
        void collapse_affect();
        // Orders adjacent tiles by entropy
        void order_adj_tiles();
        // A T * 4 * T boolean array that contains the rules for every tile
        bool*** _rule_book;
        // Stored number of tiles
        int _no_of_tiles;
        // Initalized with nullptrs, there are 4 (0 = Up, 1 = Down, 2 = Left, 3 = Right)
        QuantumTile** _adjacent_tiles;
        // Empty until ready to collapse
        std::vector<QuantumTile*> to_collapse;
        // The chosen id of the tile when collapsed, initalized to -1 when not chosen.
        int _chosen_tile = DEFAULT_CHOSEN_TILE;
        // The entropy or remaining number of choices left that a tile can be collapsed into, 0 when collapsed
        // Initialized at number of tiles.
        int _entropy;
        // The choices that a given tile can make set to all true initially
        bool* _choices;
};

// Gets a random int value from 0 to max (exclusive)
int random_int(int max);

#endif