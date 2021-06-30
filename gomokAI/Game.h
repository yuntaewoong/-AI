
#pragma once

#include <SDL.h>
#include "CustomRenderer.h"
#include "IUpdateObject.h"
#include "GomokuBoard.h"
#include <vector>
class Game
{
private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    CustomRenderer customRenderer;
    GomokuBoard* gomokuBoard;
    vector<IUpdateObject*> updateObjects;//업데이트함수 실행대상 오브젝트들
    bool m_Running;
    float m_DeltaTime;
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 800;
    const int WHITE_SPACE = 100;
public:
    void Start();
    void Stop();

private:
    void GameLoop();
    void HandleEvents();
    void Update(float deltaTime);
};