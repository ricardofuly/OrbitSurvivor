#define SDL_MAIN_USE_CALLBACKS  // This is necessary for the new callbacks API. To use the legacy API, don't define this. 

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "SDL3/SDL.h"
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h>
#include <format>
#include <string>
#include "misc/OrbitStatics.h"
#include "graphics/TextRenderer.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "SDL3_mixer/SDL_mixer.h"
#include "settings/GameSettings.h"

GameSettings* Settings = new GameSettings;

SDL_AppResult SDL_AppInit(void** AppState, int Args, char* Argv[])
{
    if (not SDL_Init(Settings->GetInitFlags())) return OrbitStatics::SDL_Fail();
    if (not TTF_Init()) return OrbitStatics::SDL_Fail();
    if (not MIX_Init()) return OrbitStatics::SDL_Fail();
    
    SDL_Window* Window = SDL_CreateWindow(Settings->GetAppContext().AppTitle, static_cast<int>(Settings->GetWindowSize().X), static_cast<int>(Settings->GetWindowSize().Y),Settings->GetAppContext().Flags);
    if (not Window) return OrbitStatics::SDL_Fail();
    
    SDL_Renderer* Renderer = SDL_CreateRenderer(Window, nullptr);
    if (not Renderer) return OrbitStatics::SDL_Fail();
    
    Settings->UpdateRenderer(Renderer);
    Settings->UpdateWindow(Window);
    
    Settings->CreateTextRenderer(Renderer);
    Settings->LoadTextFont("Default", "resources/Inter-VariableFont.ttf", 24);
    
    SDL_SetRenderVSync(Renderer, 1);
    
    *AppState = Settings->GetAppContextPtr();
    
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* AppState, SDL_Event* Event)
{
    auto* App = static_cast<AppContext*>(AppState);

    if (Event->type == SDL_EVENT_QUIT) App->App_Quit = SDL_APP_SUCCESS;
    
    return SDL_APP_CONTINUE;
}

Uint64 LastCounter = SDL_GetPerformanceCounter();

SDL_AppResult SDL_AppIterate(void* AppState)
{
    auto* App = static_cast<AppContext*>(AppState);
    
    float FPSValue = OrbitStatics::CalcFPS(LastCounter);
    std::string FPSText = std::format("FPS: {:.2}", FPSValue);
    
    SDL_RenderClear(App->Renderer);
    
    App->TextRenderer->DrawText("Default", FPSText, {20,20});
    
    SDL_RenderPresent(App->Renderer);
    
    return  App->App_Quit;
}

void SDL_AppQuit(void* AppState, SDL_AppResult Result)
{
    auto* App = static_cast<AppContext*>(AppState);

    if (App)
    {
        SDL_DestroyRenderer(App->Renderer);
        SDL_DestroyWindow(App->Window);
        
        //@TODO: Implement MIX
    }
    
    TTF_Quit();
    MIX_Quit();
    
    SDL_Log("Application Quit Successfully");
    SDL_Quit();
}
