#pragma once
#include <iostream>
#include <fstream>
#include <limits.h>  // for the INT_MAX

struct Wall
{
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
};

struct Board
{
	int theBoard[6][6] = { 0 };
	int ballCount = 0;
	Wall theWalls[6][6] = {}; 
};

class Marbles
{
protected:
	Board boardStack[100];
	Wall walls[100];
	int size = 0, wallCount = 0;
	int bestSoln = INT_MAX;

public:
	Marbles(const char* fileName)
	{
		std::fstream file(fileName);
		file >> size >> boardStack[0].ballCount >> wallCount;

		for (int i = 0; i < boardStack[0].ballCount; i++)
		{
			int row, col;

			file >> row >> col;

			boardStack[0].theBoard[row][col] = i + 1;
		}
		for (int i = 0; i < boardStack[0].ballCount; i++)
		{
			int row, col;

			file >> row >> col;

			boardStack[0].theBoard[row][col] = 0 - i - 1;
		}
		for (int i = 0; i < wallCount; i++)
		{
			int r1, c1, r2, c2;

			file >> r1 >> c1 >> r2 >> c2;

			if (r1 == r2)
			{
				if (c1 < c2)
				{
					boardStack[0].theWalls[r1][c1].right = true;
					boardStack[0].theWalls[r2][c2].left = true;
				}
				else
				{
					boardStack[0].theWalls[r1][c1].left = true;
					boardStack[0].theWalls[r2][c2].right = true;
				}
			}
			else
			{
				if (r1 < r2)
				{
					boardStack[0].theWalls[r1][c1].down = true;
					boardStack[0].theWalls[r2][c2].up = true;
				}
				else
				{
					boardStack[0].theWalls[r1][c1].up = true;
					boardStack[0].theWalls[r2][c2].down = true;
				}
			}
		}
		file.close();
	}

	// issue once this is called the entire board state is resetting back to zero
	bool rollLeft(int level)
	{
		for (int row = 0; row < size; row++)
		{
			for (int col = 1; col < size; col++)
			{
				if (boardStack[level].theBoard[row][col] > 0) // check if theres a ball
				{
					int tempCol = col;

					while (true)
					{
						// this checks if the ball is blocked by a wall (to the left) or the ball is already on the left edge of the board
						if ((boardStack[level].theWalls[row][tempCol].left == true) || (tempCol == 0))
						{
							break;
						}
						// this checks if there is a hole to the left of the ball (the cases check if it was the correct hole or not)
						else if (boardStack[level].theBoard[row][tempCol - 1] < 0)
						{
							if ((boardStack[level].theBoard[row][tempCol - 1] + boardStack[level].theBoard[row][tempCol]) != 0) // if this was true then ball 1 and hole -2 would != 0 a counter example ball 1 and hole -1 would be 0 thu false
							{
								return false;
							}
							else
							{
								boardStack[level].theBoard[row][tempCol - 1] = 0;
								boardStack[level].theBoard[row][tempCol] = 0;
								break;
							}
						}
						// the final check here is to see if the is a ball preceeding the ball (so to the left)
						else if (boardStack[level].theBoard[row][tempCol - 1] > 0)
						{
							break;
						}
						// will move the ball to the left
						else
						{
							boardStack[level].theBoard[row][tempCol - 1] = boardStack[level].theBoard[row][tempCol];
							boardStack[level].theBoard[row][tempCol] = 0;

							tempCol--;
						}
					}
				}
			}
		}
		return true;
	}

