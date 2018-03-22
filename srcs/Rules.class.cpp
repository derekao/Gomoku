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
bool Rules::EmptyCase(int Content)
{
	if ((Content & STONE_BLACK) == 0 && (Content & STONE_WHITE) == 0)
			return true;
		else
			return false;
}

// If there is 5 Stones aligned check if you can break the alignement or win eating stone
void Rules::youWin(int Player, int Opponent, int y, int x, GameManager * Instance)
{
	bool Break = breakWin(Player, Opponent, y, x, Instance);

	somethingToEatOnTheBoard(Opponent, Player, Instance);
	if ((Player & STONE_WHITE) == 0 && Instance->getHasWon() && Instance->getWhiteScore() < 10)
		Instance->setBlackWin(true);
	else if ((Player & STONE_BLACK) == 0 && Instance->getHasWon() && Instance->getBlackScore() < 10)
		Instance->setWhiteWin(true);
	else if ((Player & STONE_BLACK) != 0 && !Break && !(winByCapture(Instance) * 2 + Instance->getWhiteScore() >= 10))
		Instance->setBlackWin(true);
	else if ((Player & STONE_WHITE) != 0 && !Break && !(winByCapture(Instance) * 2 + Instance->getBlackScore() >= 10))
		Instance->setWhiteWin(true);
	else {
		Instance->setHasWon(true);
		Instance->setWinCoord(y, x);
	}
    Instance->getListEatCoord().clear();
}

// Private function used in YouWIn
int Rules::winByCapture(GameManager * Instance)
{
	int y;
	int x;
	int points = 0;
	int tmpPoints;
	for (size_t i = 0; i < Instance->getListEatCoord().size();) {
		tmpPoints = 0;
		y = Instance->getListEatCoord()[i].y;
		x = Instance->getListEatCoord()[i].x;
		for (size_t j = i + 1; j < Instance->getListEatCoord().size();) {
			if (Instance->getListEatCoord()[j].y == y &&  Instance->getListEatCoord()[j].x == x) {
				Instance->getListEatCoord().erase(Instance->getListEatCoord().begin() + j);
				tmpPoints++;
			}
			else
				j++;
		}
		Instance->getListEatCoord().erase(Instance->getListEatCoord().begin() + i);
		tmpPoints++;
		if (tmpPoints > points)
			points = tmpPoints;
	}
	Instance->getListEatCoord().clear();
	return points;
}

// Private function used in YouWIn
void Rules::somethingToEatWithPlayer(int Opponent, int i, int j, GameManager * Instance)
{
	if (i < BOARD_HEIGHT - 3 && (Instance->getBoard()[(i + 1) * BOARD_WIDTH + j] & Opponent) != 0 && (Instance->getBoard()[(i + 2) * BOARD_WIDTH + j] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i + 3) * BOARD_WIDTH + j])) // Bottom
		Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i + 3, j));
	if (j < BOARD_WIDTH - 3 && (Instance->getBoard()[i * BOARD_WIDTH + j + 1] & Opponent) != 0 && (Instance->getBoard()[i * BOARD_WIDTH + j + 2] & Opponent) != 0 && EmptyCase(Instance->getBoard()[i * BOARD_WIDTH + j + 3])) // Right
		Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i, j + 3));
	if (i >= 3 && j < BOARD_WIDTH - 3 && (Instance->getBoard()[(i - 1) * BOARD_WIDTH + j + 1] & Opponent) != 0 && (Instance->getBoard()[(i - 2) * BOARD_WIDTH + j + 2] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i - 3) * BOARD_WIDTH + j + 3])) // Top Right
		Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i - 3, j + 3));
	if (i < BOARD_HEIGHT - 3 && j < BOARD_WIDTH - 3 && (Instance->getBoard()[(i + 1) * BOARD_WIDTH + j + 1] & Opponent) != 0 && (Instance->getBoard()[(i + 2) * BOARD_WIDTH + j + 2] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i + 3) * BOARD_WIDTH + j + 3])) // Bottom Right
		Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i + 3, j + 3));
	if (i >= 3 && j >= 3 && (Instance->getBoard()[(i - 1) * BOARD_WIDTH + j - 1] & Opponent) != 0 && (Instance->getBoard()[(i - 2) * BOARD_WIDTH + j - 2] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i - 3) * BOARD_WIDTH + j - 3]))  // Top Left
		Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i - 3, j - 3));
	if (i >= 3 && (Instance->getBoard()[(i - 1) * BOARD_WIDTH + j] & Opponent) != 0 && (Instance->getBoard()[(i - 2) * BOARD_WIDTH + j] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i - 3) * BOARD_WIDTH + j])) // Top
		Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i - 3, j));
	if (j >= 3 && (Instance->getBoard()[i * BOARD_WIDTH + j - 1] & Opponent) != 0 && (Instance->getBoard()[i * BOARD_WIDTH + j - 2] & Opponent) != 0 && EmptyCase(Instance->getBoard()[i * BOARD_WIDTH + j - 3])) // Left
		Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i, j - 3));
	if (j >= 3 && i < BOARD_HEIGHT - 3 && (Instance->getBoard()[(i + 1) * BOARD_WIDTH + j - 1] & Opponent) != 0 && (Instance->getBoard()[(i + 2) * BOARD_WIDTH + j - 2] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i + 3) * BOARD_WIDTH + j - 3])) // Bottom Left
		Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i + 3, j - 3));
}

