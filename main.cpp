#include "tiles/tile_parser.hpp"
#include "tiles/tile_writer.hpp"


OUTPUT_MODE choose_options(string option){
    if(option == "-whole" || option == "-w"){
        return WHOLE;
    } else if (option == "-time" || option == "-t"){
        return WHOLE_TIME;
    } else if (option == "-iteration" || option == "-i"){
        return ITERATION;
    } else if (option == "-grid-iteration" || option == "-g"){
        return GRID_ITERATION;
    } else {
        throw "No such argument: " + option + " exists.";
    }
}

int get_integer(const std::string& prompt) {
    int value;
    bool validInput = false;
    
    do {
        std::cout << prompt;
        
        // Try to read an integer
        if (std::cin >> value) {
            validInput = true;
        } else {
            // Clear the error flag
            std::cin.clear();
            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
        }
        
        // Discard any remaining characters in the input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
    } while (!validInput);
    
    return value;
}

int main(int argc, char* argv[]){
    OUTPUT_MODE choice = WHOLE;
    if(argc == 2){
        try{
            choice = choose_options(string(argv[1]));
        }
        catch(const char* e){
            std::cerr << e << endl;
            return -1;
        }
    }
    while(true){
        try{
            int x = get_integer("Please enter a X value: ");
            int y = get_integer("Please enter a Y value: ");
            TileParser parser = TileParser(fs::path("config/ruleset.png"), fs::path("config/config.txt"));
            cout << "Parsed" << endl;
            TileRuleSet* rules = parser.get_rule_set();
            std::vector<Tile*> tiles = parser.get_tiles();
            cout << "Got Data" << endl;
            QuantumGrid* grid = new QuantumGrid(x, y, tiles.size(), rules);
            cout << "Grid Made" << endl;
            TileWriter writer = TileWriter(fs::path("output"), tiles, grid);
            cout << "Writer Made" << endl;
            writer.run_algo("default", choice);
            cout << "Algorithm Run" << endl;
            delete rules;
            delete grid;
            for (int i = 0; i < tiles.size(); i++){
                delete tiles.at(i);
            }
            cout << "Cleaned Up" << endl;
        } catch (const char* e){
            cerr << e << endl;
        }
    }
    return 0;
}