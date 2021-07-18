
#pragma once

#include <SDL.h>
#include "CustomRenderer.h"
#include "IUpdateObject.h"
#include "GomokuBoard.h"
#include "Scene.h"
#include "InitScene.h"
#include "PVPGameScene.h"
#include "AIGameScene.h"
#include "ConstValue.h"
#include <vector>

class Game
{
private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    CustomRenderer* customRenderer;
    GomokuBoard* gomokuBoard;
    Scene* currentScene;
    vector<IUpdateObject*> updateObjects;//������Ʈ�Լ� ������ ������Ʈ��
    bool m_Running;
    float m_DeltaTime;
public:
    void Start();
    void Stop();

private:
    void GameLoop();
    void HandleEvents();
    void Update(float deltaTime);
    void ChangeScene();
};