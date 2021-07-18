#include "InitScene.h"
InitScene::InitScene(CustomRenderer* customRenderer) : Scene(customRenderer)
{

}
void InitScene::EventHandling(SDL_Event event)
{
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)//왼쪽 마우스 클릭
			{
				if (isMouseOnAIButton(event.button.x, event.button.y))
				{
					ReadyToNextScene();
					isAI = true;
				}
				else if (isMouseOnPVPButton(event.button.x, event.button.y))
				{
					ReadyToNextScene();
					isPVP = true;
				}
			}
			break;
	}
}
Scene* InitScene::NextScene()
{
	if (isAI)
		return new AIGameScene(this->customRenderer,Turn::BLACK_TURN);
	else if (isPVP)
		return new PVPGameScene(this->customRenderer);
}
void InitScene::UpdateScene()
{
	this->DrawLogo();
	this->DrawAIButton();
	this->DrawPVPButton();
}
void InitScene::DrawLogo()
{
	customRenderer->DrawColorChange(this->logoColor);
	customRenderer->DrawText("Gomoku", this->logoX, this->logoY, this->logoFontSize, this->logoColor);
}
void InitScene::DrawAIButton()
{
	customRenderer->DrawColorChange(this->buttonColor);
	customRenderer->DrawFilledRect(aiGameButtonX, aiGameButtonY, aiGameButtonWidth, aiGameButtonHeight);

	customRenderer->DrawColorChange(this->aiGameButtonFontColor);
	customRenderer->DrawText("AI Battle", aiGameButtonX, aiGameButtonY, aiGameButtonFontSize, aiGameButtonFontColor);
}
void InitScene::DrawPVPButton()
{
	customRenderer->DrawColorChange(this->buttonColor);
	customRenderer->DrawFilledRect(pvpGameButtonX, pvpGameButtonY, pvpGameButtonWidth, pvpGameButtonHeight);

	customRenderer->DrawColorChange(this->pvpGameButtonFontColor);
	customRenderer->DrawText("PVP Battle", pvpGameButtonX, pvpGameButtonY, pvpGameButtonFontSize, pvpGameButtonFontColor);
}
bool InitScene::isMouseOnAIButton(int mouseX, int mouseY)
{
	return mouseX < aiGameButtonX + aiGameButtonWidth &&
		mouseX > aiGameButtonX &&
		mouseY < aiGameButtonY + aiGameButtonHeight &&
		mouseY > aiGameButtonY;
}
bool InitScene::isMouseOnPVPButton(int mouseX, int mouseY)
{
	return mouseX < pvpGameButtonX + pvpGameButtonWidth &&
		mouseX > pvpGameButtonX &&
		mouseY < pvpGameButtonY + pvpGameButtonHeight &&
		mouseY > pvpGameButtonY;
}