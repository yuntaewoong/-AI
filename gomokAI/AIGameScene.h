
#pragma once
#include "Scene.h"
#include "EndScene.h"
#include "GomokuBoard.h"
#include "GomokuAINode.h"
class AIGameScene : public Scene
{
private:
	GomokuBoard* gomokuBoard;
	Turn playerTurn;
	int miniMaxTreeDepth = 4;
public:
	AIGameScene(CustomRenderer* customRenderer,Turn playerTurn);
	virtual void EventHandling(SDL_Event);
	virtual Scene* NextScene();
	virtual void UpdateScene();
private:
	void AIProcess();
};
