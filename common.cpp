#include "common.hpp"
#include <SDL/SDL.h>
#include "config.hpp"

Common::Common(SDL_Surface* _buffer):
buffer(_buffer),
running(true),
fps(FPS_TARGET),
frame(0) {
    
}
