
#pragma once
#include "Scene.h"
#include "ConstValue.h"
#include "GomokuBoard.h"
#include "EndScene.h"
class PVPGameScene : public Scene
{
public:
	PVPGameScene(CustomRenderer* customRenderer);
	virtual void EventHandling(SDL_Event event);
	virtual Scene* NextScene();
	virtual void UpdateScene();
private:
	GomokuBoard* gomokuBoard;
};