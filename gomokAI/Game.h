
#pragma once

#include <SDL.h>
#include "CustomRenderer.h"

class Game
{
private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    CustomRenderer customRenderer;
    bool m_Running;
    float m_DeltaTime;

public:
    void Start();
    void Stop();

private:
    void GameLoop();
    void HandleEvents();
    void Update(float deltaTime);
    void Render();
};