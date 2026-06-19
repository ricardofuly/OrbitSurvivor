#include "TextRenderer.h"

#include "misc/OrbitStatics.h"
#include "misc/OrbitTypes.h"

TextRenderer::TextRenderer(SDL_Renderer* Renderer)
{
    this->Renderer = Renderer;
}

TextRenderer::~TextRenderer()
{
    for (auto& [ID, Font] : Fonts)
    {
        TTF_CloseFont(Font);
    }
    
    Fonts.clear();
    
    TTF_Quit();
}

bool TextRenderer::Initialize()
{
    if (!TTF_Init())
    {
        OrbitStatics::SDL_Fail();
        return false;
    }
    return true;
}

bool TextRenderer::LoadFont(const std::string& ID, const std::string& Path, float Size)
{
    TTF_Font* Font = TTF_OpenFont(Path.c_str(), Size);

    if (!Font)
    {
        OrbitStatics::SDL_Fail();
        return false;
    }
    
    Fonts[ID] = Font;
    return true;
}

void TextRenderer::DrawText(const std::string& FontID, std::string& Text, Vector2 Position)
{
    DrawText(FontID, Text, Position, {255, 255, 255, 255});
}

void TextRenderer::DrawText(const std::string& FontID, const std::string& Text, Vector2 Position, SDL_Color Color)
{
    if (!Fonts.contains(FontID))
    {
        OrbitStatics::SDL_Fail();
        return;
    }
    
    TTF_Font* Font = Fonts[FontID];
    
    SDL_Surface* Surface = TTF_RenderText_Blended(Font, Text.c_str(), Text.length(), Color);

    if (!Surface)
    {
        OrbitStatics::SDL_Fail();
        return;
    }
    
    SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Surface);
    SDL_FRect Rect = {Position.X, Position.Y, static_cast<float>(Surface->w), static_cast<float>(Surface->h)};
    
    SDL_RenderTexture(Renderer, Texture, nullptr, &Rect);
    
    SDL_DestroyTexture(Texture);
    SDL_DestroySurface(Surface);
}
