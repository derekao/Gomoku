// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PossibleMove.class.cpp                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/03/01 16:34:59 by semartin          #+#    #+#             //
//   Updated: 2018/03/01 16:34:59 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "PossibleMove.class.hpp"

// static void printBoard(GameManager * Board)
// {
// 	for (int i = 0; i < 361; i ++)
// 	{
// 		std::cout << Board->getBoard()[i] << " ";
// 		if (i % 19 == 18)
// 			std::cout << std::endl;
// 	}
// }

PossibleMove::PossibleMove(GameManager * src) : Board(src),
	HighestHeuristicValue(src->getHeuristicValue()), LowestHeuristicValue(src->getHeuristicValue())
{
	Compute();
}

void PossibleMove::Compute()
{
	GameManager * tmp;
	for (int i =  0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH ; j++)
		{
			if (Board->getBoard()[i * BOARD_WIDTH + j] == STONE_PLAYAREA)
			{
				tmp = new GameManager(*Board);
				PlayStone(i, j, tmp);
				Coord PlayedMove = Coord(i, j);
				tmp->setLastMove(PlayedMove);
				tabMove.push_back(tmp);
			}
		}
	}
}

// Return True if there is a stone 2 cells around the stone in parameter
bool PossibleMove::StoneNearby(int y, int x)
{
	for (int i = y - 1; i <= y + 1; i++)
	{
		if (i < 0)
			continue;
		if (i >= BOARD_HEIGHT)
			break;
		for (int j = x - 1; j <= x + 1; j++)
		{
			if (j < 0)
				continue;
			if (j >= BOARD_WIDTH)
				break;
			if (!Rules::EmptyCase(Board->getBoard()[i * BOARD_WIDTH + j]))
			{
				return true;
			}
		}
	}
	return false;
}

// Static function that play a stone.
void PossibleMove::PlayStone(int y, int x, GameManager * Board)
{
	int PlayerOne;
	int PlayerTwo;

	bool SomethingEaten = CheckStoneEaten(y, x, Board);
	if (Board->getbPlayerOneTurn())
	{
		PlayerOne = STONE_BLACK;
		PlayerTwo = STONE_WHITE;
		Board->setbPlayerOneTurn(false);
	}
	else
	{
		PlayerOne = STONE_WHITE;
		PlayerTwo = STONE_BLACK;
		Board->setbPlayerOneTurn(true);
	}

	Board->getBoard()[y * BOARD_WIDTH + x] = PlayerOne;
	int win;
	if (Board->getHasWon())
	{
		win = Rules::CheckWin(PlayerTwo, Board->getWinPos().y, Board->getWinPos().x, Board);
		if (win != 0)
		{
			Rules::youWin(PlayerTwo, PlayerOne, Board->getWinPos().y, Board->getWinPos().x, Board);
			return ;
		}
		else
			Board->setHasWon(false);
	}
	win = Rules::CheckWin(PlayerOne, y, x, Board);
	if (win != 0)
	{
		Rules::youWin(PlayerOne, PlayerTwo, y, x, Board);
	}
	CheckBoardState(y, x, SomethingEaten, Board);
	MakePlayArea(y, x, Board);
}

