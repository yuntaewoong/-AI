#include "GomokuBoard.h"
#include <iostream>
GomokuBoard::GomokuBoard(CustomRenderer* renderer, int boardWidth, int boardHeight, int boardWhiteSpace)
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
	this->DrawBlackBanned();
	this->DrawMouseOnRect();
}
void GomokuBoard::ChangeTurn()
{
	if (turn == Turn::BLACK_TURN)
		turn = Turn::WHITE_TURN;
	else
		turn = Turn::BLACK_TURN;
}
void GomokuBoard::PutStone(int x, int y)
{
	if (turn == Turn::BLACK_TURN && board[x][y].GetBlackBanned())
		return;//검정턴에 검정돌을 놓으려는데 그곳이 흑금수일경우 착수금지
	if (board[y][x].GetBoardValue() != GomokuBoardValue::EMPTY)
		return;//이미 채워진칸에 착수금지
	
	if (turn == Turn::BLACK_TURN)
		board[y][x].SetBoardValue(GomokuBoardValue::BLACK);
	else
		board[y][x].SetBoardValue(GomokuBoardValue::WHITE);

	ChangeTurn();//착수후 턴교체
}
void GomokuBoard::PutStoneByMouse()//gomokuBoard객체에 저장된 마우스 정보로 착수
{
	int rectWidth = boardWidth - 2 * boardWhiteSpace;
	int rectHeight = boardHeight - 2 * boardWhiteSpace;
	int gridWidth = rectWidth / (BOARD_SIZE - 1);
	int gridHeight = rectHeight / (BOARD_SIZE - 1);
	if (mouseX < boardWhiteSpace - gridWidth || mouseX >= boardWhiteSpace + rectWidth + gridWidth)
		return;//x범위 초과시 리턴
	if (mouseY < boardWhiteSpace - gridHeight || mouseY >= boardWhiteSpace + rectHeight + gridHeight)
		return;//y범위 초과시 리턴
	int boardX = Mouse2BoardPositionX(mouseX);
	int boardY = Mouse2BoardPositionY(mouseY);

	this->PutStone(boardX, boardY);
}
void GomokuBoard::SetMousePosition(int x, int y)
{
	mouseX = x;
	mouseY = y;
}
int GomokuBoard::GetMouseX()
{
	return mouseX;
}
int GomokuBoard::GetMouseY()
{
	return mouseY;
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
	int rectWidth = boardWidth - 2 * boardWhiteSpace;
	int rectHeight = boardHeight - 2 * boardWhiteSpace;
	this->renderer->DrawRect(boardWhiteSpace, boardWhiteSpace,rectWidth,rectHeight);
	int gridWidth = rectWidth / (BOARD_SIZE-1);
	int gridHeight = rectHeight / (BOARD_SIZE - 1);
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
	int rectWidth = boardWidth - 2 * boardWhiteSpace;
	int rectHeight = boardHeight - 2 * boardWhiteSpace;
	int gridWidth = rectWidth / (BOARD_SIZE - 1);
	int gridHeight = rectHeight / (BOARD_SIZE - 1);
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
void GomokuBoard::DrawBlackBanned()
{
	if (turn == Turn::WHITE_TURN)//백턴일때는 흑금수 출력 X
		return;
	int rectWidth = boardWidth - 2 * boardWhiteSpace;
	int rectHeight = boardHeight - 2 * boardWhiteSpace;
	int gridWidth = rectWidth / (BOARD_SIZE - 1);
	int gridHeight = rectHeight / (BOARD_SIZE - 1);
	renderer->DrawColorChange(BLACKBANNED_COLOR);
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j].GetBlackBanned() == true)
			{
				renderer->DrawLine(boardWhiteSpace + j * gridWidth - gridWidth * BLACKBANNED_SIZE,
					boardWhiteSpace + i * gridHeight - gridHeight * BLACKBANNED_SIZE,
					boardWhiteSpace + j * gridWidth + gridWidth * BLACKBANNED_SIZE,
					boardWhiteSpace + i * gridHeight + gridHeight * BLACKBANNED_SIZE);
				renderer->DrawLine(boardWhiteSpace + j * gridWidth - gridWidth  * BLACKBANNED_SIZE,
					boardWhiteSpace + i * gridHeight + gridHeight * BLACKBANNED_SIZE,
					boardWhiteSpace + j * gridWidth + gridWidth  * BLACKBANNED_SIZE,
					boardWhiteSpace + i * gridHeight - gridHeight * BLACKBANNED_SIZE);
			}
		}
	}
}
void GomokuBoard::DrawMouseOnRect()
{
	int rectWidth = boardWidth - 2 * boardWhiteSpace;
	int rectHeight = boardHeight - 2 * boardWhiteSpace;
	int gridWidth = rectWidth / (BOARD_SIZE - 1);
	int gridHeight = rectHeight / (BOARD_SIZE - 1);
	if (mouseX < boardWhiteSpace - gridWidth || mouseX >= boardWhiteSpace + rectWidth + gridWidth)
		return;//x범위 초과시 출력X
	if (mouseY < boardWhiteSpace - gridHeight || mouseY >= boardWhiteSpace + rectHeight + gridHeight)
		return;//y범위 초과시 출력X
	if (turn == Turn::WHITE_TURN)
		renderer->DrawColorChange(WHITESTONE_COLOR);
	else
		renderer->DrawColorChange(BLACKSTONE_COLOR);
	
	int boardMouseX = Mouse2BoardPositionX(mouseX);
	int boardMouseY = Mouse2BoardPositionY(mouseY);
	if (board[boardMouseY][boardMouseX].GetBoardValue() == GomokuBoardValue::EMPTY)
	{
		renderer->DrawFilledRect(boardWhiteSpace + boardMouseX * gridWidth - MOUSEON_SIZE / 2 * gridWidth,
			boardWhiteSpace + boardMouseY * gridHeight - MOUSEON_SIZE / 2 * gridHeight,
			gridWidth * MOUSEON_SIZE,
			gridHeight * MOUSEON_SIZE);
		renderer->DrawColorChange(BLACKSTONE_COLOR);
		renderer->DrawRect(boardWhiteSpace + boardMouseX * gridWidth - MOUSEON_SIZE / 2 * gridWidth,
			boardWhiteSpace + boardMouseY * gridHeight - MOUSEON_SIZE / 2 * gridHeight,
			gridWidth * MOUSEON_SIZE,
			gridHeight * MOUSEON_SIZE);
	}
}
int GomokuBoard::Mouse2BoardPositionX(int mouseX)
{
	int rectWidth = boardWidth - 2 * boardWhiteSpace;
	int gridWidth = rectWidth / (BOARD_SIZE - 1);
	int result = int((mouseX - boardWhiteSpace) / (float)gridWidth + 0.5);
	return result <= 0 ? 0 : (result >= BOARD_SIZE ? BOARD_SIZE-1:result);
}
int GomokuBoard::Mouse2BoardPositionY(int mouseY)
{
	int rectHeight = boardHeight - 2 * boardWhiteSpace;
	int gridHeight = rectHeight / (BOARD_SIZE - 1);
	int result = int((mouseY - boardWhiteSpace) / (float)gridHeight + 0.5);
	return result <= 0 ? 0 : (result >= BOARD_SIZE ? BOARD_SIZE - 1 : result);
}