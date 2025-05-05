#ifndef TILE_RULE_SET
#define TILE_RULE_SET

const int DIR_COUNT = 4;

class TileRuleSet{
    public:
        TileRuleSet(int tile_c);
        void set(bool value, int for_tile, int dir, int at);
        bool get(int for_tile, int dir, int at);
        void print();
        ~TileRuleSet();
    private:
        bool* _lookup;
        int _tile_c;
};

#endif