// Private function used in YouWIn
void Rules::somethingToEatOnTheBoard(int Player, int Opponent, GameManager * Instance)
{
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if ((Instance->getBoard()[i * BOARD_WIDTH + j] & Player) != 0) {
				somethingToEatWithPlayer(Opponent, i, j, Instance);
			}
		}
	}
}

// Private function used in YouWIn
void Rules::checkBreak(bool first, GameManager * Instance)
{
    int y;
    int x;
    int doublon;
    for (size_t i = 0; i < Instance->getListEatCoord().size();) {
        doublon = 0;
        y = Instance->getListEatCoord()[i].y;
        x = Instance->getListEatCoord()[i].x;
        for (size_t j = i + 1; j < Instance->getListEatCoord().size();) {
            if ( Instance->getListEatCoord()[j].y == y &&  Instance->getListEatCoord()[j].x == x) {
                Instance->getListEatCoord().erase(Instance->getListEatCoord().begin() + j);
                doublon++;
            }
            else
                j++;
        }
        if (!first && doublon == 0)
            Instance->getListEatCoord().erase(Instance->getListEatCoord().begin() + i);
        else
            i++;
    }
}

// Private function used in YouWIn
void Rules::canBeEat(int Player, int Opponent, int i, int j, GameManager * Instance)
{
    //Top
    if (i >= 2 && i < BOARD_HEIGHT - 1 && (Instance->getBoard()[(i - 1) * BOARD_WIDTH + j] & Player) != 0 && (Instance->getBoard()[(i + 1) * BOARD_WIDTH + j] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i - 2) * BOARD_WIDTH + j])) 
        Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i - 2, j));
    if (i >= 1 && i < BOARD_HEIGHT - 2 && (Instance->getBoard()[(i + 1) * BOARD_WIDTH + j] & Player) != 0 && (Instance->getBoard()[(i + 2) * BOARD_WIDTH + j] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i - 1) * BOARD_WIDTH + j]))
        Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i - 1, j));

    //Bottom
    if (i >= 2 && i < BOARD_HEIGHT - 1 && (Instance->getBoard()[(i - 1) * BOARD_WIDTH + j] & Player) != 0 && (Instance->getBoard()[(i - 2) * BOARD_WIDTH + j] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i + 1) * BOARD_WIDTH + j])) 
        Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i + 1, j));
    if (i >= 1 && i < BOARD_HEIGHT - 2 && (Instance->getBoard()[(i + 1) * BOARD_WIDTH + j] & Player) != 0 && (Instance->getBoard()[(i - 1) * BOARD_WIDTH + j] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i + 2) * BOARD_WIDTH + j]))
        Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i + 2, j));

    //Right
    if (j >= 1 && j < BOARD_WIDTH - 2 && (Instance->getBoard()[i * BOARD_WIDTH + j + 1] & Player) != 0 && (Instance->getBoard()[i * BOARD_WIDTH + j - 1] & Opponent) != 0 && EmptyCase(Instance->getBoard()[i * BOARD_WIDTH + j + 2]))
        Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i, j + 2));
    if (j >= 2 && j < BOARD_WIDTH - 1 && (Instance->getBoard()[i * BOARD_WIDTH + j - 1] & Player) != 0 && (Instance->getBoard()[i * BOARD_WIDTH + j - 2] & Opponent) != 0 && EmptyCase(Instance->getBoard()[i * BOARD_WIDTH + j + 1]))
        Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i, j + 1));

    //Left
    if (j >= 2 && j < BOARD_WIDTH - 1 && (Instance->getBoard()[i * BOARD_WIDTH + j - 1] & Player) != 0 && (Instance->getBoard()[i * BOARD_WIDTH + j + 1] & Opponent) != 0 && EmptyCase(Instance->getBoard()[i * BOARD_WIDTH + j - 2]))
        Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i, j - 2));
    if (j >= 1 && j < BOARD_WIDTH - 2 && (Instance->getBoard()[i * BOARD_WIDTH + j + 1] & Player) != 0 && (Instance->getBoard()[i * BOARD_WIDTH + j + 2] & Opponent) != 0 && EmptyCase(Instance->getBoard()[i * BOARD_WIDTH + j - 1]))
        Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i, j - 1));
