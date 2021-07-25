#include "AIGameScene.h"
#include <iostream>
AIGameScene::AIGameScene(CustomRenderer* customRenderer,Turn playerTurn) : Scene(customRenderer)
{
    gomokuBoard = new GomokuBoard(customRenderer, WINDOW_WIDTH, WINDOW_HEIGHT, WHITE_SPACE);
    this->playerTurn = playerTurn;
    this->AddUpdateObject(gomokuBoard);
}
void AIGameScene::EventHandling(SDL_Event event)
{
    if (this->playerTurn != gomokuBoard->GetTurn())//AI턴일시 player입력제한
        return;
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
            AIProcess();//AI턴진행
            break;
        }
        break;
    }
}
Scene* AIGameScene::NextScene()
{
	Turn winnerTurn = (this->gomokuBoard->GetTurn() == Turn::BLACK_TURN) ? Turn::WHITE_TURN : Turn::BLACK_TURN;
	return new EndScene(this->customRenderer, winnerTurn);
}
void AIGameScene::UpdateScene()
{
	if (this->gomokuBoard->IsEnd())
		ReadyToNextScene();
}
#include <iostream>
void AIGameScene::AIProcess()
{
    GomokuAINode* gomokuAINode = new GomokuAINode(*this->gomokuBoard);
    gomokuAINode->MakeTree(0);
    GomokuBoard* result = gomokuAINode->GetMiniMaxResult();//result: ai에 의한 수를 둔 gomokuBOard
    std::cout << gomokuAINode->NumOfNode() << std::endl;
    std::cout << gomokuAINode->SizeOfNode() << std::endl;
    int x, y;
    result->GetDifference(*this->gomokuBoard, *result, &x, &y);
    std::cout << "x: " << x<< "y: " << y<< std::endl;


    gomokuBoard->PutStone(x, y);
    delete gomokuAINode;
}