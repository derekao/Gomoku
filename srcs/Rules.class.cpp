// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Rules.class.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/02/28 11:47:24 by semartin          #+#    #+#             //
//   Updated: 2018/02/28 11:47:24 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Rules.class.hpp"

// Return True if the Cell dont have any Black or White Stone
static bool Rules::EmptyCase(int Content)
{
	if ((Content & STONE_BLACK) == 0 && (Content & STONE_WHITE) == 0)
			return true;
		else
			return false;
}

// If there is 5 Stones aligned check if you can break the alignement or win eating stone
static void Rules::youWin(int Player, int Opponent, int y, int x, GameManager * Instance)
{
	bool Break = breakWin(Player, Opponent, y, x);

	somethingToEatOnTheBoard(Opponent, Player);
	if ((Player & STONE_WHITE) == 0 && Instance->getHasWon() && Instance->getWhiteScore() < 10)
		Instance->setBlackWin(true)
	else if ((Player & STONE_BLACK) == 0 && Instance->getHasWon() && Instance->getBlackScore() < 10)
		Instance->setWhiteWin(true);
	else if ((Player & STONE_BLACK) != 0 && !Break && !(winByCapture() * 2 + Instance->getWhiteScore() >= 10))
		Instance->setBlackWin(true);
	else if ((Player & STONE_WHITE) != 0 && !Break && !(winByCapture() * 2 + Instance->getBlackScore() >= 10))
		Instance->setWhiteWin(true);
	else {
		Instance->setHasWon(true);
		Instance->setWinCoord(y, x);
	}
}

// Private function used in YouWIn
static void Rules::somethingToEatWithPlayer(int Opponent, int i, int j, GameManager * Instance)
{
	if (i < BOARD_HEIGHT - 3 && (Instance->getBoard()[(i + 1) * BOARD_WIDTH + j] & Opponent) != 0 && (Instance->getBoard()[(i + 2) * BOARD_WIDTH + j] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i + 3) * BOARD_WIDTH + j])) // Bottom
		Instance.getListEatCoord.push_front(Coord(i + 3, j));
	if (j < BOARD_WIDTH - 3 && (Instance->getBoard()[i * BOARD_WIDTH + j + 1] & Opponent) != 0 && (Instance->getBoard()[i * BOARD_WIDTH + j + 2] & Opponent) != 0 && EmptyCase(Instance->getBoard()[i * BOARD_WIDTH + j + 3])) // Right
		Instance.getListEatCoord.push_front(Coord(i, j + 3));
	if (i >= 3 && j < BOARD_WIDTH - 3 && (Instance->getBoard()[(i - 1) * BOARD_WIDTH + j + 1] & Opponent) != 0 && (Instance->getBoard()[(i - 2) * BOARD_WIDTH + j + 2] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i - 3) * BOARD_WIDTH + j + 3])) // Top Right
		Instance.getListEatCoord.push_front(Coord(i - 3, j + 3));
	if (i < BOARD_HEIGHT - 3 && j < BOARD_WIDTH - 3 && (Instance->Board()[(i + 1) * BOARD_WIDTH + j + 1] & Opponent) != 0 && (Instance->Board()[(i + 2) * BOARD_WIDTH + j + 2] & Opponent) != 0 && EmptyCase(Instance->Board()[(i + 3) * BOARD_WIDTH + j + 3])) // Bottom Right
		Instance.getListEatCoord.push_front(Coord(i + 3, j + 3));
	if (i >= 3 && j >= 3 && (Instance->getBoard()[(i - 1) * BOARD_WIDTH + j - 1] & Opponent) != 0 && (Instance->getBoard()[(i - 2) * BOARD_WIDTH + j - 2] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i - 3) * BOARD_WIDTH + j - 3]))  // Top Left
		Instance.getListEatCoord.push_front(Coord(i - 3, j - 3));
	if (i >= 3 && (Instance->getBoard()[(i - 1) * BOARD_WIDTH + j] & Opponent) != 0 && (Instance->getBoard()[(i - 2) * BOARD_WIDTH + j] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i - 3) * BOARD_WIDTH + j])) // Top
		Instance.getListEatCoord.push_front(Coord(i - 3, j));
	if (j >= 3 && (Instance->getBoard()[i * BOARD_WIDTH + j - 1] & Opponent) != 0 && (Instance->getBoard()[i * BOARD_WIDTH + j - 2] & Opponent) != 0 && EmptyCase(Instance->getBoard()[i * BOARD_WIDTH + j - 3])) // Left
		Instance.getListEatCoord.push_front(Coord(i, j - 3));
	if (j >= 3 && i < BOARD_HEIGHT - 3 && (Instance->getBoard()[(i + 1) * BOARD_WIDTH + j - 1] & Opponent) != 0 && (Instance->getBoard()[(i + 2) * BOARD_WIDTH + j - 2] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i + 3) * BOARD_WIDTH + j - 3])) // Bottom Left
		Instance.getListEatCoord.push_front(Coord(i + 3, j - 3));
}

