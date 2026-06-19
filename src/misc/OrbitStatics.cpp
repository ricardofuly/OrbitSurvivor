#include "OrbitStatics.h"

OrbitStatics::OrbitStatics()
{
}

SDL_AppResult OrbitStatics::SDL_Fail()
{
    SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error: %s", SDL_GetError());
    return SDL_APP_FAILURE;
}

float OrbitStatics::CalcFPS(Uint64& LastCounter)
{
    Uint64 CurrentCounter = SDL_GetPerformanceCounter();
    
    float DeltaTime = static_cast<float>((CurrentCounter - LastCounter)) / static_cast<float>(SDL_GetPerformanceFrequency());
    
    LastCounter = CurrentCounter;
    
    float FPSValue = 1.0f / DeltaTime;
    
    return FPSValue;
}
