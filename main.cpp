//Le alibaba game

#include <iostream>
#include <SDL/SDL.h>
#include "cleanup.hpp"
#include "config.hpp"
#include "common.hpp"
#include "game_map.hpp"

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
    if (!screen)
        return -2;
    
    //The shared common state object
    Common* common = new Common(screen);
    
    //Set window text
    SDL_WM_SetCaption(GAME_NAME, NULL);
    
    GameMap map(common);
    
    //For timing and FPS measures
    unsigned int timeLast;
    int delay = 0;
    int frames = 0;
    int fpsLast = 0;
    int fps = 0;
    
    while (common->running)
	{	
        timeLast = SDL_GetTicks();
		SDL_PollEvent(&common->gameEvent);
        common->keystate = SDL_GetKeyState(NULL);
		
        //Quit if requested
		if (common->gameEvent.type == SDL_QUIT)
            common->running = false;
        //Quit if esc pressed (for now)
        if (common->gameEvent.type == SDL_KEYDOWN) {
			if (common->gameEvent.key.keysym.sym == SDLK_ESCAPE)
				common->running = false;
		}

        map.draw();

        //Updates the screen
		SDL_Flip(screen);
        
        //FPS check
        frames++;
        if (fpsLast+10000<SDL_GetTicks()) {
            fpsLast=SDL_GetTicks();
            fps = frames/10.0f;
            std::cout << "FPS: " << fps << std::endl;
            if (fps < (common->fps - 5))
				std::cout << "Target framerate not achieved! If this message repeats, your computer is not fast enough for intended gameplay!\n";
            frames = 0;
        }
        
        common->frame++;
	}
    
    return 0;
}
