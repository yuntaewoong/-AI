#pragma once
#include "GomokuBoard.h"
#include <vector>
class GomokuAINode
{
private:
	GomokuBoard* board;
	vector<GomokuAINode*> nextNodes;
	int value;
public:
	GomokuAINode(GomokuBoard& board,int value = 0);
	~GomokuAINode();
	void MakeTree(int depth);//depth�� ¦���� ����Ϻ��尡 �������, Ȧ���� ���Ϻ��尡 ������� 
	GomokuBoard* GetMiniMaxResult();
private:
	bool NewNode(int x,int y,int value = 0);//(x,y)�� ���� ���� ��带 ������ nextNodes�� push_back
	int EvaluateNode(int x,int y);//(x,y)�� ���������� ��ġ�� ����
	void SetMiniValue();//�ڽ� ������ value���� �ּڰ��� value�� ����
	void SetMaxValue();//�ڽ� ������ value���� �ִ��� value�� ����
};
