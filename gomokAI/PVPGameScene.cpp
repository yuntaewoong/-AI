#include "PVPGameScene.h"
PVPGameScene::PVPGameScene(CustomRenderer* customRenderer) : Scene(customRenderer)
{
	gomokuBoard = new GomokuBoard(customRenderer, WINDOW_WIDTH, WINDOW_HEIGHT, WHITE_SPACE);
	this->AddUpdateObject(gomokuBoard);
}
#include <iostream>
void PVPGameScene::EventHandling(SDL_Event event)
{
    switch (event.type)
    {
        case SDL_MOUSEMOTION:
            gomokuBoard->SetMousePosition(event.motion.x, event.motion.y);
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                gomokuBoard->PutStoneByMouse();
                break;
            }
            break;
    }
}
Scene* PVPGameScene::NextScene()
{
    Turn winnerTurn = (this->gomokuBoard->GetTurn() == Turn::BLACK_TURN) ? Turn::WHITE_TURN : Turn::BLACK_TURN;
	return new EndScene(this->customRenderer,winnerTurn);
}
void PVPGameScene::UpdateScene()
{
    if (this->gomokuBoard->IsEnd())
        ReadyToNextScene();
}