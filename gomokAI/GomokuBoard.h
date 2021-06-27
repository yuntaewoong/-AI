#pragma once
#include "GomokuBoardState.h"
#include "CustomRenderer.h"
#include "IUpdateObject.h"
class GomokuBoard : public IUpdateObject
{
private:
	const int BOARD_SIZE = 19;
	const SDL_Color GRID_COLOR = { 0,0,0,0 };
	const SDL_Color WHITESTONE_COLOR = { 255,255,255,0 };
	const SDL_Color BLACKSTONE_COLOR = { 0,0,0,0 };
	float boardWidth;
	float boardHeight;
	float boardWhiteSpace;
	GomokuBoardState** board;
	CustomRenderer* renderer;
public:
	GomokuBoard(CustomRenderer* renderer,float boardWidth,float boardHeight,float boardWhiteSpace);
	virtual void Update();
	~GomokuBoard();
private:
	void DrawGrid();
	void DrawStone();
};