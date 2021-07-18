#include "EndScene.h"

EndScene::EndScene(CustomRenderer* customRenderer,Turn winner) : Scene(customRenderer)
{
	this->winner = winner;
}
void EndScene::EventHandling(SDL_Event event)
{
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)//왼쪽 마우스 클릭
			if (IsMouseOnInitButton(event.button.x, event.button.y))
				ReadyToNextScene();
		break;
	}
}
Scene* EndScene::NextScene()
{
	return new InitScene(customRenderer);
}
void EndScene::UpdateScene()
{
	DrawScene();
}
void EndScene::DrawScene()
{
	DrawResultMessage();
	DrawInitButton();
}
void EndScene::DrawResultMessage()
{
	string resultString;
	if (winner == Turn::BLACK_TURN)
		resultString = "Winner is Black";
	else
		resultString = "Winner is White";
	customRenderer->DrawText(resultString, this->resultMessageX, this->resultMessageY, resultMessageFontSize, resultMessageColor);
}
void EndScene::DrawInitButton()
{
	customRenderer->DrawColorChange(this->initButtonColor);
	customRenderer->DrawFilledRect(this->initButtonX, this->initButtonY, this->initButtonWidth,this->initButtonHeight);

	customRenderer->DrawColorChange(this->initButtonMessageFontColor);
	customRenderer->DrawText("Home", this->initButtonX, this->initButtonY, this->initButtonMessageFontSize, this->initButtonMessageFontColor);
}
bool EndScene::IsMouseOnInitButton(int x, int y)
{
	if (x > this->initButtonX && x < this->initButtonX + this->initButtonWidth &&
		y > this->initButtonY && y < this->initButtonY + this->initButtonHeight)
		return true;
	else
		return false;
}