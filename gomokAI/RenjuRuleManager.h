#pragma once
#include "GomokuBoardState.h"
class RenjuRuleManager//���ַ� ������Ʈ, �Լ������� ����� gomokuBoardValue���� �ٲ�������
{
private:
	GomokuBoardState** board;
	int BOARD_SIZE;
public:
	RenjuRuleManager(GomokuBoardState** board,int BOARD_SIZE);
	bool IsBlackBanned(int x, int y);
private:
	void SetStone(int x, int y, GomokuBoardValue stone);
	bool IsFive(int x, int y, Turn turn);
	bool IsOverline(int x, int y,Turn turn);
	bool IsFive(int x, int y, Turn turn, int dir);
	bool IsFour(int x, int y, Turn turn, int dir);
	int  IsOpenFour(int x, int y, Turn turn, int dir);
	bool IsOpenThree(int x, int y, Turn turn, int dir);
	bool IsDoubleFour(int x, int y,Turn turn);
	bool IsDoubleThree(int x, int y,Turn turn);
	GomokuBoardValue Turn2GomokuBoardValue(Turn turn);
};