// Private function used in YouWIn
static void Rules::somethingToEatOnTheBoard(int Player, int Opponent, GameManager * Instance)
{
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if ((Instance.getBoard()[i * BOARD_WIDTH + j] & Player) != 0) {
				somethingToEatWithPlayer(Opponent, i, j, Intance);
			}
		}
	}
}

// Return True if there is a double tree on the cell [y,x]
static bool Rules::checkDoubleTreeBox(int y, int x, GameManager * Instance)
{
	int Player1;
	if (!Instance->getbPlayerOneTurn())
		Player1 = STONE_BLACK;
	else
		Player1 = STONE_WHITE;
	int NumTree = 0;

	//  - X 0 X -
	if (x >= 2 && x < BOARD_WIDTH - 2 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x - 2]) && Instance->getBoard()[y * BOARD_WIDTH + x - 1] == Player1 && Instance->getBoard()[y * BOARD_WIDTH + x + 1] == Player1 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x + 2]))
		NumTree++;
	if (y >= 2 && y < BOARD_HEIGHT - 2 && EmptyCase(Instance->getBoard()[(y - 2) * BOARD_WIDTH + x]) && Instance->getBoard()[(y - 1) * BOARD_WIDTH + x] == Player1 && Instance->getBoard()[(y + 1) * BOARD_WIDTH + x] == Player1 && EmptyCase(Instance->getBoard()[(y + 2) * BOARD_WIDTH + x]))
		NumTree++;
	if (x >= 2 && x < BOARD_WIDTH - 2 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x - 2]) && y >= 2 && y < BOARD_HEIGHT - 2
		&& EmptyCase(Instance->getBoard()[(y - 2) * BOARD_WIDTH + x - 2]) && Instance->getBoard()[(y - 1) * BOARD_WIDTH + x - 1] == Player1 && Instance->getBoard()[(y + 1) * BOARD_WIDTH + x + 1] == Player1 && EmptyCase(Instance->getBoard()[(y + 2) * BOARD_WIDTH + x + 2]))
		NumTree++;
	if (x >= 2 && x < BOARD_WIDTH - 2 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x - 2]) && y >= 2 && y < BOARD_HEIGHT - 2
		&& EmptyCase(Instance->getBoard()[(y + 2) * BOARD_WIDTH + x - 2]) && Instance->getBoard()[(y + 1) * BOARD_WIDTH + x - 1] == Player1 && Instance->getBoard()[(y - 1) * BOARD_WIDTH + x + 1] == Player1 && EmptyCase(Instance->getBoard()[(y - 2) * BOARD_WIDTH + x + 2]))
		NumTree++;

	// - X X 0 -
	if (x >= 3 && x < BOARD_WIDTH - 1 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x - 3]) && Instance->getBoard()[y * BOARD_WIDTH + x - 2] == Player1 && Instance->getBoard()[y * BOARD_WIDTH + x - 1] == Player1 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x + 1]))
		NumTree++;
	if (x >= 1 && x < BOARD_WIDTH - 3 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x - 1]) && Instance->getBoard()[y * BOARD_WIDTH + x + 1] == Player1 && Instance->getBoard()[y * BOARD_WIDTH + x + 2] == Player1 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x + 3]))
		NumTree++;
	if (y >= 3 && y < BOARD_HEIGHT - 1 && EmptyCase(Instance->getBoard()[(y - 3) * BOARD_WIDTH + x]) && Instance->getBoard()[(y - 2) * BOARD_WIDTH + x] == Player1 && Instance->getBoard()[(y - 1) * BOARD_WIDTH + x] == Player1 && EmptyCase(Instance->getBoard()[(y + 1) * BOARD_WIDTH + x]))
		NumTree++;
	if (y >= 1 && y < BOARD_HEIGHT - 3 && EmptyCase(Instance->getBoard()[(y - 1) * BOARD_WIDTH + x]) && Instance->getBoard()[(y + 1) * BOARD_WIDTH + x] == Player1 && Instance->getBoard()[(y + 2) * BOARD_WIDTH + x] == Player1 && EmptyCase(Instance->getBoard()[(y + 3) * BOARD_WIDTH + x]))
		NumTree++;
	if (x >= 3 && x < BOARD_WIDTH - 1 && y >= 3 && y < BOARD_HEIGHT - 1
		&& EmptyCase(Instance->getBoard()[(y - 3) * BOARD_WIDTH + x - 3]) && Instance->getBoard()[(y - 2) * BOARD_WIDTH + x - 2] == Player1 && Instance->getBoard()[(y - 1) * BOARD_WIDTH + x - 1] == Player1 && EmptyCase(Instance->getBoard()[(y + 1) * BOARD_WIDTH + x + 1]))
		NumTree++;
	if (x >= 1 && x < BOARD_WIDTH - 3 && y >= 1 && y < BOARD_HEIGHT - 3 
		&& EmptyCase(Instance->getBoard()[(y - 1) * BOARD_WIDTH + x - 1]) && Instance->getBoard()[(y + 1) * BOARD_WIDTH + x + 1] == Player1 && Instance->getBoard()[(y + 2) * BOARD_WIDTH + x + 2] == Player1 && EmptyCase(Instance->getBoard()[(y + 3) * BOARD_WIDTH + x + 3]))
		NumTree++;
	if (x >= 3 && x < BOARD_WIDTH - 1 && y >= 1 && y < BOARD_HEIGHT - 3 
		&& EmptyCase(Instance->getBoard()[(y + 3) * BOARD_WIDTH + x - 3]) && Instance->getBoard()[(y + 2) * BOARD_WIDTH + x - 2] == Player1 && Instance->getBoard()[(y + 1) * BOARD_WIDTH + x - 1] == Player1 && EmptyCase(Instance->getBoard()[(y - 1) * BOARD_WIDTH + x + 1]))
		NumTree++;
	if (x >= 1 && x < BOARD_WIDTH - 3 && y >= 3 && y < BOARD_HEIGHT - 1
		&& EmptyCase(Instance->getBoard()[(y + 1) * BOARD_WIDTH + x - 1]) && Instance->getBoard()[(y - 1) * BOARD_WIDTH + x + 1] == Player1 && Instance->getBoard()[(y - 2) * BOARD_WIDTH + x + 2] == Player1 && EmptyCase(Instance->getBoard()[(y - 3) * BOARD_WIDTH + x + 3]))
		NumTree++;
	
		// - X X - 0 -
	if (x >= 4 && x < BOARD_WIDTH - 1 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x - 4]) && Instance->getBoard()[y * BOARD_WIDTH + x - 3] == Player1 && Instance->getBoard()[y * BOARD_WIDTH + x - 2] == Player1 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x - 1])  && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x + 1]))
		NumTree++;
	if (x >= 1 && x < BOARD_WIDTH - 4 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x + 4]) && Instance->getBoard()[y * BOARD_WIDTH + x + 3] == Player1 && Instance->getBoard()[y * BOARD_WIDTH + x + 2] == Player1 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x + 1])  && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x - 1]))
		NumTree++;
	if (y >= 4 && y < BOARD_HEIGHT - 1 && EmptyCase(Instance->getBoard()[(y - 4) * BOARD_WIDTH + x]) && Instance->getBoard()[(y - 3) * BOARD_WIDTH + x] == Player1 && Instance->getBoard()[(y - 2) * BOARD_WIDTH + x] == Player1 && EmptyCase(Instance->getBoard()[(y - 1) * BOARD_WIDTH + x])  && EmptyCase(Instance->getBoard()[(y + 1) * BOARD_WIDTH + x]))
		NumTree++;
	if (y >= 1 && y < BOARD_HEIGHT - 4 && EmptyCase(Instance->getBoard()[(y + 4) * BOARD_WIDTH + x]) && Instance->getBoard()[(y + 3) * BOARD_WIDTH + x] == Player1 && Instance->getBoard()[(y + 2) * BOARD_WIDTH + x] == Player1 && EmptyCase(Instance->getBoard()[(y + 1) * BOARD_WIDTH + x])  && EmptyCase(Instance->getBoard()[(y - 1) * BOARD_WIDTH + x]))
		NumTree++;
	if (x >= 4 && x < BOARD_WIDTH - 1 && y >= 4 && y < BOARD_HEIGHT - 1
		&& EmptyCase(Instance->getBoard()[(y - 4) * BOARD_WIDTH + x - 4]) && Instance->getBoard()[(y - 3) * BOARD_WIDTH + x - 3] == Player1 && Instance->getBoard()[(y - 2) * BOARD_WIDTH + x - 2] == Player1 && EmptyCase(Instance->getBoard()[(y - 1) * BOARD_WIDTH + x - 1])  && EmptyCase(Instance->getBoard()[(y + 1) * BOARD_WIDTH + x + 1]))
		NumTree++;
	if (x >= 1 && x < BOARD_WIDTH - 4 && y >= 1 && y < BOARD_HEIGHT - 4
		&& EmptyCase(Instance->getBoard()[(y + 4) * BOARD_WIDTH + x + 4]) && Instance->getBoard()[(y + 3) * BOARD_WIDTH + x + 3] == Player1 && Instance->getBoard()[(y + 2) * BOARD_WIDTH + x + 2] == Player1 && EmptyCase(Instance->getBoard()[(y + 1) * BOARD_WIDTH + x + 1])  && EmptyCase(Instance->getBoard()[(y - 1) * BOARD_WIDTH + x - 1]))
		NumTree++;
	if (x >= 4 && x < BOARD_WIDTH - 1 && y >= 1 && y < BOARD_HEIGHT - 4
		&& EmptyCase(Instance->getBoard()[(y + 4) * BOARD_WIDTH + x - 4]) && Instance->getBoard()[(y + 3) * BOARD_WIDTH + x - 3] == Player1 && Instance->getBoard()[(y + 2) * BOARD_WIDTH + x - 2] == Player1 && EmptyCase(Instance->getBoard()[(y + 1) * BOARD_WIDTH + x - 1])  && EmptyCase(Instance->getBoard()[(y - 1) * BOARD_WIDTH + x + 1]))
		NumTree++;
	if (x >= 1 && x < BOARD_WIDTH - 4 && y >= 4 && y < BOARD_HEIGHT - 1
		&& EmptyCase(Instance->getBoard()[(y - 4) * BOARD_WIDTH + x + 4]) && Instance->getBoard()[(y - 3) * BOARD_WIDTH + x + 3] == Player1 && Instance->getBoard()[(y - 2) * BOARD_WIDTH + x + 2] == Player1 && EmptyCase(Instance->getBoard()[(y - 1) * BOARD_WIDTH + x + 1])  && EmptyCase(Instance->getBoard()[(y + 1) * BOARD_WIDTH + x - 1]))
		NumTree++;
	
		//  - X - 0 X -
	if (x >= 3 && x < BOARD_WIDTH - 2 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x - 3]) && Instance->getBoard()[y * BOARD_WIDTH + x - 2] == Player1 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x - 1]) && Instance->getBoard()[y * BOARD_WIDTH + x + 1] == Player1  && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x + 2]))
		NumTree++;
	if (x >= 2 && x < BOARD_WIDTH - 3 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x + 3]) && Instance->getBoard()[y * BOARD_WIDTH + x + 2] == Player1 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x + 1]) && Instance->getBoard()[y * BOARD_WIDTH + x - 1] == Player1  && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x - 2]))
		NumTree++;
	if (y >= 3 && y < BOARD_HEIGHT - 2 && EmptyCase(Instance->getBoard()[(y - 3) * BOARD_WIDTH + x]) && Instance->getBoard()[(y - 2) * BOARD_WIDTH + x] == Player1 && EmptyCase(Instance->getBoard()[(y - 1) * BOARD_WIDTH + x]) && Instance->getBoard()[(y + 1) * BOARD_WIDTH + x] == Player1  && EmptyCase(Instance->getBoard()[(y + 2) * BOARD_WIDTH + x]))
		NumTree++;
	if (y >= 2 && y < BOARD_HEIGHT - 3 && EmptyCase(Instance->getBoard()[(y + 3) * BOARD_WIDTH + x]) && Instance->getBoard()[(y + 2) * BOARD_WIDTH + x] == Player1 && EmptyCase(Instance->getBoard()[(y + 1) * BOARD_WIDTH + x]) && Instance->getBoard()[(y - 1) * BOARD_WIDTH + x] == Player1  && EmptyCase(Instance->getBoard()[(y - 2) * BOARD_WIDTH + x]))
		NumTree++;
	if (x >= 3 && x < BOARD_WIDTH - 2 && y >= 3 && y < BOARD_HEIGHT - 2
		&& EmptyCase(Instance->getBoard()[(y - 3) * BOARD_WIDTH + x - 3]) && Instance->getBoard()[(y - 2) * BOARD_WIDTH + x - 2] == Player1 && EmptyCase(Instance->getBoard()[(y - 1) * BOARD_WIDTH + x - 1]) && Instance->getBoard()[(y + 1) * BOARD_WIDTH + x + 1] == Player1  && EmptyCase(Instance->getBoard()[(y + 2) * BOARD_WIDTH + x + 2]))
		NumTree++;
	if (x >= 2 && x < BOARD_WIDTH - 3 && y >= 2 && y < BOARD_HEIGHT - 3
		&& EmptyCase(Instance->getBoard()[(y + 3) * BOARD_WIDTH + x + 3]) && Instance->getBoard()[(y + 2) * BOARD_WIDTH + x + 2] == Player1 && EmptyCase(Instance->getBoard()[(y + 1) * BOARD_WIDTH + x + 1]) && Instance->getBoard()[(y - 1) * BOARD_WIDTH + x - 1] == Player1  && EmptyCase(Instance->getBoard()[(y - 2) * BOARD_WIDTH + x - 2]))
		NumTree++;
	if (x >= 3 && x < BOARD_WIDTH - 2 && y >= 2 && y < BOARD_HEIGHT - 3
		&& EmptyCase(Instance->getBoard()[(y + 3) * BOARD_WIDTH + x - 3]) && Instance->getBoard()[(y + 2) * BOARD_WIDTH + x - 2] == Player1 && EmptyCase(Instance->getBoard()[(y + 1) * BOARD_WIDTH + x - 1]) && Instance->getBoard()[(y - 1) * BOARD_WIDTH + x + 1] == Player1  && EmptyCase(Instance->getBoard()[(y - 2) * BOARD_WIDTH + x + 2]))
		NumTree++;
	if (x >= 2 && x < BOARD_WIDTH - 3 && y >= 3 && y < BOARD_HEIGHT - 2
		&& EmptyCase(Instance->getBoard()[(y - 3) * BOARD_WIDTH + x + 3]) && Instance->getBoard()[(y - 2) * BOARD_WIDTH + x + 2] == Player1 && EmptyCase(Instance->getBoard()[(y - 1) * BOARD_WIDTH + x + 1]) && Instance->getBoard()[(y + 1) * BOARD_WIDTH + x - 1] == Player1  && EmptyCase(Instance->getBoard()[(y + 2) * BOARD_WIDTH + x - 2]))
		NumTree++;
	if (NumTree >= 2)
	{
		if (!Instance->getbPlayerOneTurn() && (Instance->getBoard()[y * BOARD_WIDTH + x] & STONE_BLACKDoubleTree) == 0)
			Instance->getBoard()[y * BOARD_WIDTH + x] += STONE_BLACKDoubleTree;
		else if (Instance->getbPlayerOneTurn() && (Instance->getBoard()[y * BOARD_WIDTH + x] & STONE_WHITEDoubleTree) == 0)
			Instance->getBoard()[y * BOARD_WIDTH + x] += STONE_WHITEDoubleTree;
		return true;
	}
	else 
	{
		if ((Instance->getBoard()[y * BOARD_WIDTH + x] & STONE_WHITEDoubleTree) != 0 && Instance->getbPlayerOneTurn())
			Instance->getBoard()[y * BOARD_WIDTH + x] -= STONE_WHITEDoubleTree;
		if ((Instance->getBoard()[y * BOARD_WIDTH + x] & STONE_BLACKDoubleTree) != 0 && !Instance->getbPlayerOneTurn())
			Instance->getBoard()[y * BOARD_WIDTH + x] -= STONE_BLACKDoubleTree;
		return false;
	}
}