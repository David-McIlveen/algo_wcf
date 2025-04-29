#include "tiles/tile_parser.hpp"
#include "tiles/tile_writer.hpp"

OUTPUT_MODE choose_options(string option){
    if(option == "-whole" || option == "-w"){

    } else if (option == "-time" || option == "-t"){

    } else if (option == "-iteration" || option == "-i"){

    } else if (option == "-grid-iteration" || option == "-g"){
        
    } else {
        throw "No such argument: " + option + " exists.";
    }
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
    return 0;
}