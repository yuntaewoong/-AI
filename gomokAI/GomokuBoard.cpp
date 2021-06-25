#include "GomokuBoard.h"

GomokuBoard::GomokuBoard(CustomRenderer* renderer,int boardWidth,int boardHeight,int boardWhiteSpace)
{
	this->board = new GomokuBoardState*[BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; i++)
		this->board[i] = new GomokuBoardState[BOARD_SIZE];
	this->renderer = renderer;
	this->boardWidth = boardWidth;
	this->boardHeight = boardHeight;
	this->boardWhiteSpace = boardWhiteSpace;
}
void GomokuBoard::Update()
{
	this->DrawGrid();
	this->DrawStone();
}
GomokuBoard::~GomokuBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++)
		delete[] this->board[i];
	delete[] this->board;
}
void GomokuBoard::DrawGrid()
{
	this->renderer->DrawColorChange({ 0,0,0,0 });
	this->renderer->DrawRect(boardWhiteSpace, boardWhiteSpace, boardWidth - 2*boardWhiteSpace, boardHeight - 2*boardWhiteSpace);
}
void GomokuBoard::DrawStone()
{

}