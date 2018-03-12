#pragma once

#include <iostream>
#include <cmath>
#include "GameManager.class.hpp"
#include "Rules.class.hpp"
#include "PotentialMove.hpp"
#include <fstream>

#define HORIZONTAL 1
#define VERTICAL 2
#define DIAGORIGHT 3
#define DIAGOLEFT 4

#define OTW_PLAYER 1
#define OTW_OPPONENT 2
#define TTW_PLAYER 3
#define TTW_OPPONENT 4
#define STRONG_MOVE 5
#define AVERAGE_MOVE 6
#define BAD_MOVE 7

#define CAPTURE 0 

class Heuristic {

private:

	int Player;
	int Opponent;
	GameManager * Instance;
	int HighestPriority;

	int CountHorizontalAlignmentScore(int, bool, bool = false);
	int CountVerticalAlignmentScore(int, bool, bool = false);
	int CountDiagonnalRightAlignmentScore(int, bool, bool = false);
	int CountDiagonnalLeftAlignmentScore(int, bool, bool = false);
	int CountHeuristicAlignmentScore(int, int, bool, bool, bool, int);
	void getMovePriority(int , int , bool , bool , bool , bool , int , int , int, bool);
	void addMove(int, int, int);

public:
	Heuristic(int iPlayer, int iOpponent, GameManager * gInstance);
	int BoardValue();
	void searchMoves();

};

// 1. Win Instant > All
// 2. Blocker une Win 
// 3. Win en deux coups Sois meme
// 4. Win deux coups de l’adversaire
// 5. Prise de pierre
// 6. Menance de prise de pierre
// 7. Menace de win de deux coups

// 8.Double deux