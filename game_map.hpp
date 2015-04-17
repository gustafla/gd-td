#ifndef MAP_HPP
#define MAP_HPP

#include "common.hpp"
#include "config.hpp"
#include <string>

// Only one base and attack per map.

// If a road has two or more cornering road neigbors
// the tile in between them cannot be a road or base or attack.

// A base and attack tile have to have a road neighbor

/*
 * G R G
 * R R R
 * G R G
 * 
 * OK
 */
    
 /* |
  * v 
  * R R G
  * R R G
  * G G G
  * 
  * No
  */
  
 /*
  * G R G
  * G R G
  * G R G
  * 
  * OK
  */

typedef enum {TILE_ROAD, TILE_GROUND, TILE_BASE, TILE_ATTACK, TILE_UNDEF} TileType;

class GameMap {
    public:
        GameMap(Common* _common, std::string _fileName="map0.map");
        ~GameMap();
        void draw();
    private:
        std::string fileName;
        bool checkValidity();
        void loadFromFile();
        Common* common;
        TileType mapTiles[TILES_IN_ROW][TILES_IN_COLUMN];
        
        SDL_Surface* sprRoadTile;
        SDL_Surface* sprGroundTile;
        SDL_Surface* sprBaseTile;
        SDL_Surface* sprAttackTile;
};

#endif
