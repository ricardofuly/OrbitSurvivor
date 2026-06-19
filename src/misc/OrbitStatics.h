#pragma once

#include "SDL3/SDL.h"

class OrbitStatics
{
public:
    OrbitStatics();
    
    static SDL_AppResult SDL_Fail();
    
    static float CalcFPS(Uint64& LastCounter);
};