	bool rollRight(int level)
	{
		for (int row = 0; row < size; row++)
		{
			for (int col = size - 2; col >= 0; col--)
			{
				if (boardStack[level].theBoard[row][col] > 0) // check if theres a ball
				{
					int tempCol = col;

					while (true)
					{
						// this checks if the ball is blocked by a wall (to the right) or the ball is already on the right edge of the board
						if ((boardStack[level].theWalls[row][tempCol].right == true) || (tempCol == size - 1))
						{
							break;
						}
						// this checks if there is a hole to the right of the ball (the cases check if it was the correct hole or not)
						else if (boardStack[level].theBoard[row][tempCol + 1] < 0)
						{
							if ((boardStack[level].theBoard[row][tempCol + 1] + boardStack[level].theBoard[row][tempCol]) != 0) // if this was true then ball 1 and hole -2 would != 0 a counter example ball 1 and hole -1 would be 0 thu false
							{
								return false;
							}
							else
							{
								boardStack[level].theBoard[row][tempCol + 1] = 0;
								boardStack[level].theBoard[row][tempCol] = 0;
								break;
							}
						}
						// the final check here is to see if the is a ball preceeding the ball (so to the left)
						else if (boardStack[level].theBoard[row][tempCol + 1] > 0)
						{
							break;
						}
						// will move the ball to the left
						else
						{
							boardStack[level].theBoard[row][tempCol + 1] = boardStack[level].theBoard[row][tempCol];
							boardStack[level].theBoard[row][tempCol] = 0;

							tempCol++;
						}
					}
				}
			}
		}
		return true;
	}

	bool rollUp(int level)
	{
		for (int col = 0; col < size; col++)
		{
			for (int row = 1; row < size; row++)
			{
				if (boardStack[level].theBoard[row][col] > 0) // check if theres a ball
				{
					int tempRow = row;

					while (true)
					{
						// this checks if the ball is blocked by a wall (above) or the ball is already on the top edge of the board
						if ((boardStack[level].theWalls[tempRow][col].up == true) || (tempRow == 0))
						{
							break;
						}
						// this checks if there is a hole above the ball (the cases check if it was the correct hole or not)
						else if (boardStack[level].theBoard[tempRow - 1][col] < 0)
						{
							if ((boardStack[level].theBoard[tempRow - 1][col] + boardStack[level].theBoard[tempRow][col]) != 0) // if this was true then ball 1 and hole -2 would != 0 a counter example ball 1 and hole -1 would be 0 thu false
							{
								return false;
							}
							else
							{
								boardStack[level].theBoard[tempRow - 1][col] = 0;
								boardStack[level].theBoard[tempRow][col] = 0;
								break;
							}
						}
						// the final check here is to see if the is a ball preceeding the ball (so to the left)
						else if (boardStack[level].theBoard[tempRow - 1][col] > 0)
						{
							break;
						}
						// will move the ball to the left
						else
						{
							boardStack[level].theBoard[tempRow - 1][col] = boardStack[level].theBoard[tempRow][col];
							boardStack[level].theBoard[tempRow][col] = 0;

							tempRow--;
						}
					}
				}
			}
		}

		return true;
	}

	bool rollDown(int level)
	{
		for (int col = 0; col < size; col++)
		{
			for (int row = size -2; row >= 0; row--)
			{
				if (boardStack[level].theBoard[row][col] > 0) // check if theres a ball
				{
					int tempRow = row;

					while (true)
					{
						// this checks if the ball is blocked by a wall (above) or the ball is already on the top edge of the board
						if ((boardStack[level].theWalls[tempRow][col].down == true) || (tempRow == size - 1))
						{
							break;
						}
						// this checks if there is a hole above the ball (the cases check if it was the correct hole or not)
						else if (boardStack[level].theBoard[tempRow + 1][col] < 0)
						{
							if ((boardStack[level].theBoard[tempRow + 1][col] + boardStack[level].theBoard[tempRow][col]) != 0) // if this was true then ball 1 and hole -2 would != 0 a counter example ball 1 and hole -1 would be 0 thu false
							{
								return false;
							}
							else
							{
								boardStack[level].theBoard[tempRow + 1][col] = 0;
								boardStack[level].theBoard[tempRow][col] = 0;
								break;
							}
						}
						// the final check here is to see if the is a ball preceeding the ball (so to the left)
						else if (boardStack[level].theBoard[tempRow + 1][col] > 0)
						{
							break;
						}
						// will move the ball to the left
						else
						{
							boardStack[level].theBoard[tempRow + 1][col] = boardStack[level].theBoard[tempRow][col];
							boardStack[level].theBoard[tempRow][col] = 0;

							tempRow++;
						}
					}
				}
			}
		}
		return true;
	}