//Top-Right
    if (j >= 2 && j < BOARD_WIDTH - 1 && i >= 1 && i < BOARD_HEIGHT - 2 && (Instance->getBoard()[(i + 1) * BOARD_WIDTH + j - 1] & Player) != 0 && (Instance->getBoard()[(i + 2) * BOARD_WIDTH + j - 2] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i - 1) * BOARD_WIDTH + j + 1]))
        Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i - 1, j + 1));
    if (j >= 1 && j < BOARD_WIDTH - 2 && i >= 2 && i < BOARD_HEIGHT - 1 && (Instance->getBoard()[(i - 1) * BOARD_WIDTH + j + 1] & Player) != 0 && (Instance->getBoard()[(i + 1) * BOARD_WIDTH + j - 1] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i - 2) * BOARD_WIDTH + j + 2]))
        Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i - 2, j + 2));

    //Bot-Left
    if (j >= 2 && j < BOARD_WIDTH - 1 && i >= 1 && i < BOARD_HEIGHT - 2 && (Instance->getBoard()[(i + 1) * BOARD_WIDTH + j - 1] & Player) != 0 && (Instance->getBoard()[(i - 1) * BOARD_WIDTH + j + 1] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i + 2) * BOARD_WIDTH + j - 2]))
        Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i + 2, j - 2));
    if (j >= 1 && j < BOARD_WIDTH - 2 && i >= 2 && i < BOARD_HEIGHT - 1 && (Instance->getBoard()[(i - 1) * BOARD_WIDTH + j + 1] & Player) != 0 && (Instance->getBoard()[(i - 2) * BOARD_WIDTH + j + 2] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i + 1) * BOARD_WIDTH + j - 1]))
        Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i + 1, j - 1));

    //Top-Left
    if (j >= 1 && j < BOARD_WIDTH - 2 && i >= 1 && i < BOARD_HEIGHT - 2 && (Instance->getBoard()[(i + 1) * BOARD_WIDTH + j + 1] & Player) != 0 && (Instance->getBoard()[(i + 2) * BOARD_WIDTH + j + 2] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i - 1) * BOARD_WIDTH + j - 1]))
        Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i - 1, j - 1));
    if (j >= 2 && j < BOARD_WIDTH - 1 && i >= 2 && i < BOARD_HEIGHT - 1 && (Instance->getBoard()[(i - 1) * BOARD_WIDTH + j - 1] & Player) != 0 && (Instance->getBoard()[(i + 1) * BOARD_WIDTH + j + 1] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i - 2) * BOARD_WIDTH + j - 2]))
        Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i - 2, j - 2));

    //Bot-Right
    if (j >= 1 && j < BOARD_WIDTH - 2 && i >= 1 && i < BOARD_HEIGHT - 2 && (Instance->getBoard()[(i + 1) * BOARD_WIDTH + j + 1] & Player) != 0 && (Instance->getBoard()[(i - 1) * BOARD_WIDTH + j - 1] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i + 2) * BOARD_WIDTH + j + 2]))
        Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i + 2, j + 2));
    if (j >= 2 && j < BOARD_WIDTH - 1 && i >= 2 && i < BOARD_HEIGHT - 1 && (Instance->getBoard()[(i - 1) * BOARD_WIDTH + j - 1] & Player) != 0 && (Instance->getBoard()[(i - 2) * BOARD_WIDTH + j - 2] & Opponent) != 0 && EmptyCase(Instance->getBoard()[(i + 1) * BOARD_WIDTH + j + 1]))
        Instance->getListEatCoord().insert(Instance->getListEatCoord().begin(), Coord(i + 1, j + 1));

}

