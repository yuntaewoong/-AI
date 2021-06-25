#pragma once
enum GomokuBoardValue
{
	EMPTY,
	WHITE,
	BLACK
};



class GomokuBoardState
{
public:
	GomokuBoardState();
	GomokuBoardState(GomokuBoardValue boardValue);
private:
	GomokuBoardValue boardValue;
	bool blackBanned = false;
};