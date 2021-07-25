#include "GomokuAINode.h"
GomokuAINode::GomokuAINode(GomokuBoard& board, int value)
{
	this->board = new GomokuBoard(board);
	this->value = value;
}
GomokuAINode::GomokuAINode(GomokuBoard* board, int value)
{
	this->board = board;
	this->value = value;
}
GomokuAINode::~GomokuAINode()
{
	delete this->board;
	for each (GomokuAINode * node in nextNodes)
		delete node;
	nextNodes.clear();
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
			if (NewNode(j, i))
			{
				nextNodes.back()->MakeTree(depth - 1);
			}
		}
	}
}
int GomokuAINode::NumOfNode()
{
	int result = 0;
	result = NumOfNextNodes(nextNodes);
	return result;
}
int GomokuAINode::NumOfNextNodes(list<GomokuAINode*> nextNodes)
{
	int result = 0;
	if (nextNodes.empty())
		return 1;
	else
	{
		for (GomokuAINode* ptr : nextNodes)
		{
			result += NumOfNextNodes(ptr->nextNodes);
		}
	}
	return result;
}
int GomokuAINode::SizeOfNode()
{
	int result = 0;
	result = SizeOfNextNodes(nextNodes);
	return result;
}
int GomokuAINode::SizeOfNextNodes(list<GomokuAINode*> nextNodes)
{
	int result = 0;
	if (nextNodes.empty())
		return _msize(this) + _msize(this->board);
	else
	{
		for (GomokuAINode* ptr: nextNodes)
		{
			result += SizeOfNextNodes(ptr->nextNodes);
		}
	}
	return result;
}
GomokuBoard* GomokuAINode::GetMiniMaxResult()
{
	this->SetMaxValue();
	for (GomokuAINode* ptr : nextNodes)
	{
		if (this->value == ptr->value)
			return ptr->board;
	}
}
bool GomokuAINode::NewNode(int x, int y,int value)
{

	GomokuBoard* newBoard = new GomokuBoard(*board);//µöÄ«ÇÇ
	if (newBoard->PutStone(x, y))
	{
		this->nextNodes.push_back(new GomokuAINode(newBoard,value));
		return true;
	}
	else
	{
		delete newBoard;
		return false;
	}
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
	for (GomokuAINode* ptr : nextNodes)
	{
		ptr->SetMaxValue();
		if (ptr->value <= temp)
			temp = ptr->value;
	}
	this->value = temp;
}
void GomokuAINode::SetMaxValue()
{
	if (nextNodes.empty())
		return;
	int temp = 0;

	for (GomokuAINode* ptr : nextNodes)
	{
		ptr->SetMiniValue();
		if (ptr->value >= temp)
			temp = ptr->value;
	}
	this->value = temp;
}