// Private function used in YouWIn
bool Rules::breakWin(int Player, int Opponent, int y, int x, GameManager * Instance)
{
    int Align = 1;
    int nbAlign = 0;
    int i = y;
    int j = x + 1;
    int lstSize = 0;
    bool stillBreakable;

    Rules::canBeEat(Player, Opponent, y, x, Instance);
    if (Instance->getListEatCoord().size() > 0) {
        Instance->getListEatCoord().clear();
        return true;
    }
    //Horizontal
    while (j < BOARD_WIDTH && Instance->getBoard()[i * BOARD_WIDTH + j] == Player)
    {
        Rules::canBeEat(Player, Opponent, i, j, Instance);
        j++;
        Align++;
    }
    j = x - 1;
    while (j >= 0 && Instance->getBoard()[i * BOARD_WIDTH + j] == Player)
    {
        Rules::canBeEat(Player, Opponent, i, j, Instance);
        j--;
        Align++;
    }
    if (Align >= 5) {
        checkBreak((nbAlign == 0 ? true : false), Instance);
        lstSize = Instance->getListEatCoord().size();
        nbAlign++;
    }
    else {
        Instance->getListEatCoord().erase(Instance->getListEatCoord().begin(), Instance->getListEatCoord().end() - lstSize );
    }

    Align = 1;
    i = y + 1;
    j = x;
    //Vertical
    while (i < BOARD_HEIGHT && Instance->getBoard()[i * BOARD_WIDTH + j] == Player)
    {
        Rules::canBeEat(Player, Opponent, i, j, Instance);
        i++;
        Align++;
    }
    i = y - 1;
    while (i >= 0 && Instance->getBoard()[i * BOARD_WIDTH + j] == Player)
    {
        Rules::canBeEat(Player, Opponent, i, j, Instance);
        i--;
        Align++;
    }
    if (Align >= 5) {
        checkBreak((nbAlign == 0 ? true : false), Instance);
        lstSize = Instance->getListEatCoord().size();
        nbAlign++;
    }
    else {
        Instance->getListEatCoord().erase(Instance->getListEatCoord().begin(), Instance->getListEatCoord().end() - lstSize );
    }

    Align = 1;
    i = y + 1;
    j = x + 1;

    //Diagonal Top->Bottom
    while (i < BOARD_HEIGHT && j < BOARD_WIDTH && Instance->getBoard()[i * BOARD_WIDTH + j] == Player)
    {
        Rules::canBeEat( Player, Opponent,  i, j, Instance);
        i++;
        j++;
        Align++;
    }
    i = y - 1;
    j = x - 1;
    while (i >= 0 && j >= 0 && Instance->getBoard()[i * BOARD_WIDTH + j] == Player)
    {
        Rules::canBeEat(Player, Opponent, i, j, Instance);
        i--;
        j--;
        Align++;
    }
    if (Align >= 5) {
        checkBreak((nbAlign == 0 ? true : false), Instance);
        lstSize = Instance->getListEatCoord().size();
        nbAlign++;
    }
    else {
        Instance->getListEatCoord().erase(Instance->getListEatCoord().begin(), Instance->getListEatCoord().end() - lstSize );
    }

    Align = 1;
    i = y + 1;
    j = x - 1;
    //Diagonal Bottom->Top
    while (i < BOARD_HEIGHT && j >= 0 && Instance->getBoard()[i * BOARD_WIDTH + j] == Player)
    {
        Rules::canBeEat(Player, Opponent, i, j, Instance);
        i++;
        j--;
        Align++;            
    }
    i = y - 1;
    j = x + 1;
    while (j < BOARD_WIDTH && i >= 0 && Instance->getBoard()[i * BOARD_WIDTH + j] == Player)
    {
        Rules::canBeEat(Player, Opponent, i, j, Instance);
        i--;
        j++;
        Align++;
        
    }
    if (Align >= 5) {
        checkBreak((nbAlign == 0 ? true : false), Instance);
        lstSize = Instance->getListEatCoord().size();
        nbAlign++;
    }
    else {
        Instance->getListEatCoord().erase(Instance->getListEatCoord().begin(), Instance->getListEatCoord().end() - lstSize );
    }
    stillBreakable = Instance->getListEatCoord().size() > 0 ? true : false;
    Instance->getListEatCoord().clear();
    return stillBreakable;
}

