#include "GameSettings.h"

#include "graphics/TextRenderer.h"

GameSettings::GameSettings()
{
    InitFlags = SDL_INIT_VIDEO | SDL_INIT_AUDIO;
    ScreenSize = {1280, 720};
}

void GameSettings::UpdateWindow(SDL_Window* InWindow)
{
    App.Window = InWindow;
}

void GameSettings::UpdateRenderer(SDL_Renderer* InRenderer)
{
    App.Renderer = InRenderer;
}

void GameSettings::CreateTextRenderer(SDL_Renderer* Renderer)
{
    App.TextRenderer = new TextRenderer(Renderer);
}

void GameSettings::LoadTextFont(const std::string& FontID, const std::string& Path, float Size) const
{
    App.TextRenderer->LoadFont(FontID, Path, Size);
}
