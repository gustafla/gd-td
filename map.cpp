#include "map.hpp"
#include "gfxutil.hpp"
#include "util.hpp"

Map::Map(Common* _common):
common(_common){
    for (int y=0; y<TILES_IN_COLUMN; y++) {
        for (int x=0; x<TILES_IN_ROW; x++) {
            mapTiles[x][y] = TILE_GROUND;
        }
    }
    file2surface("ground.png", &sprGroundTile);
}

Map::~Map() {
    SDL_FreeSurface(sprGroundTile);
}

void Map::draw() {
    SDL_Rect dst;
    for (int y=0; y<TILES_IN_COLUMN; y++) {
        for (int x=0; x<TILES_IN_ROW; x++) {
            dst = buildRect(x*TILE_SIZE, y*TILE_SIZE, TILE_SIZE, TILE_SIZE);
            SDL_BlitSurface(sprGroundTile, NULL, common->buffer, &dst);
        }
    }
}
