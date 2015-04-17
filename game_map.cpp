#include "game_map.hpp"
#include "gfxutil.hpp"
#include "util.hpp"
#include <fstream>
#include <cstdlib>
#include <iostream>

GameMap::GameMap(Common* _common, std::string _fileName):
common(_common),
fileName(_fileName) {
    loadFromFile();
    file2surface("ground.png", &sprGroundTile);
    file2surface("road.png", &sprRoadTile);
    file2surface("base.png", &sprBaseTile);
    file2surface("attack.png", &sprAttackTile);
}

GameMap::~GameMap() {
    SDL_FreeSurface(sprGroundTile);
    SDL_FreeSurface(sprRoadTile);
}

bool GameMap::checkValidity() {
    unsigned int bases = 0;
    unsigned int attacks = 0;
    TileType tmp;
    TileType tmpNeighbors[8]; //clockwise from the top
    for (int y=0; y<TILES_IN_COLUMN; y++) {
        for (int x=0; x<TILES_IN_ROW; x++) {
            tmp = mapTiles[x][y];
            
            if (tmp == TILE_GROUND)
                continue; //Ground tiles don't need special checking
                
            if (tmp == TILE_BASE) {
                bases++;
                continue;
            } else if (tmp == TILE_ATTACK) {
                attacks++;
                continue;
            } else if (tmp == TILE_UNDEF) { //These don't need neighbor check too because there are only one of them
                std::cout << "WTF! Something went horribly wrong while loading map " << fileName << ". Blame the devs, please./n";
                exit(-9001);
            }
            
            for (int i=0; i<8; i++) //All neighbors are not in map's area by default
                tmpNeighbors[i] = TILE_UNDEF;
                
            if (y!=0) //The following block of ifs is needed to avoid pointer errors
                tmpNeighbors[0] = mapTiles[x][y-1];
            if (x!=TILES_IN_ROW-1) {
                if (y!=0)
                    tmpNeighbors[1] = mapTiles[x+1][y-1];
                tmpNeighbors[2] = mapTiles[x+1][y];
                if (y!=TILES_IN_COLUMN-1)
                    tmpNeighbors[3] = mapTiles[x+1][y+1];
            }
            if (y!=TILES_IN_COLUMN-1)
                tmpNeighbors[4] = mapTiles[x][y+1];
            if (x!=0) {
                if (y!=TILES_IN_COLUMN-1)
                    tmpNeighbors[5] = mapTiles[x-1][y+1];
                tmpNeighbors[6] = mapTiles[x-1][y];
                if (y!=0)
                    tmpNeighbors[7] = mapTiles[x-1][y-1];
            }
            
            if (tmp == TILE_ROAD) { //Not needed to check current tile's type but let's do it anyway
                TileType a, b, c;
                for (int i = 0; i<8; i+=2) { //for every U/D/L/R neighbors that are "next to" each other
                    a = tmpNeighbors[i];
                    b = tmpNeighbors[(i+2)%8]; //Modulo to loop back to 0 when checking 6
                    c = tmpNeighbors[i+1];
                    if ((a == TILE_ROAD || a == TILE_BASE || a == TILE_ATTACK) && (b == TILE_ROAD || b == TILE_BASE || b == TILE_ATTACK)) {
                        if (c == TILE_ROAD || c == TILE_BASE || c == TILE_ATTACK) {
                            std::cout << "Incorrect path placement in " << fileName << ".\n";
                            return false;
                        }
                    }
                }
            }
        }
    }
    if (attacks != 1 || bases != 1)
        return false;
    
    return true;
}

void GameMap::loadFromFile() {
    std::ifstream inFile(fileName.c_str());
    if (!inFile.is_open())
    {
        std::cout << __FILE__ << ": " << __LINE__ << " : This file: " << fileName << ": No such file\n";
        exit(-2);
    }

    char tmp[TILES_IN_ROW][TILES_IN_COLUMN];
    for (int y=0; y<TILES_IN_COLUMN; y++)
        for (int x=0; x<TILES_IN_ROW; x++)
            tmp[x][y]='u';

    char nothing;
    for (int y=0; y<TILES_IN_COLUMN || inFile.eof(); y++) { //Horrible but it's the only way I got it working
        for (int x=0; x<TILES_IN_ROW; x++)
            inFile.read(&tmp[x][y], 1);
        inFile.read(&nothing, 1);
    }
    /*    if (tmp[TILES_IN_ROW-1][y] == 'u') {
            std::cout << fileName << ": Map's row size too small!\n";
            for (int y=0; y<TILES_IN_COLUMN; y++)
                std::cout << &tmp[0][y] << std::endl;
            exit(-2);
        }
        inFile.read(&nothing, 1);
    }*/
    if (tmp[TILES_IN_ROW-1][TILES_IN_COLUMN-1] == 'u') {
        std::cout << fileName << ": Map's column size too small!\n";
        for (int y=0; y<TILES_IN_COLUMN; y++)
            for (int x=0; x<TILES_IN_ROW; y++)
                std::cout << tmp[x][y];
        exit(-2);
    }
    
    for(int y=0; y<TILES_IN_COLUMN; y++) {
        for(int x=0; x<TILES_IN_ROW; x++) {
            if (tmp[x][y] == 'G')
                mapTiles[x][y] = TILE_GROUND;
            else if (tmp[x][y] == 'R')
                mapTiles[x][y] = TILE_ROAD;
            else if (tmp[x][y] == 'B')
                mapTiles[x][y] = TILE_BASE;
            else if (tmp[x][y] == 'A')
                mapTiles[x][y] = TILE_ATTACK;
            else {
                std::cout << "Unsupported tiles in " << fileName << ".\n";
                exit(-2);
            }
        }
    }
    
    if (!checkValidity()) {
        std::cout << fileName << ": incorrect layout!\n";
        exit(-2);
    }
}

void GameMap::draw() {
    SDL_Rect dst;
    SDL_Surface* toDraw;
    for (int y=0; y<TILES_IN_COLUMN; y++) {
        for (int x=0; x<TILES_IN_ROW; x++) {
            dst = buildRect(x*TILE_SIZE, y*TILE_SIZE, TILE_SIZE, TILE_SIZE);
            if (mapTiles[x][y] == TILE_GROUND)
                toDraw = sprGroundTile;
            else if (mapTiles[x][y] == TILE_ROAD)
                toDraw = sprRoadTile;
            else if (mapTiles[x][y] == TILE_BASE)
                toDraw = sprBaseTile;
            else if (mapTiles[x][y] == TILE_ATTACK)
                toDraw = sprAttackTile;
            SDL_BlitSurface(toDraw, NULL, common->buffer, &dst);
        }
    }
}
