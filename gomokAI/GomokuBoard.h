#pragma once
#include "GomokuBoardState.h"
#include "CustomRenderer.h"
#include "IUpdateObject.h"
#include "RenjuRuleManager.h"
#include "ConstValue.h"
class GomokuBoard : public IUpdateObject
{
private:
	int boardWidth;
	int boardHeight;
	int boardWhiteSpace;
	int mouseX=0;
	int mouseY=0;
	bool isEnd = false;
	GomokuBoardState** board;
	CustomRenderer* renderer;
	RenjuRuleManager* renjuRuleManager;
	Turn turn = Turn::BLACK_TURN;
public:
	GomokuBoard(CustomRenderer* renderer,int boardWidth,int boardHeight, int boardWhiteSpace);
	GomokuBoard(GomokuBoard& board);
	static const int BOARD_SIZE = 15;
	static void GetDifference(GomokuBoard& board1, GomokuBoard& board2, int* x, int* y);//board1:원본판, board2:원본판에 한수 놓은 판,xy: 한수의 위치리턴
	virtual void Update();
	void ChangeTurn();
	bool PutStone(int x,int y);
	bool PutStoneByMouse();
	void SetMousePosition(int x, int y);
	bool IsEmpty(int x,int y);
	bool IsBlackBanned(int x, int y);
	int GetMouseX();
	int GetMouseY();
	Turn GetTurn();
	int GetBoardValue(int x,int y);//현재 오목판의 (x,y)에 돌을 놓을때의 가치를 수치화해서 리턴
	bool IsEnd();
	~GomokuBoard();
private:
	void BlackBannedUpdate();//오목 보드의 흑금수 갱신
	void DrawGrid();
	void DrawStone();
	void DrawBlackBanned();
	void DrawMouseOnRect();
	int Mouse2BoardPositionX(int mouseX);
	int Mouse2BoardPositionY(int mouseY);
};