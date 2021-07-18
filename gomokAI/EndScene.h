#pragma once
#include "Scene.h"
#include "CustomRenderer.h"
#include "InitScene.h"
#include "GomokuBoardState.h"
class EndScene : public Scene
{
private:
	Turn winner;
	const int resultMessageX = 300;
	const int resultMessageY = 200;
	const int resultMessageFontSize = 65;
	const SDL_Color resultMessageColor = { 0,0,0,0 };
	const int initButtonX = 300;
	const int initButtonY = 500;
	const int initButtonWidth = 200;
	const int initButtonHeight = 100;
	const SDL_Color initButtonColor = { 0,0,0,0 };
	const int initButtonMessageFontSize = 50;
	const SDL_Color initButtonMessageFontColor = { 255,255,255,0 };
public:
	EndScene(CustomRenderer* customRenderer,Turn winner);
	virtual void EventHandling(SDL_Event event);
	virtual Scene* NextScene();
	virtual void UpdateScene();
private:
	void DrawScene();
	void DrawResultMessage();
	void DrawInitButton();
	bool IsMouseOnInitButton(int x, int y);
};
