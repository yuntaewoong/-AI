#pragma once
#include "GomokuBoard.h"
#include <list>
class GomokuAINode
{
private:
	GomokuBoard* board = nullptr;
	list<GomokuAINode*> nextNodes;
	int value;
	int x;
	int y;
public:
	GomokuAINode(GomokuBoard& board,int value = 0);
	GomokuAINode(GomokuBoard* board, int value = 0);
	~GomokuAINode();
	void MakeTree(int depth);//depth�� ¦���� ����Ϻ��尡 �������, Ȧ���� ���Ϻ��尡 ������� 
	int NumOfNode();
	int NumOfNextNodes(list<GomokuAINode*> nextNodes);
	int SizeOfNode();
	int SizeOfNextNodes(list<GomokuAINode*> nextNodes);
	GomokuBoard* GetMiniMaxResult();//MakeTree������ ����
private:
	bool NewNode(int x,int y,int value = 0);//(x,y)�� ���� ���� ��带 ������ nextNodes�� push_back
	int EvaluateNode(int x,int y);//(x,y)�� ���������� ��ġ�� ����
	void SetMiniValue();//�ڽ� ������ value���� �ּڰ��� value�� ����
	void SetMaxValue();//�ڽ� ������ value���� �ִ��� value�� ����
};
