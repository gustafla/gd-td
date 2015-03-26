//Le alibaba game

#include <iostream>
#include <SDL/SDL.h>
#include "cleanup.hpp"
#include "config.hpp"

//using namespace std;
//Let's not use std all the time, use std::* instead
//std::cout << "stuff\n"; for example

int main(int argc, char* argv[])
{
    //Safely quit SDL at any exit case
    atexit(cleanup);

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return -1;

    //(Pretty much) everything is an SDL_Surface (pointer), so is our front screen.
    SDL_Surface *screen;
    
    //Open the screen (16bit, hardware where available)
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 16, SDL_HWSURFACE);

    return 0;
}
