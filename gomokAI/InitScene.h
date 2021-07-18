
#pragma once
#include "Scene.h"
#include "PVPGameScene.h"
#include "AIGameScene.h"
#include "CustomRenderer.h"
#include "SDL.h"
class InitScene : public Scene
{
private:
	bool isAI = false;
	bool isPVP = false;
	const int logoX = 200;
	const int logoY = 200;
	const int logoFontSize = 100;
	const SDL_Color logoColor = { 255,120,0,0 };
	const SDL_Color buttonColor = { 0,0,0,0 };
	const int aiGameButtonX = 300;
	const int aiGameButtonY = 400;
	const int aiGameButtonWidth = 200;
	const int aiGameButtonHeight = 100;
	const int aiGameButtonFontSize = 30;
	const SDL_Color aiGameButtonFontColor = { 255,0,0,0 };
	const int pvpGameButtonX = 300;
	const int pvpGameButtonY = 600;
	const int pvpGameButtonWidth = 200;
	const int pvpGameButtonHeight = 100;
	const int pvpGameButtonFontSize = 30;
	const SDL_Color pvpGameButtonFontColor = { 0,0,255,0 };
public:
	InitScene(CustomRenderer* customRenderer);
	virtual void EventHandling(SDL_Event);
	virtual Scene* NextScene();
	virtual void UpdateScene();
private:
	void DrawLogo();
	void DrawAIButton();
	void DrawPVPButton();
	bool isMouseOnAIButton(int mouseX, int mouseY);
	bool isMouseOnPVPButton(int mouseX, int mouseY);
};