// Return True if the Cell [i,j] allow you yo eat Opponent Stones
bool Rules::somethingToEatWithEmpty(int Player, int Opponent, int i, int j, GameManager * Instance)
{
	bool canEat = false;
	if (i < BOARD_HEIGHT - 3 && (Instance->getBoard()[(i + 1) * BOARD_WIDTH + j] & Opponent) != 0 && (Instance->getBoard()[(i + 2) * BOARD_WIDTH + j] & Opponent) != 0 && (Instance->getBoard()[(i + 3) * BOARD_WIDTH + j] & Player) != 0) // Bottom
		canEat = true;
	if (j < BOARD_WIDTH - 3 && (Instance->getBoard()[i * BOARD_WIDTH + j + 1] & Opponent) != 0 && (Instance->getBoard()[i * BOARD_WIDTH + j + 2] & Opponent) != 0 && (Instance->getBoard()[i * BOARD_WIDTH + j + 3] & Player) != 0) // Right
		canEat = true;
	if (i >= 3 && j < BOARD_WIDTH - 3 && (Instance->getBoard()[(i - 1) * BOARD_WIDTH + j + 1] & Opponent) != 0 && (Instance->getBoard()[(i - 2) * BOARD_WIDTH + j + 2] & Opponent) != 0 && (Instance->getBoard()[(i - 3) * BOARD_WIDTH + j + 3] & Player) != 0) // Top Right
		canEat = true;
	if (i < BOARD_HEIGHT - 3 && j < BOARD_WIDTH - 3 && (Instance->getBoard()[(i + 1) * BOARD_WIDTH + j + 1] & Opponent) != 0 && (Instance->getBoard()[(i + 2) * BOARD_WIDTH + j + 2] & Opponent) != 0 && (Instance->getBoard()[(i + 3) * BOARD_WIDTH + j + 3] & Player) != 0) // Bottom Right
		canEat = true;
	if (i >= 3 && j >= 3 && (Instance->getBoard()[(i - 1) * BOARD_WIDTH + j - 1] & Opponent) != 0 && (Instance->getBoard()[(i - 2) * BOARD_WIDTH + j - 2] & Opponent) != 0 && (Instance->getBoard()[(i - 3) * BOARD_WIDTH + j - 3] & Player) != 0)  //  Top Left
		canEat = true;
	if (i >= 3 && (Instance->getBoard()[(i - 1) * BOARD_WIDTH + j] & Opponent) != 0 && (Instance->getBoard()[(i - 2) * BOARD_WIDTH + j] & Opponent) != 0 && (Instance->getBoard()[(i - 3) * BOARD_WIDTH + j] & Player) != 0) // Top
		canEat = true;
	if (j >= 3 && (Instance->getBoard()[i * BOARD_WIDTH + j - 1] & Opponent) != 0 && (Instance->getBoard()[i * BOARD_WIDTH + j - 2] & Opponent) != 0 && (Instance->getBoard()[i * BOARD_WIDTH + j - 3] & Player) != 0) // Left
		canEat = true;
	if (j >= 3 && i < BOARD_HEIGHT - 3 && (Instance->getBoard()[(i + 1) * BOARD_WIDTH + j - 1] & Opponent) != 0 && (Instance->getBoard()[(i + 2) * BOARD_WIDTH + j - 2] & Opponent) != 0 && (Instance->getBoard()[(i + 3) * BOARD_WIDTH + j - 3] & Player) != 0) // Bottom Left
		canEat = true;
	return canEat;
}

