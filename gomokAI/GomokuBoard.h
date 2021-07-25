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
	static void GetDifference(GomokuBoard& board1, GomokuBoard& board2, int* x, int* y);//board1:������, board2:�����ǿ� �Ѽ� ���� ��,xy: �Ѽ��� ��ġ����
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
	int GetBoardValue(int x,int y);//���� �������� (x,y)�� ���� �������� ��ġ�� ��ġȭ�ؼ� ����
	bool IsEnd();
	~GomokuBoard();
private:
	void BlackBannedUpdate();//���� ������ ��ݼ� ����
	void DrawGrid();
	void DrawStone();
	void DrawBlackBanned();
	void DrawMouseOnRect();
	int Mouse2BoardPositionX(int mouseX);
	int Mouse2BoardPositionY(int mouseY);
};