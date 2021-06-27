#include "GomokuBoard.h"

GomokuBoard::GomokuBoard(CustomRenderer* renderer,float boardWidth,float boardHeight,float boardWhiteSpace)
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
	this->renderer->DrawColorChange(GRID_COLOR);
	float rectWidth = boardWidth - 2 * boardWhiteSpace;
	float rectHeight = boardHeight - 2 * boardWhiteSpace;
	this->renderer->DrawRect(boardWhiteSpace, boardWhiteSpace,rectWidth,rectHeight);
	
	float gridWidth = (float)rectWidth / (BOARD_SIZE-1);
	float gridHeight = (float)rectHeight / (BOARD_SIZE - 1);
	for (int i = 0; i < BOARD_SIZE-1; i++)
	{
		this->renderer->DrawLine(boardWhiteSpace + i * gridWidth,
			boardWhiteSpace,
			boardWhiteSpace + i * gridWidth,
			boardHeight - boardWhiteSpace);//가로선

		this->renderer->DrawLine(boardWhiteSpace,
			boardWhiteSpace + i * gridHeight,
			boardWhiteSpace + rectWidth,
			boardWhiteSpace + i * gridHeight);//세로선
	}
}
void GomokuBoard::DrawStone()
{
	float rectWidth = boardWidth - 2 * boardWhiteSpace;
	float rectHeight = boardHeight - 2 * boardWhiteSpace;
	float gridWidth = (float)rectWidth / (BOARD_SIZE - 1);
	float gridHeight = (float)rectHeight / (BOARD_SIZE - 1);
	this->board[0][0].SetBoardValue(GomokuBoardValue::BLACK);
	this->board[5][5].SetBoardValue(GomokuBoardValue::BLACK);
	this->board[18][18].SetBoardValue(GomokuBoardValue::WHITE);
	this->board[13][0].SetBoardValue(GomokuBoardValue::WHITE);
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			GomokuBoardValue boardValue = this->board[i][j].GetBoardValue();
			switch (boardValue)
			{
			case GomokuBoardValue::EMPTY:
				break;
			case GomokuBoardValue::BLACK:
				this->renderer->DrawColorChange(this->BLACKSTONE_COLOR);
				this->renderer->DrawFilledCircle(boardWhiteSpace + j * gridWidth, boardWhiteSpace + i * gridHeight, gridWidth / 2);
				break;
			case GomokuBoardValue::WHITE:
				this->renderer->DrawColorChange(this->WHITESTONE_COLOR);
				this->renderer->DrawFilledCircle(boardWhiteSpace + j * gridWidth, boardWhiteSpace + i * gridHeight, gridWidth / 2);
				this->renderer->DrawColorChange(this->BLACKSTONE_COLOR);
				this->renderer->DrawEmptyCircle(boardWhiteSpace + j * gridWidth, boardWhiteSpace + i * gridHeight, gridWidth / 2);
				break;
			default:
				break;
			}
		}
	}
}