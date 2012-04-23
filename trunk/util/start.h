#include "SDL/SDL.h"
#include <stdlib.h>
#include <iostream>
namespace cham{
    namespace draw{
        void startup(){
            if (SDL_Init(SDL_INIT_VIDEO) < 0){
                std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
                exit(1);
            }
            atexit(SDL_Quit);
        }
    }
}
