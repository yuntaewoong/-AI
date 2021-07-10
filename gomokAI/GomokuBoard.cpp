#include "GomokuBoard.h"
GomokuBoard::GomokuBoard(CustomRenderer* renderer, int boardWidth, int boardHeight, int boardWhiteSpace)
{
	this->board = new GomokuBoardState*[BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; i++)
		this->board[i] = new GomokuBoardState[BOARD_SIZE];
	this->renderer = renderer;
	this->renjuRuleManager = new RenjuRuleManager(this->board, BOARD_SIZE);
	this->boardWidth = boardWidth;
	this->boardHeight = boardHeight;
	this->boardWhiteSpace = boardWhiteSpace;
}
GomokuBoard::GomokuBoard(GomokuBoard& board)
{
	this->board = new GomokuBoardState * [BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; i++)
		this->board[i] = new GomokuBoardState[BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			this->board[i][j] = board.board[i][j];
		}
	}
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
bool GomokuBoard::PutStone(int x, int y)
{
	if (turn == Turn::BLACK_TURN && board[y][x].GetBlackBanned())
		return false;//검정턴에 검정돌을 놓으려는데 그곳이 흑금수일경우 착수금지
	if (board[y][x].GetBoardValue() != GomokuBoardValue::EMPTY)
		return false;//이미 채워진칸에 착수금지
	
	if (turn == Turn::BLACK_TURN)
		board[y][x].SetBoardValue(GomokuBoardValue::BLACK);
	else
		board[y][x].SetBoardValue(GomokuBoardValue::WHITE);
	BlackBannedUpdate();//흑금수 갱신
	ChangeTurn();//착수후 턴교체
	return true;
}
bool GomokuBoard::PutStoneByMouse()//gomokuBoard객체에 저장된 마우스 정보로 착수
{
	int rectWidth = boardWidth - 2 * boardWhiteSpace;
	int rectHeight = boardHeight - 2 * boardWhiteSpace;
	float gridWidth = rectWidth / (BOARD_SIZE - 1);
	float gridHeight = rectHeight / (BOARD_SIZE - 1);
	if (mouseX < boardWhiteSpace - gridWidth || mouseX >= boardWhiteSpace + rectWidth + gridWidth)
		return false;//x범위 초과시 리턴
	if (mouseY < boardWhiteSpace - gridHeight || mouseY >= boardWhiteSpace + rectHeight + gridHeight)
		return false;//y범위 초과시 리턴
	int boardX = Mouse2BoardPositionX(mouseX);
	int boardY = Mouse2BoardPositionY(mouseY);

	this->PutStone(boardX, boardY);
	return true;
}
void GomokuBoard::SetMousePosition(int x, int y)
{
	mouseX = x;
	mouseY = y;
}
bool GomokuBoard::IsEmpty(int x, int y)
{
	return this->board[y][x].GetBoardValue() == GomokuBoardValue::EMPTY;
}
bool GomokuBoard::IsBlackBanned(int x, int y)
{
	return this->board[y][x].GetBlackBanned();
}
int GomokuBoard::GetMouseX()
{
	return mouseX;
}
int GomokuBoard::GetMouseY()
{
	return mouseY;
}
Turn GomokuBoard::GetTurn()
{
	return turn;
}
int GomokuBoard::GetBoardValue(int x,int y)
{
	int value = 0;
	if (renjuRuleManager->IsFive(x, y, turn) || renjuRuleManager->IsOverline(x, y, turn))
		return 10000;
	if (renjuRuleManager->IsDoubleFour(x, y, turn) || renjuRuleManager->IsDoubleThree(x, y, turn))
		return 5000;
	if (renjuRuleManager->IsOpenFour(x, y, turn,1) || renjuRuleManager->IsOpenFour(x, y, turn, 2) 
		|| renjuRuleManager->IsOpenFour(x, y, turn, 3) || renjuRuleManager->IsOpenFour(x, y, turn, 4))
		return 5000;
	if (renjuRuleManager->IsFour(x,y,turn,1) || renjuRuleManager->IsFour(x, y, turn, 2)
		|| renjuRuleManager->IsFour(x, y, turn, 3) || renjuRuleManager->IsFour(x, y, turn, 4))
		value += 1000;
	if (renjuRuleManager->IsOpenThree(x, y, turn, 1) || renjuRuleManager->IsOpenThree(x, y, turn, 2)
		|| renjuRuleManager->IsOpenThree(x, y, turn, 3) || renjuRuleManager->IsOpenThree(x, y, turn, 4))
		value += 1000;
	return value;
}
GomokuBoard::~GomokuBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++)
		delete[] this->board[i];
	delete[] this->board;
}
void GomokuBoard::BlackBannedUpdate()
{
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			this->board[i][j].SetBlackBanned(renjuRuleManager->IsBlackBanned(j, i));
}
void GomokuBoard::DrawGrid()
{
	int rectWidth = boardWidth - 2 * boardWhiteSpace;
	int rectHeight = boardHeight - 2 * boardWhiteSpace;
	this->renderer->DrawColorChange(GOMOKUBOARD_COLOR);
	this->renderer->DrawFilledRect(boardWhiteSpace, boardWhiteSpace,rectWidth,rectHeight);
	float gridWidth = (float)rectWidth / (BOARD_SIZE-1);
	float gridHeight = (float)rectHeight / (BOARD_SIZE - 1);
	this->renderer->DrawColorChange(GRID_COLOR);
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
	float gridWidth = (float)rectWidth / (BOARD_SIZE - 1);
	float gridHeight = (float)rectHeight / (BOARD_SIZE - 1);
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
	float gridWidth = (float)rectWidth / (BOARD_SIZE - 1);
	float gridHeight = (float)rectHeight / (BOARD_SIZE - 1);
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
	float gridWidth = (float)rectWidth / (BOARD_SIZE - 1);
	float gridHeight = (float)rectHeight / (BOARD_SIZE - 1);
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
	float gridWidth = (float)rectWidth / (BOARD_SIZE - 1);
	int result = int((mouseX - boardWhiteSpace) / gridWidth + 0.5);
	return result <= 0 ? 0 : (result >= BOARD_SIZE ? BOARD_SIZE-1:result);
}
int GomokuBoard::Mouse2BoardPositionY(int mouseY)
{
	int rectHeight = boardHeight - 2 * boardWhiteSpace;
	float gridHeight = (float)rectHeight / (BOARD_SIZE - 1);
	int result = int((mouseY - boardWhiteSpace) / gridHeight + 0.5);
	return result <= 0 ? 0 : (result >= BOARD_SIZE ? BOARD_SIZE - 1 : result);
}