	int GetBestMoves()
	{
		if (bestSoln == INT_MAX)
		{
			throw 99;
		}
		return bestSoln;
	}

	// I am having issues making the original to work so I am going to try to go back to the longer version 
	bool seen(int level)
	{
		for (int curLevel = level - 2; curLevel >= 0; curLevel--)
		{
			bool identicalBoards = true;
			for (int row = 0; row < size; row++)
			{
				for (int col = 0; col < size; col ++)
				{
					if (boardStack[level - 1].theBoard[row][col] != boardStack[curLevel].theBoard[row][col])
					{
						identicalBoards = false;
						break;
					}
				}
				if (!identicalBoards)
				{
					break;
				}
			}
			if (identicalBoards)
			{
				return true;;
			}
			//if (boardStack[level - 1].ballCount < boardStack[curLevel].ballCount)
			//{
			//	return true;
			//}
			//else if (boardStack[level - 1].theBoard == boardStack[curLevel].theBoard)
			//{
			//	return false;
			//}
		}
		return false;
	}
	
	bool isEmpty(int level)
	{
		for (int row = 0; row < size; row++)
		{
			for (int col = 0; col < size; col++)
			{
				if (boardStack[level-1].theBoard[row][col] != 0)
				{
					return false;
				}
			}
		}

		return true;
	}

	void solve(int level = 1)
	{
		if (level == 100) {
			return;
		}
		if (level >= bestSoln)
		{
			return;
		}
		else if (seen(level))
		{
			return;
		}
		else if (isEmpty(level))
		{
			if (bestSoln == 0)
			{
				bestSoln = level;
			}
			else
			{
				bestSoln = level - 1;
			}

			return;
		}

		//boardStack[level] = boardStack[level + 1]; 
		//making a copy of the board state 
		for (int row = 0; row < size; row++)
		{
			for (int col = 0; col < size; col++)
			{
				boardStack[level].theBoard[row][col] = boardStack[level - 1].theBoard[row][col];
				boardStack[level].theWalls[row][col] = boardStack[level - 1].theWalls[row][col];
			}
		}
		if (rollLeft(level))
		{
			solve(level + 1);
		}

		for (int row = 0; row < size; row++)
		{
			for (int col = 0; col < size; col++)
			{
				boardStack[level].theBoard[row][col] = boardStack[level - 1].theBoard[row][col];
				boardStack[level].theWalls[row][col] = boardStack[level - 1].theWalls[row][col];
			}
		}
		if (rollDown(level))
		{
			solve(level + 1);
		}

		for (int row = 0; row < size; row++)
		{
			for (int col = 0; col < size; col++)
			{
				boardStack[level].theBoard[row][col] = boardStack[level - 1].theBoard[row][col];
				boardStack[level].theWalls[row][col] = boardStack[level - 1].theWalls[row][col];
			}
		}
		if (rollUp(level))
		{
			solve(level + 1);
		}


		for (int row = 0; row < size; row++)
		{
			for (int col = 0; col < size; col++)
			{
				boardStack[level].theBoard[row][col] = boardStack[level - 1].theBoard[row][col];
				boardStack[level].theWalls[row][col] = boardStack[level - 1].theWalls[row][col];
			}
		}
		if (rollRight(level))
		{
			solve(level + 1);
		}

		try
		{
			if (level > 100)
			{
				throw level;
			}
		}
		catch (int level)
		{
			std::cout << "ERROR! Board Stack has exceeded 100" << std::endl;
		}
	}
};