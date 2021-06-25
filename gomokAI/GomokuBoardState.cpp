#include"GomokuBoardState.h"

GomokuBoardState::GomokuBoardState(GomokuBoardValue boardValue)
{
	this->boardValue = boardValue;
}
GomokuBoardState::GomokuBoardState()
{
	this->boardValue = EMPTY;
}