// Return True if there is a double tree on the cell [y,x]
bool Rules::CheckDoubleTreeBox(int y, int x, int Player1, GameManager * Instance)
{
	int NumTree = 0;

	//  - X 0 X -
	if (x >= 2 && x < BOARD_WIDTH - 2 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x - 2]) && Instance->getBoard()[y * BOARD_WIDTH + x - 1] == Player1 && Instance->getBoard()[y * BOARD_WIDTH + x + 1] == Player1 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x + 2]))
		NumTree++;
	if (y >= 2 && y < BOARD_HEIGHT - 2 && EmptyCase(Instance->getBoard()[(y - 2) * BOARD_WIDTH + x]) && Instance->getBoard()[(y - 1) * BOARD_WIDTH + x] == Player1 && Instance->getBoard()[(y + 1) * BOARD_WIDTH + x] == Player1 && EmptyCase(Instance->getBoard()[(y + 2) * BOARD_WIDTH + x]))
		NumTree++;
	if (x >= 2 && x < BOARD_WIDTH - 2 && y >= 2 && y < BOARD_HEIGHT - 2
		&& EmptyCase(Instance->getBoard()[(y - 2) * BOARD_WIDTH + x - 2]) && Instance->getBoard()[(y - 1) * BOARD_WIDTH + x - 1] == Player1 && Instance->getBoard()[(y + 1) * BOARD_WIDTH + x + 1] == Player1 && EmptyCase(Instance->getBoard()[(y + 2) * BOARD_WIDTH + x + 2]))
		NumTree++;
	if (x >= 2 && x < BOARD_WIDTH - 2 && y >= 2 && y < BOARD_HEIGHT - 2
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

		// - X - X 0 -
	if (x >= 4 && x < BOARD_WIDTH - 1 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x - 4]) && Instance->getBoard()[y * BOARD_WIDTH + x - 3] == Player1 && Instance->getBoard()[y * BOARD_WIDTH + x - 1] == Player1 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x - 2])  && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x + 1]))
		NumTree++;
	if (x >= 1 && x < BOARD_WIDTH - 4 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x + 4]) && Instance->getBoard()[y * BOARD_WIDTH + x + 3] == Player1 && Instance->getBoard()[y * BOARD_WIDTH + x + 1] == Player1 && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x + 2])  && EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x - 1]))
		NumTree++;
	if (y >= 4 && y < BOARD_HEIGHT - 1 && EmptyCase(Instance->getBoard()[(y - 4) * BOARD_WIDTH + x]) && Instance->getBoard()[(y - 3) * BOARD_WIDTH + x] == Player1 && Instance->getBoard()[(y - 1) * BOARD_WIDTH + x] == Player1 && EmptyCase(Instance->getBoard()[(y - 2) * BOARD_WIDTH + x])  && EmptyCase(Instance->getBoard()[(y + 1) * BOARD_WIDTH + x]))
		NumTree++;
	if (y >= 1 && y < BOARD_HEIGHT - 4 && EmptyCase(Instance->getBoard()[(y + 4) * BOARD_WIDTH + x]) && Instance->getBoard()[(y + 3) * BOARD_WIDTH + x] == Player1 && Instance->getBoard()[(y + 1) * BOARD_WIDTH + x] == Player1 && EmptyCase(Instance->getBoard()[(y + 2) * BOARD_WIDTH + x])  && EmptyCase(Instance->getBoard()[(y - 1) * BOARD_WIDTH + x]))
		NumTree++;
	if (x >= 4 && x < BOARD_WIDTH - 1 && y >= 4 && y < BOARD_HEIGHT - 1
		&& EmptyCase(Instance->getBoard()[(y - 4) * BOARD_WIDTH + x - 4]) && Instance->getBoard()[(y - 3) * BOARD_WIDTH + x - 3] == Player1 && Instance->getBoard()[(y - 1) * BOARD_WIDTH + x - 1] == Player1 && EmptyCase(Instance->getBoard()[(y - 2) * BOARD_WIDTH + x - 2])  && EmptyCase(Instance->getBoard()[(y + 1) * BOARD_WIDTH + x + 1]))
		NumTree++;
	if (x >= 1 && x < BOARD_WIDTH - 4 && y >= 1 && y < BOARD_HEIGHT - 4
		&& EmptyCase(Instance->getBoard()[(y + 4) * BOARD_WIDTH + x + 4]) && Instance->getBoard()[(y + 3) * BOARD_WIDTH + x + 3] == Player1 && Instance->getBoard()[(y + 1) * BOARD_WIDTH + x + 1] == Player1 && EmptyCase(Instance->getBoard()[(y + 2) * BOARD_WIDTH + x + 2])  && EmptyCase(Instance->getBoard()[(y - 1) * BOARD_WIDTH + x - 1]))
		NumTree++;
	if (x >= 4 && x < BOARD_WIDTH - 1 && y >= 1 && y < BOARD_HEIGHT - 4
		&& EmptyCase(Instance->getBoard()[(y + 4) * BOARD_WIDTH + x - 4]) && Instance->getBoard()[(y + 3) * BOARD_WIDTH + x - 3] == Player1 && Instance->getBoard()[(y + 1) * BOARD_WIDTH + x - 1] == Player1 && EmptyCase(Instance->getBoard()[(y + 2) * BOARD_WIDTH + x - 2])  && EmptyCase(Instance->getBoard()[(y - 1) * BOARD_WIDTH + x + 1]))
		NumTree++;
	if (x >= 1 && x < BOARD_WIDTH - 4 && y >= 4 && y < BOARD_HEIGHT - 1
		&& EmptyCase(Instance->getBoard()[(y - 4) * BOARD_WIDTH + x + 4]) && Instance->getBoard()[(y - 3) * BOARD_WIDTH + x + 3] == Player1 && Instance->getBoard()[(y - 1) * BOARD_WIDTH + x + 1] == Player1 && EmptyCase(Instance->getBoard()[(y - 2) * BOARD_WIDTH + x + 2])  && EmptyCase(Instance->getBoard()[(y + 1) * BOARD_WIDTH + x - 1]))
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
		if (!Instance->getbPlayerOneTurn() && (Instance->getBoard()[y * BOARD_WIDTH + x] & STONE_BLACKDOUBLETREE) == 0)
			Instance->getBoard()[y * BOARD_WIDTH + x] += STONE_BLACKDOUBLETREE;
		else if (Instance->getbPlayerOneTurn() && (Instance->getBoard()[y * BOARD_WIDTH + x] & STONE_WHITEDOUBLETREE) == 0)
			Instance->getBoard()[y * BOARD_WIDTH + x] += STONE_WHITEDOUBLETREE;
		return true;
	}
	else 
	{
		if ((Instance->getBoard()[y * BOARD_WIDTH + x] & STONE_WHITEDOUBLETREE) != 0 && Player1 == STONE_WHITE)
			Instance->getBoard()[y * BOARD_WIDTH + x] -= STONE_WHITEDOUBLETREE;
		if ((Instance->getBoard()[y * BOARD_WIDTH + x] & STONE_BLACKDOUBLETREE) != 0 && Player1 == STONE_BLACK)
			Instance->getBoard()[y * BOARD_WIDTH + x] -= STONE_BLACKDOUBLETREE;
		return false;
	}
}