// static function
bool PossibleMove::CheckStoneEaten(int y, int x, GameManager * Board) 
{
	int Player1;
	int Player2;
	int iScore = 0;
	bool SomethingEaten = false;

	if (Board->getbPlayerOneTurn())
	{
		Player1 = STONE_BLACK;
		Player2 = STONE_WHITE;
	}
	else
	{
		Player1 = STONE_WHITE;
		Player2 = STONE_BLACK;
	}
	if (x >= 3) // Eat Left
		if (Board->getBoard()[y * BOARD_WIDTH + x - 1] == Player2 && Board->getBoard()[y * BOARD_WIDTH + x - 2] == Player2 && Board->getBoard()[y * BOARD_WIDTH + x - 3] == Player1)
		{
			Board->getBoard()[y * BOARD_WIDTH + x - 1] = STONE_EMPTY;
			Board->getBoard()[y * BOARD_WIDTH + x - 2] = STONE_EMPTY;
			iScore += 2;
			SomethingEaten = true;
		}
	if (x <= BOARD_WIDTH - 3) // Eat Right
		if (Board->getBoard()[y * BOARD_WIDTH + x + 1] == Player2 && Board->getBoard()[y * BOARD_WIDTH + x + 2] == Player2 && Board->getBoard()[y * BOARD_WIDTH + x + 3] == Player1)
		{
			Board->getBoard()[y * BOARD_WIDTH + x + 1] = STONE_EMPTY;
			Board->getBoard()[y * BOARD_WIDTH + x + 2] = STONE_EMPTY;
			iScore += 2;
			SomethingEaten = true;
		}
	if (y >= 3) // Eat Top
		if (Board->getBoard()[(y - 1) * BOARD_WIDTH + x] == Player2 && Board->getBoard()[(y - 2) * BOARD_WIDTH + x] == Player2 && Board->getBoard()[(y - 3) * BOARD_WIDTH + x] == Player1)
		{
			Board->getBoard()[(y - 1) * BOARD_WIDTH + x] = STONE_EMPTY;
			Board->getBoard()[(y - 2) * BOARD_WIDTH + x] = STONE_EMPTY;
			iScore += 2;
			SomethingEaten = true;
		}
	if (y < BOARD_HEIGHT- 3) // Eat Bottom
		if (Board->getBoard()[(y + 1) * BOARD_WIDTH + x] == Player2 && Board->getBoard()[(y + 2) * BOARD_WIDTH + x] == Player2 && Board->getBoard()[(y + 3) * BOARD_WIDTH + x] == Player1)
		{
			Board->getBoard()[(y + 1) * BOARD_WIDTH + x] = STONE_EMPTY;
			Board->getBoard()[(y + 2) * BOARD_WIDTH + x] = STONE_EMPTY;
			iScore += 2;
			SomethingEaten = true;
		}
	if (x >= 3 && y >= 3) // Eat Top Left
		if (Board->getBoard()[(y - 1) * BOARD_WIDTH + x - 1] == Player2 && Board->getBoard()[(y - 2) * BOARD_WIDTH + x - 2] == Player2 && Board->getBoard()[(y - 3) * BOARD_WIDTH + x - 3] == Player1)
		{
			Board->getBoard()[(y - 1) * BOARD_WIDTH + x - 1] = STONE_EMPTY;
			Board->getBoard()[(y - 2) * BOARD_WIDTH + x - 2] = STONE_EMPTY;
			iScore += 2;
			SomethingEaten = true;
		}
	if (x < BOARD_WIDTH - 3 && y >= 3) // Eat Top Right
		if (Board->getBoard()[(y - 1) * BOARD_WIDTH + x + 1] == Player2 && Board->getBoard()[(y - 2) * BOARD_WIDTH + x + 2] == Player2 && Board->getBoard()[(y - 3) * BOARD_WIDTH + x + 3] == Player1)
		{
			Board->getBoard()[(y - 1) * BOARD_WIDTH + x + 1] = STONE_EMPTY;
			Board->getBoard()[(y - 2) * BOARD_WIDTH + x + 2] = STONE_EMPTY;
			iScore += 2;
			SomethingEaten = true;
		}
	if (x < BOARD_WIDTH - 3 && y < BOARD_HEIGHT- 3) // Eat Bottom Right
		if (Board->getBoard()[(y + 1) * BOARD_WIDTH + x + 1] == Player2 && Board->getBoard()[(y + 2) * BOARD_WIDTH + x + 2] == Player2 && Board->getBoard()[(y + 3) * BOARD_WIDTH + x + 3] == Player1)
		{
			Board->getBoard()[(y + 1) * BOARD_WIDTH + x + 1] = STONE_EMPTY;
			Board->getBoard()[(y + 2) * BOARD_WIDTH + x + 2] = STONE_EMPTY;
			iScore += 2;
			SomethingEaten = true;
		}
	if (x >= 3 && y < BOARD_HEIGHT- 3) // Eat Bottom Left
		if (Board->getBoard()[(y + 1) * BOARD_WIDTH + x - 1] == Player2 && Board->getBoard()[(y + 2) * BOARD_WIDTH + x - 2] == Player2 && Board->getBoard()[(y + 3) * BOARD_WIDTH + x - 3] == Player1)
		{
			Board->getBoard()[(y + 1) * BOARD_WIDTH + x - 1] = STONE_EMPTY;
			Board->getBoard()[(y + 2) * BOARD_WIDTH + x - 2] = STONE_EMPTY;
			iScore += 2;
			SomethingEaten = true;
		}
	if (Board->getbPlayerOneTurn())
	{
		Board->setBlackScore(Board->getBlackScore() + iScore);
	}
	else
	{
		Board->setWhiteScore(Board->getWhiteScore() + iScore);
	}
	return SomethingEaten;
}

