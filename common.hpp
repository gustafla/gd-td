#ifndef COMMON_HPP
#define COMMON_HPP

#include <SDL/SDL.h>

//Will be created at main() and a pointer to that passed around the entire game
class Common {
    public:
        Common(SDL_Surface* _buffer);
        
        //Probably the same as screen in main()
        SDL_Surface* buffer;
        
        bool running;
        
        //Event contains all kinds of per frame stuff like keyboard input and if the program has been requested to exit
        SDL_Event gameEvent;
        
        //Allows access to every key, "filled" at main()
        //TODO: Do we need to call GetKeyState each frame?
        Uint8* keystate;
        
        //What framerate we want to run at (just for reference)
        unsigned int fps;
        
        //What frame num we're at (might be useful?)
        unsigned int frame;
};

#endif
