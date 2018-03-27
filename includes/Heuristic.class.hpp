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

#define CAPTURE 0
#define OTW_PLAYER 1
#define OTW_OPPONENT 2
#define TTW_PLAYER 3
#define TTW_OPPONENT 4
#define STRONG_MOVE 5
#define BAD_MOVE 6

#define FIRST_STONE_THREAT 8
#define SECOND_STONE_THREAT 32
#define THIRD_STONE_THREAT 128
#define FOURTH_STONE_THREAT 512
#define FITH_STONE_THREAT 2192

#define FIRST_STONE_TAKEN 600
#define SECOND_STONE_TAKEN 900
#define THIRD_STONE_TAKEN 1200
#define FOURTH_STONE_TAKEN 1500

#define SIZE_1 1
#define SIZE_2 10
#define SIZE_3 100
#define SIZE_4 1000
#define BLOCK_REDUCTION 2


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
	int CountHeuristicAlignmentScore(int, int, bool, bool, bool, int, bool);
	void getMovePriority(int , int , bool , bool , bool , bool , int , int , int, bool);
	void addMove(int, int, int);

public:
	Heuristic(int iPlayer, int iOpponent, GameManager * gInstance);

	// Return the value of the Board
	int BoardValue();

	// Search move aviable and fill Potential move in Instance
	void searchMoves();

	static bool ramdomMove;

};
