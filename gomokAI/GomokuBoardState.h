#pragma once
enum class GomokuBoardValue
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
	GomokuBoardValue GetBoardValue();
	bool GetBlackBanned();
	void SetBoardValue(GomokuBoardValue boardValue);
private:
	GomokuBoardValue boardValue;
	bool blackBanned = false;
};