// Return the number of 5 Aligned stone around [y,x] (Max 4)
int Rules::CheckWin(int Player, int y, int x, GameManager * Instance)
{
	int Align = 1;
	int nbAlign = 0;
	int i = y;
	int j = x + 1;

	if ((Instance->getBoard()[y * BOARD_WIDTH + x] & Player) == 0)
		return 0;
	//Horizontal
	while (j < BOARD_WIDTH && Instance->getBoard()[i * BOARD_WIDTH + j] == Player)
	{
		j++;
		Align++;
	}
	j = x - 1;
	while (j >= 0 && Instance->getBoard()[i * BOARD_WIDTH + j] == Player)
	{
		j--;
		Align++;
	}

	if (Align >= 5)
		nbAlign++;

	Align = 1;
	i = y + 1;
	j = x;

	//Vertical
	while (i < BOARD_HEIGHT && Instance->getBoard()[i * BOARD_WIDTH + j] == Player)
	{
		i++;
		Align++;
	}
	i = y - 1;
	while (i >= 0 && Instance->getBoard()[i * BOARD_WIDTH + j] == Player)
	{
		i--;
		Align++;
	}

	if (Align >= 5)
		nbAlign++;

	Align = 1;
	i = y + 1;
	j = x + 1;

	//Diagonal Top->Bottom
	while (i < BOARD_HEIGHT && j < BOARD_WIDTH && Instance->getBoard()[i * BOARD_WIDTH + j] == Player)
	{
		i++;
		j++;
		Align++;
	}
	i = y - 1;
	j = x - 1;
	while (i >= 0 && j >= 0 && Instance->getBoard()[i * BOARD_WIDTH + j] == Player)
	{
		i--;
		j--;
		Align++;
	}

	if (Align >= 5)
		nbAlign++;

	Align = 1;
	i = y + 1;
	j = x - 1;
	//Diagonal Bottom->Top
	while (i < BOARD_HEIGHT && j >= 0 && Instance->getBoard()[i * BOARD_WIDTH + j] == Player)
	{
		i++;
		j--;
		Align++;
	}
	i = y - 1;
	j = x + 1;
	while (j < BOARD_WIDTH && i >= 0 && Instance->getBoard()[i * BOARD_WIDTH + j] == Player)
	{
		i--;
		j++;
		Align++;
	}

	if (Align >= 5)
		nbAlign++;
	return nbAlign;
}