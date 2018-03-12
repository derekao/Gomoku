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
	

//std::cout << "test = " <<  Board->getPotentialMove().size() << std::endl;
	for (size_t i = 0; i < Board->getPotentialMove().size(); i++)
	{
		if (Board->getPotentialMove()[i].priority <= Board->getHighestPriority()) {
			tmp = new GameManager(*Board);
			PlayStone(Board->getPotentialMove()[i].y, Board->getPotentialMove()[i].x, tmp);
 			Coord PlayedMove = Coord(Board->getPotentialMove()[i].y, Board->getPotentialMove()[i].x);
			tmp->setLastMove(PlayedMove);
			tabMove.push_back(tmp);
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
		Board->getBlackStones().push_back(Coord(y, x));
	}
	else
	{
		PlayerOne = STONE_WHITE;
		PlayerTwo = STONE_BLACK;
		Board->setbPlayerOneTurn(true);
		Board->getWhiteStones().push_back(Coord(y, x));
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
//	std::cout << " 4)" << Board->getBlackStones().size() << " et " << Board->getWhiteStones().size() << std::endl;
	Heuristic bestMoves = Heuristic(PlayerTwo, PlayerOne, Board);
	bestMoves.searchMoves();
//	std::cout << "testR = " <<  Board->getPotentialMove().size() << std::endl;
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
	// Eat Left
	if (x >= 3 && Board->getBoard()[y * BOARD_WIDTH + x - 1] == Player2 && Board->getBoard()[y * BOARD_WIDTH + x - 2] == Player2 && Board->getBoard()[y * BOARD_WIDTH + x - 3] == Player1)
		SomethingEaten = DeadStone(y, x -1, y, x - 2, &iScore, Player1, Board);
	// Eat Right
	if (x <= BOARD_WIDTH - 3 && Board->getBoard()[y * BOARD_WIDTH + x + 1] == Player2 && Board->getBoard()[y * BOARD_WIDTH + x + 2] == Player2 && Board->getBoard()[y * BOARD_WIDTH + x + 3] == Player1)
		SomethingEaten = DeadStone(y, x + 1, y, x + 2, &iScore, Player1, Board);
	// Eat Top
	if (y >= 3 && Board->getBoard()[(y - 1) * BOARD_WIDTH + x] == Player2 && Board->getBoard()[(y - 2) * BOARD_WIDTH + x] == Player2 && Board->getBoard()[(y - 3) * BOARD_WIDTH + x] == Player1)
		SomethingEaten = DeadStone(y - 1, x, y - 2, x, &iScore, Player1, Board);
	// Eat Bottom
	if (y < BOARD_HEIGHT- 3 && Board->getBoard()[(y + 1) * BOARD_WIDTH + x] == Player2 && Board->getBoard()[(y + 2) * BOARD_WIDTH + x] == Player2 && Board->getBoard()[(y + 3) * BOARD_WIDTH + x] == Player1)
		SomethingEaten = DeadStone(y + 1, x, y + 2, x, &iScore, Player1, Board);
	// Eat Top Left
	if (x >= 3 && y >= 3 && Board->getBoard()[(y - 1) * BOARD_WIDTH + x - 1] == Player2 && Board->getBoard()[(y - 2) * BOARD_WIDTH + x - 2] == Player2 && Board->getBoard()[(y - 3) * BOARD_WIDTH + x - 3] == Player1)
		SomethingEaten = DeadStone(y - 1, x - 1, y - 2, x - 2, &iScore, Player1, Board);
	// Eat Top Right
	if (x < BOARD_WIDTH - 3 && y >= 3 && Board->getBoard()[(y - 1) * BOARD_WIDTH + x + 1] == Player2 && Board->getBoard()[(y - 2) * BOARD_WIDTH + x + 2] == Player2 && Board->getBoard()[(y - 3) * BOARD_WIDTH + x + 3] == Player1)
		SomethingEaten = DeadStone(y - 1, x + 1, y - 2, x + 2, &iScore, Player1, Board);
	// Eat Bottom Right
	if (x < BOARD_WIDTH - 3 && y < BOARD_HEIGHT- 3 && Board->getBoard()[(y + 1) * BOARD_WIDTH + x + 1] == Player2 && Board->getBoard()[(y + 2) * BOARD_WIDTH + x + 2] == Player2 && Board->getBoard()[(y + 3) * BOARD_WIDTH + x + 3] == Player1)
		SomethingEaten = DeadStone(y + 1, x + 1, y + 2, x + 2, &iScore, Player1, Board);
	// Eat Bottom Left
	if (x >= 3 && y < BOARD_HEIGHT - 3 && Board->getBoard()[(y + 1) * BOARD_WIDTH + x - 1] == Player2 && Board->getBoard()[(y + 2) * BOARD_WIDTH + x - 2] == Player2 && Board->getBoard()[(y + 3) * BOARD_WIDTH + x - 3] == Player1)
		SomethingEaten = DeadStone(y + 1, x - 1, y + 2, x - 2, &iScore, Player1, Board);
	if (Board->getbPlayerOneTurn())
		Board->setBlackScore(Board->getBlackScore() + iScore);
	else
		Board->setWhiteScore(Board->getWhiteScore() + iScore);
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
//				checkForbiddenBox(i, j);
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

bool PossibleMove::DeadStone(int y1, int x1, int y2, int x2, int * iScore, int Player, GameManager * Board)
{
	if (Player == STONE_BLACK)
	{
		int stop = 0;
		for (size_t i = 0; i < Board->getBlackStones().size(); i++)
		{
			if (stop == 2)
				break;
			if ((Board->getBlackStones()[i].x == x1 && Board->getBlackStones()[i].y == y1)
				|| (Board->getBlackStones()[i].x == x2 && Board->getBlackStones()[i].y == y2))
			{
				Board->getBlackStones().erase(Board->getBlackStones().begin() + i);
				stop++;
			}
		}
	}
	Board->getBoard()[y1 * BOARD_WIDTH + x1] = STONE_EMPTY;
	Board->getBoard()[y2 * BOARD_WIDTH + x2] = STONE_EMPTY;
	*iScore += 2;
	return true;
}