#pragma once
#include "GomokuBoardState.h"
#include "CustomRenderer.h"
#include "IUpdateObject.h"
enum class Turn
{
	BLACK_TURN,
	WHITE_TURN
};


class GomokuBoard : public IUpdateObject
{
private:
	const int BOARD_SIZE = 19;
	const float BLACKBANNED_SIZE = 0.25;
	const float MOUSEON_SIZE = 0.5;
	const SDL_Color GRID_COLOR = { 0,0,0,0 };
	const SDL_Color WHITESTONE_COLOR = { 255,255,255,0 };
	const SDL_Color BLACKSTONE_COLOR = { 0,0,0,0 };
	const SDL_Color BLACKBANNED_COLOR = { 255,0,0,0 };
	int boardWidth;
	int boardHeight;
	int boardWhiteSpace;
	int mouseX=0;
	int mouseY=0;

	GomokuBoardState** board;
	CustomRenderer* renderer;
	Turn turn = Turn::BLACK_TURN;
public:
	GomokuBoard(CustomRenderer* renderer,int boardWidth,int boardHeight, int boardWhiteSpace);
	virtual void Update();
	void ChangeTurn();
	void PutStone(int x,int y);
	void PutStoneByMouse();
	void SetMousePosition(int x, int y);
	int GetMouseX();
	int GetMouseY();
	~GomokuBoard();
private:
	void DrawGrid();
	void DrawStone();
	void DrawBlackBanned();
	void DrawMouseOnRect();
	int Mouse2BoardPositionX(int mouseX);
	int Mouse2BoardPositionY(int mouseY);
};