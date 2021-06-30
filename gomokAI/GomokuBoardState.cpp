#include"GomokuBoardState.h"
GomokuBoardState::GomokuBoardState(GomokuBoardValue boardValue)
{
	this->boardValue = boardValue;
}
GomokuBoardState::GomokuBoardState()
{
	this->boardValue = GomokuBoardValue::EMPTY;
}
GomokuBoardValue GomokuBoardState::GetBoardValue()
{
	return this->boardValue;
}
bool GomokuBoardState::GetBlackBanned()
{
	return this->blackBanned;
}
void GomokuBoardState::SetBoardValue(GomokuBoardValue boardValue)
{
	this->boardValue = boardValue;
}
void GomokuBoardState::SetBlackBanned(bool blackBanned)
{
	this->blackBanned = blackBanned;
}