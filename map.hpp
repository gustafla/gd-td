#ifndef MAP_HPP
#define MAP_HPP

#include "common.hpp"
#include "config.hpp"

typedef enum {TILE_ROAD, TILE_GROUND} TileType;

class Map {
    public:
        Map(Common* _common);
        ~Map();
        void draw();
    private:
        Common* common;
        TileType mapTiles[TILES_IN_ROW][TILES_IN_COLUMN];
        
        SDL_Surface* sprRoadTile;
        SDL_Surface* sprGroundTile;
};

#endif