void PossibleMove::CheckBoardState(int Height, int Width, bool SomethingEaten, GameManager * Board) 
{
		int Player1;
		int Player2;
		bool dTree = false;
		Height = (Height <= 5) ? 0 : Height - 5;
		Width = (Width <= 5) ? 0 : Width - 5; 
		int MaxHeight = (Height + 10 >= BOARD_HEIGHT - 1) ? BOARD_HEIGHT - 1 : Height + 10;
		int MaxWidth = (Width + 10 >= BOARD_WIDTH - 1) ? BOARD_WIDTH - 1 : Width + 10;

		if (Board->getbPlayerOneTurn()) {
			Player1 = STONE_BLACK;
			Player2 = STONE_WHITE;
		}
		else {
			Player1 = STONE_WHITE;
			Player2 = STONE_BLACK;
		}

		for (int i = Height; i <= MaxHeight; i++) {
			for (int j = Width; j <= MaxWidth; j++) {

				if (Rules::EmptyCase(Board->getBoard()[i * BOARD_WIDTH + j])) {
//					checkForbiddenBox(i, j);
					int win = Rules::CheckWin(Player2, i, j, Board);
					if (SomethingEaten)
					{
						dTree = Rules::CheckDoubleTreeBox(i, j, Player1, Board);
						if ((dTree && Rules::somethingToEatWithEmpty(Player2, Player1, i, j, Board)) && win == 0 ) 
						{
							dTree = false;
							if ((Player1 & STONE_BLACK) != 0)
								Board->getBoard()[i * BOARD_WIDTH + j] -= STONE_BLACKDOUBLETREE;
							else
								Board->getBoard()[i * BOARD_WIDTH + j] -= STONE_WHITEDOUBLETREE;

						}
					}
					dTree = Rules::CheckDoubleTreeBox(i, j, Player2, Board);
					if ((dTree && Rules::somethingToEatWithEmpty(Player1, Player2, i, j, Board)) && win == 0 ) 
					{
						dTree = false;
						if ((Player1 & STONE_BLACK) != 0)
							Board->getBoard()[i * BOARD_WIDTH + j] -= STONE_BLACKDOUBLETREE;
						else
							Board->getBoard()[i * BOARD_WIDTH + j] -= STONE_WHITEDOUBLETREE;
						
					}
					else if (win != 0)
					{
						Board->getBoard()[i * BOARD_WIDTH + j] = STONE_EMPTY;
					}
				}
			}
		}	
	}

void PossibleMove::MakePlayArea(int y, int x, GameManager * Board)
{
	for (int i = y - PLAY_AREA_SIZE; i <= y + PLAY_AREA_SIZE; i++)
	{
		if (i < 0 || i >= BOARD_HEIGHT)
			continue;
		for (int j = x - PLAY_AREA_SIZE; j <= x + PLAY_AREA_SIZE; j++)
		{
			if (j < 0 || j >= BOARD_WIDTH)
				continue;
			if (Board->getBoard()[i * BOARD_WIDTH + j] == STONE_EMPTY)
			{
				Board->getBoard()[i * BOARD_WIDTH + j] = STONE_PLAYAREA;
			}
		}
	}
}