#include "Game.h"
#include <iostream>
#include <SDL_ttf.h>
#include "Timer.h"
#include <string>
void Game::Start()
{
    m_Running = true;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "ERROR: Failed to initialise SDL!" << std::endl;
        Stop();
    }


    if (TTF_Init() == -1)
    {
        std::cout << "ERROR: Failed to initialise SDL_ttf!" << std::endl;
        Stop();
    }

    m_Window = SDL_CreateWindow("RPG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (!m_Window)
    {
        std::cout << "ERROR: Failed to create SDL_Window!" << std::endl;
        Stop();
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (!m_Renderer)
    {
        std::cout << "ERROR: Failed to create SDL_Renderer!" << std::endl;
        Stop();
    }
    customRenderer = CustomRenderer(m_Renderer);
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);

    GameLoop();
}

void Game::Stop()
{
    SDL_DestroyWindow(m_Window);
    SDL_DestroyRenderer(m_Renderer);
    m_Window = nullptr;
    m_Renderer = nullptr;

    SDL_Quit();

    m_Running = false;
}

void Game::GameLoop()
{
    Timer deltaTimer;
    deltaTimer.Start();
    while (m_Running)
    {
        HandleEvents();//���� �̺�Ʈó��
        Update(m_DeltaTime);//���� ������Ʈ����
        m_DeltaTime = static_cast<float>(deltaTimer.GetTicks()) / 1000.0f;
        deltaTimer.Start();
        Render();
    }
    Stop();
}
void Game::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        m_Running = false;
        break;
    }
}
void Game::Update(float deltaTime)
{
}

void Game::Render()
{
    customRenderer.DrawColorChange({ 255,255,255 });
    customRenderer.ClearRenderer();
    customRenderer.DrawColorChange({ 255,255,0 });
    customRenderer.DrawFilledCircle(100, 100, 100);
    customRenderer.Render();
}