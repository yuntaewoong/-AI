#include "RenjuRuleManager.h"
#include <iostream>
RenjuRuleManager::RenjuRuleManager(GomokuBoardState** board,int BOARD_SIZE)
{
	this->BOARD_SIZE = BOARD_SIZE;
	this->board = board;
}
bool RenjuRuleManager::IsBlackBanned(int x, int y)
{
	if (board[y][x].GetBoardValue() != GomokuBoardValue::EMPTY)
		return false;
	else
	{
		if (IsOverline(x, y, Turn::BLACK_TURN) || IsDoubleFour(x, y, Turn::BLACK_TURN) ||  IsDoubleThree(x, y, Turn::BLACK_TURN))
			return true;
	}
}
void RenjuRuleManager::SetStone(int x, int y, GomokuBoardValue stone)
{
	board[y][x].SetBoardValue(stone);
}
bool RenjuRuleManager::IsFive(int x, int y, Turn turn)
{
	if (board[y][x].GetBoardValue() != GomokuBoardValue::EMPTY)
		return false;
	return IsFive(x, y, turn, 1) || IsFive(x, y, turn, 2) || IsFive(x, y, turn, 3) || IsFive(x, y, turn, 4);
}
bool RenjuRuleManager::IsOverline(int x, int y,Turn turn)
{
	if (board[y][x].GetBoardValue() != GomokuBoardValue::EMPTY)
		return false;

	SetStone(x, y, Turn2GomokuBoardValue(turn));

	// detect black overline
	int i, j;
	bool bOverline = false;

	// 1 - horizontal direction
	int nLine = 1;
	i = x-1;
	while (i >= 0)
	{
		if (board[y][i--].GetBoardValue() == Turn2GomokuBoardValue(turn))
			nLine++;
		else
			break;
	}
	i = x + 1;
	while (i < BOARD_SIZE)
	{
		if (board[y][i++].GetBoardValue() == Turn2GomokuBoardValue(turn))
			nLine++;
		else
			break;
	}
	if (nLine == 5)
	{
		SetStone(x, y, GomokuBoardValue::EMPTY);
		return false;
	}
	else
		bOverline = (nLine >= 6);

	// 2 - vertical direction
	nLine = 1;
	i = y - 1;
	while (i >= 0)
	{
		if (board[i--][x].GetBoardValue() == Turn2GomokuBoardValue(turn))
			nLine++;
		else
			break;
	}
	i = y + 1;
	while (i < BOARD_SIZE)
	{
		if (board[i++][x].GetBoardValue() == Turn2GomokuBoardValue(turn))
			nLine++;
		else
			break;
	}
	if (nLine == 5)
	{
		SetStone(x, y, Turn2GomokuBoardValue(turn));
		return false;
	}
	else
		bOverline = (nLine >= 6);

	// 3 - diagonal direction (lower-left to upper-right: '/')
	nLine = 1;
	i = x-1;
	j = y-1;
	while ((i >= 0) && (j >= 0))
	{
		if (board[j--][i--].GetBoardValue() == Turn2GomokuBoardValue(turn))
			nLine++;
		else
			break;
	}
	i = x + 1;
	j = y + 1;
	while ((i < BOARD_SIZE) && (j < BOARD_SIZE))
	{
		if (board[j++][i++].GetBoardValue() == Turn2GomokuBoardValue(turn))
			nLine++;
		else
			break;
	}
	if (nLine == 5)
	{
		SetStone(x, y, GomokuBoardValue::EMPTY);
		return false;
	}
	else
		bOverline = (nLine >= 6);

	// 4 - diagonal direction (upper-left to lower-right: '\')
	nLine = 1;
	i = x - 1;
	j = y + 1;
	while ((i >= 0) && (j < BOARD_SIZE))
	{
		if (board[j++][i--].GetBoardValue() == Turn2GomokuBoardValue(turn))
			nLine++;
		else
			break;
	}
	i = x + 1;
	j = y - 1;
	while ((i < BOARD_SIZE) && (j >= 0))
	{
		if (board[j--][i++].GetBoardValue() == Turn2GomokuBoardValue(turn))
			nLine++;
		else
			break;
	}
	if (nLine == 5)
	{
		SetStone(x, y, GomokuBoardValue::EMPTY);
		return false;
	}
	else
		bOverline = (nLine >= 6);

	SetStone(x, y, GomokuBoardValue::EMPTY);
	return bOverline;
}
bool RenjuRuleManager::IsFive(int x, int y, Turn turn, int dir)
{
	if (board[y][x].GetBoardValue() != GomokuBoardValue::EMPTY)
		return false;
	SetStone(x, y, Turn2GomokuBoardValue(turn));
	int i, j;
	int nLine;
	switch (dir)
	{
	case 1:		// horizontal direction
		nLine = 1;
		i = x-1;
		while (i >= 0)
		{
			if (board[y][i--].GetBoardValue() == Turn2GomokuBoardValue(turn))
				nLine++;
			else
				break;
		}
		i = x + 1;
	
		while (i < BOARD_SIZE)
		{
			if (board[y][i++].GetBoardValue() == Turn2GomokuBoardValue(turn))
				nLine++;
			else
				break;
		}
		if (nLine == 5)
		{
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return true;
		}
		else
		{
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return false;
		}
		break;
	case 2:		// vertial direction
		nLine = 1;
		i = y-1;
		while (i >= 0)
		{
			if (board[i--][x].GetBoardValue() == Turn2GomokuBoardValue(turn))
				nLine++;
			else
				break;
		}
		i = y + 1;
		while (i < BOARD_SIZE)
		{
			if (board[i++][x].GetBoardValue() == Turn2GomokuBoardValue(turn))
				nLine++;
			else
				break;
		}
		if (nLine == 5)
		{
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return true;
		}
		else
		{
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return false;
		}
		break;
	case 3:		// diagonal direction - '/'
		nLine = 1;
		i = x-1;
		j = y-1;
		while ((i >= 0) && (j >= 0))
		{
			if (board[j--][i--].GetBoardValue() == Turn2GomokuBoardValue(turn))
				nLine++;
			else
				break;
		}
		i = x + 1;
		j = y + 1;
		while ((i < BOARD_SIZE) && (j < BOARD_SIZE))
		{
			if (board[j++][i++].GetBoardValue() == Turn2GomokuBoardValue(turn))
				nLine++;
			else
				break;
		}
		if (nLine == 5)
		{
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return true;
		}
		else
		{
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return false;
		}
		break;
	case 4:		// diagonal direction - '\'
		nLine = 1;
		i = x-1;
		j = y + 1;
		while ((i >= 0) && (j < BOARD_SIZE))
		{
			if (board[j++][i--].GetBoardValue() == Turn2GomokuBoardValue(turn))
				nLine++;
			else
				break;
		}
		i = x + 1;
		j = y - 1;
		while ((i < BOARD_SIZE) && (j >= 0))
		{
			if (board[j--][i++].GetBoardValue() == Turn2GomokuBoardValue(turn))
				nLine++;
			else
				break;
		}
		if (nLine == 5)
		{
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return true;
		}
		else
		{
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return false;
		}
		break;
	default:
		SetStone(x, y, GomokuBoardValue::EMPTY);
		return false;
		break;
	}

}
bool RenjuRuleManager::IsFour(int x, int y, Turn turn, int dir)
{
	if (board[y][x].GetBoardValue() != GomokuBoardValue::EMPTY)
		return false;
	if (IsFive(x, y, turn))	// five?
		return false;
	else if (turn == Turn::BLACK_TURN && (IsOverline(x, y,turn)))	// black overline?
		return false;
	else
	{
		SetStone(x, y, Turn2GomokuBoardValue(turn));

		int i, j;

		switch (dir)
		{
		case 1:		// horizontal direction
			i = x-1;
			while (i >= 0)
			{
				if (board[y][i].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i--;
					continue;
				}
				else if (board[y][i].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if (IsFive(i , y, turn, dir))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return true;
					}
					else
						break;
				}
				else
					break;
			}
			i = x + 1;
			while (i < BOARD_SIZE)
			{
				if (board[y][i].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i++;
					continue;
				}
				else if (board[y][i].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if (IsFive(i, y, turn, dir))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return true;
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return false;
			break;
		case 2:		// vertial direction
			i = y-1;
			while (i >= 0)
			{
				if (board[i][x].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i--;
					continue;
				}
				else if (board[i][x].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if (IsFive(x, i, turn, dir))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return true;
					}
					else
						break;
				}
				else
					break;
			}
			i = y + 1;
			while (i < BOARD_SIZE)
			{
				if (board[i][x].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i++;
					continue;
				}
				else if (board[i][x].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if (IsFive(x, i, turn, dir))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return true;
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return false;
			break;
		case 3:		// diagonal direction - '/'
			i = x-1;
			j = y-1;
			while ((i >= 0) && (j >= 0))
			{
				if (board[j][i].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i--;
					j--;
					continue;
				}
				else if (board[j][i].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if (IsFive(i, j, turn, dir))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return true;
					}
					else
						break;
				}
				else
					break;
			}
			i = x + 1;
			j = y + 1;
			while ((i < BOARD_SIZE) && (j < BOARD_SIZE))
			{
				if (board[j][i].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i++;
					j++;
					continue;
				}
				else if (board[j][i].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if (IsFive(i , j , turn, dir))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return true;
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return false;
			break;
		case 4:		// diagonal direction - '\'
			i = x-1;
			j = y + 1;
			while ((i >= 0) && (j < BOARD_SIZE))
			{
				if (board[j][i].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i--;
					j++;
					continue;
				}
				else if (board[j][i].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if (IsFive(i , j , turn, dir))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return true;
					}
					else
						break;
				}
				else
					break;
			}
			i = x +1;
			j = y - 1;
			while ((i < BOARD_SIZE) && (j >= 0))
			{
				if (board[j][i].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i++;
					j--;
					continue;
				}
				else if (board[j][i].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if (IsFive(i , j , turn,dir))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return true;
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return false;
			break;
		default:
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return false;
			break;
		}
	}
}
int  RenjuRuleManager::IsOpenFour(int x, int y, Turn turn, int dir)
{
	if (board[y][x].GetBoardValue() != GomokuBoardValue::EMPTY)
		return 0;
	if (IsFive(x, y, turn))	// five?
		return 0;
	else if (turn == Turn::BLACK_TURN && (IsOverline(x, y,turn)))	// black overline?
		return 0;
	else
	{
		SetStone(x, y, Turn2GomokuBoardValue(turn));

		int i, j;
		int nLine;

		switch (dir)
		{
		case 1:		// horizontal direction
			nLine = 1;
			i = x-1;
			while (i >= 0)
			{
				if (board[y][i].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i--;
					nLine++;
					continue;
				}
				else if (board[y][i].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if (!IsFive(i, y, turn, dir))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return 0;
					}
					else
						break;
				}
				else
				{
					SetStone(x, y, GomokuBoardValue::EMPTY);
					return 0;
				}
			}
			i = x + 1;
			while (i < BOARD_SIZE)
			{
				if (board[y][i].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i++;
					nLine++;
					continue;
				}
				else if (board[y][i].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if (IsFive(i , y, turn, dir))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return (nLine == 4 ? 1 : 2);//nLine이 4보다 작은경우-> 44인경우, 
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return 0;
			break;
		case 2:		// vertial direction
			nLine = 1;
			i = y-1;
			while (i >= 0)
			{
				if (board[i][x].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i--;
					nLine++;
					continue;
				}
				else if (board[i][x].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if (!IsFive(x, i, turn, dir))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return 0;
					}
					else
						break;
				}
				else
				{
					SetStone(x, y, GomokuBoardValue::EMPTY);
					return 0;
				}
			}
			i = y + 1;
			while (i < BOARD_SIZE)
			{
				if (board[i][x].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i++;
					nLine++;
					continue;
				}
				else if (board[i][x].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if (IsFive(x, i , turn, dir))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return (nLine == 4 ? 1 : 2);
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return 0;
			break;
		case 3:		// diagonal direction - '/'
			nLine = 1;
			i = x-1;
			j = y-1;
			while ((i >= 0) && (j >= 0))
			{
				if (board[j][i].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i--;
					j--;
					nLine++;
					continue;
				}
				else if (board[j][i].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if (!IsFive(i , j , turn, dir))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return 0;
					}
					else
						break;
				}
				else
				{
					SetStone(x, y,GomokuBoardValue::EMPTY);
					return 0;
				}
			}
			i = x + 1;
			j = y + 1;
			while ((i < BOARD_SIZE) && (j < BOARD_SIZE))
			{
				if (board[j][i].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i++;
					j++;
					nLine++;
					continue;
				}
				else if (board[j][i].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if (IsFive(i , j , turn, dir))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return (nLine == 4 ? 1 : 2);
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return 0;
			break;
		case 4:		// diagonal direction - '\'
			nLine = 1;
			i = x-1;
			j = y + 1;
			while ((i >= 0) && (j < BOARD_SIZE))
			{
				if (board[j][i].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i--;
					j++;
					nLine++;
					continue;
				}
				else if (board[j][i].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if (!IsFive(i , j , turn, dir))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return 0;
					}
					else
						break;
				}
				else
				{
					SetStone(x, y, GomokuBoardValue::EMPTY);
					return 0;
				}
			}
			i = x +1;
			j = y - 1;
			while ((i < BOARD_SIZE) && (j >= 0))
			{
				if (board[j][i].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i++;
					j--;
					nLine++;
					continue;
				}
				else if (board[j][i].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if (IsFive(i , j , turn, dir))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return (nLine == 4 ? 1 : 2);
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return 0;
			break;
		default:
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return 0;
			break;
		}
	}
}
bool RenjuRuleManager::IsOpenThree(int x, int y, Turn turn, int dir)
{
	if (board[y][x].GetBoardValue() != GomokuBoardValue::EMPTY)
		return false;
	if (IsFive(x, y,turn))	// five?
		return false;
	else if ((turn == Turn::BLACK_TURN) && (IsOverline(x, y,turn)))	// black overline?
		return false;
	else
	{
		SetStone(x, y, Turn2GomokuBoardValue(turn));
		int i, j;

		switch (dir)
		{
		case 1:		// horizontal direction
			i = x-1;
			while (i >= 0)
			{
				if (board[y][i].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i--;
					continue;
				}
				else if (board[y][i].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if ((IsOpenFour(i, y, turn, dir) == 1) && (!IsDoubleFour(i, y,turn)) && (!IsDoubleThree(i , y,turn)))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return true;
					}
					else
						break;
				}
				else
					break;
			}
			i = x + 1;
			while (i < BOARD_SIZE)
			{
				if (board[y][i].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i++;
					continue;
				}
				else if (board[y][i].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if ((IsOpenFour(i, y, turn, dir) == 1) && (!IsDoubleFour(i, y,turn)) && (!IsDoubleThree(i, y, turn)))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return true;
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return false;
			break;
		case 2:		// vertial direction
			i = y-1;
			while (i >= 0)
			{
				if (board[i][x].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i--;
					continue;
				}
				else if (board[i][x].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if ((IsOpenFour(x, i, turn, dir) == 1) && (!IsDoubleFour(x, i, turn)) && (!IsDoubleThree(x, i, turn)))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return true;
					}
					else
						break;
				}
				else
					break;
			}
			i = y + 1;
			while (i < BOARD_SIZE)
			{
				if (board[i][x].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i++;
					continue;
				}
				else if (board[i][x].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if ((IsOpenFour(x, i, turn, dir) == 1) && (!IsDoubleFour(x, i, turn)) && (!IsDoubleThree(x, i, turn)))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return true;
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return false;
			break;
		case 3:		// diagonal direction - '/'
			i = x-1;
			j = y-1;
			while ((i >= 0) && (j >= 0))
			{
				if (board[j][i].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i--;
					j--;
					continue;
				}
				else if (board[j][i].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if ((IsOpenFour(i , j , turn, dir) == 1) && (!IsDoubleFour(i , j, turn)) && (!IsDoubleThree(i , j, turn)))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return true;
					}
					else
						break;
				}
				else
					break;
			}
			i = x + 1;
			j = y + 1;
			while ((i < BOARD_SIZE) && (j < BOARD_SIZE))
			{
				if (board[j][i].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i++;
					j++;
					continue;
				}
				else if (board[j][i].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if ((IsOpenFour(i , j , turn, dir) == 1) && (!IsDoubleFour(i , j, turn)) && (!IsDoubleThree(i , j, turn)))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return true;
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return false;
			break;
		case 4:		// diagonal direction - '\'
			i = x-1;
			j = y + 1;
			while ((i >= 0) && (j < BOARD_SIZE))
			{
				if (board[j][i].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i--;
					j++;
					continue;
				}
				else if (board[j][i].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if ((IsOpenFour(i , j , turn, dir) == 1) && (!IsDoubleFour(i , j, turn)) && (!IsDoubleThree(i , j, turn)))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return true;
					}
					else
						break;
				}
				else
					break;
			}
			i = x + 1;
			j = y - 1;
			while ((i < BOARD_SIZE) && (j >= 0))
			{
				if (board[j][i].GetBoardValue() == Turn2GomokuBoardValue(turn))
				{
					i++;
					j--;
					continue;
				}
				else if (board[j][i].GetBoardValue() == GomokuBoardValue::EMPTY)
				{
					if ((IsOpenFour(i , j , turn, dir) == 1) && (!IsDoubleFour(i , j, turn)) && (!IsDoubleThree(i , j, turn)))
					{
						SetStone(x, y, GomokuBoardValue::EMPTY);
						return true;
					}
					else
						break;
				}
				else
					break;
			}
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return false;
			break;
		default:
			SetStone(x, y, GomokuBoardValue::EMPTY);
			return false;
			break;
		}
	}
	
}
bool RenjuRuleManager::IsDoubleFour(int x, int y,Turn turn)
{
	if (board[y][x].GetBoardValue() != GomokuBoardValue::EMPTY)
		return false;
	if (IsFive(x, y, turn))	// five?
		return false;

	int nFour = 0;
	for (int i = 1; i <= 4; i++)
	{
		if (IsOpenFour(x, y, turn, i) == 2)
			nFour += 2;
		else if (IsFour(x, y, turn, i))
			nFour++;
	}

	if (nFour >= 2)
		return true;
	else
		return false;
}
bool RenjuRuleManager::IsDoubleThree(int x, int y,Turn turn)
{
	if (board[y][x].GetBoardValue() != GomokuBoardValue::EMPTY)
		return false;
	if (IsFive(x, y, turn))	// five?
		return false;
	
	int nThree = 0;
	
	for (int i = 1; i <= 4; i++)
	{
		if (IsOpenThree(x, y, turn, i))
		{
			nThree++;
		}
	}
	
	if (nThree >= 2)
		return true;
	else
		return false;
}
GomokuBoardValue RenjuRuleManager::Turn2GomokuBoardValue(Turn turn)
{
	return turn == Turn::BLACK_TURN ? GomokuBoardValue::BLACK : GomokuBoardValue::WHITE;
}