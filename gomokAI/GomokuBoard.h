#pragma once
#include "GomokuBoardState.h"
#include "CustomRenderer.h"
#include "IUpdateObject.h"
class GomokuBoard : public IUpdateObject
{
private:
	const int BOARD_SIZE = 19;
	int boardWidth;
	int boardHeight;
	int boardWhiteSpace;
	GomokuBoardState** board;
	CustomRenderer* renderer;
public:
	GomokuBoard(CustomRenderer* renderer,int boardWidth,int boardHeight,int boardWhiteSpace);
	virtual void Update();
	~GomokuBoard();
private:
	void DrawGrid();
	void DrawStone();
};