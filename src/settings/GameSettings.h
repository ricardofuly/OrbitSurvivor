#pragma once

#include <string>
#include <SDL3/SDL.h>
#include "misc/OrbitTypes.h"

class TextRenderer;

struct AppContext
{
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    const char* AppTitle = "Orbit Survivors";
    SDL_WindowFlags Flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY;
    TextRenderer* TextRenderer = nullptr;
    SDL_AppResult App_Quit = SDL_APP_CONTINUE;
};

class GameSettings
{
public:
    GameSettings();
    
    Vector2 GetWindowSize() const { return ScreenSize; }
    AppContext GetAppContext() const { return App; }
    SDL_InitFlags GetInitFlags() const { return InitFlags; }
    AppContext* GetAppContextPtr() { return &App; }
    
    void UpdateWindow(SDL_Window* InWindow);
    void UpdateRenderer(SDL_Renderer* InRenderer);
    
    void CreateTextRenderer(SDL_Renderer* Renderer);
    void LoadTextFont(const std::string& FontID, const std::string& Path, float Size) const;
    
private:
    Vector2 ScreenSize;
    AppContext App;
    SDL_InitFlags InitFlags;
};
