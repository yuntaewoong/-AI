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
	void MakeTree(int depth);//depth가 짝수면 상대턴보드가 리프노드, 홀수면 내턴보드가 리프노드 
	int NumOfNode();
	int NumOfNextNodes(list<GomokuAINode*> nextNodes);
	int SizeOfNode();
	int SizeOfNextNodes(list<GomokuAINode*> nextNodes);
	GomokuBoard* GetMiniMaxResult();//MakeTree실행후 실행
private:
	bool NewNode(int x,int y,int value = 0);//(x,y)에 돌을 놓은 노드를 생성후 nextNodes에 push_back
	int EvaluateNode(int x,int y);//(x,y)에 놓았을시의 가치를 리턴
	void SetMiniValue();//자식 노드들의 value값중 최솟값을 value에 저장
	void SetMaxValue();//자식 노드들의 value값중 최댓값을 value에 저장
};
