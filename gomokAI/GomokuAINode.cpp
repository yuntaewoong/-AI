#include "GomokuAINode.h"

GomokuAINode::GomokuAINode(GomokuBoard& board, int value)
{
	this->board = new GomokuBoard(board);//µöÄ«ÇÇ
	this->value = value;
}
GomokuAINode::~GomokuAINode()
{
	delete this->board;
}
void GomokuAINode::MakeTree(int depth)
{
	if (depth == 0)//base case
	{
		for (int i = 0; i < GomokuBoard::BOARD_SIZE; i++)
			for (int j = 0; j < GomokuBoard::BOARD_SIZE; j++)
				NewNode(j, i,EvaluateNode(j,i));
		return;
	}
	for (int i = 0; i < GomokuBoard::BOARD_SIZE; i++)
	{
		for (int j = 0; j < GomokuBoard::BOARD_SIZE; j++)
		{
			if(NewNode(j, i))
				nextNodes[nextNodes.size() - 1]->MakeTree(depth - 1);
		}
	}
}
GomokuBoard* GomokuAINode::GetMiniMaxResult()
{
	this->SetMaxValue();
	for (int i = 0; i < nextNodes.size(); i++)
	{
		if (this->value == nextNodes[i]->value)
			return nextNodes[i]->board;
	}
}
bool GomokuAINode::NewNode(int x, int y,int value)
{
	GomokuBoard* newBoard = new GomokuBoard(*board);
	if (newBoard->PutStone(x, y))
	{
		this->nextNodes.push_back(new GomokuAINode(*newBoard,value));
		return true;
	}
	else
		return false;
}
int GomokuAINode::EvaluateNode(int x,int y)
{
	return  board->GetBoardValue(x, y);
}
void GomokuAINode::SetMiniValue()
{
	if (nextNodes.empty())
		return;
	int temp = 0;
	for (int i = 0; i < nextNodes.size(); i++)
	{
		nextNodes[i]->SetMaxValue();
		if (nextNodes[i]->value <= temp)
			temp = nextNodes[i]->value;
	}
	this->value = temp;
}
void GomokuAINode::SetMaxValue()
{
	if (nextNodes.empty())
		return;
	int temp = 0;
	for (int i = 0; i < nextNodes.size(); i++)
	{
		nextNodes[i]->SetMiniValue();
		if (nextNodes[i]->value >= temp)
			temp = nextNodes[i]->value;
	}
	this->value = temp;
}