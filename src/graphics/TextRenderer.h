#pragma once
#include <string>
#include <unordered_map>
#include <SDL3_ttf/SDL_ttf.h>

#include "SDL3/SDL_render.h"

struct Vector2;

class TextRenderer
{
public:
    explicit TextRenderer(SDL_Renderer* Renderer);
    ~TextRenderer();
    
    bool Initialize();
    
    bool LoadFont(const std::string& ID, const std::string& Path, float Size);
    void DrawText(const std::string& FontID, std::string& Text, Vector2 Position);
    
    void DrawText(const std::string& FontID, const std::string& Text, Vector2 Position, SDL_Color Color);
    
private:
    SDL_Renderer* Renderer = nullptr;
    
    std::unordered_map<std::string, TTF_Font*> Fonts;
};
