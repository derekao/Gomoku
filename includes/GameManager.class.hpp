// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GameManager.class.hpp                              :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/02/28 13:56:40 by semartin          #+#    #+#             //
//   Updated: 2018/02/28 13:56:41 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>
#include <vector>
#include <list>
#include "Coord.hpp"
#include "PotentialMove.hpp"

#define STONE_EMPTY 0
#define STONE_BLACK 1
#define STONE_WHITE 2
#define STONE_WHITEFORBIDDEN 4
#define STONE_BLACKFORBIDDEN 8
#define STONE_WHITEDOUBLETREE 16
#define STONE_BLACKDOUBLETREE 32

#define BOARD_WIDTH 19
#define BOARD_HEIGHT 19

#define MAX_INFINIT 1073741824
#define MIN_INFINIT -1073741825

class GameManager
{

private:
	GameManager();

	int HeuristicValue;
	GameManager * Parent;
	std::vector<GameManager *> Childs;
	Coord LastMove;

	int LowerBound;
	int UpperBound;
	int BoundDepth;

	bool BlackWin;
	bool WhiteWin;
	bool HasWon;
	bool bPlayerOneTurn;

	int WhiteScore;
	int BlackScore;

	int HighestPriority;

	std::vector<char> Board;
	std::vector<Coord> BlackStones;
	std::vector<Coord> WhiteStones;
	std::vector<PotentialMove> lPotentialMove;

	Coord WinPos;
	
	std::vector<Coord> ListEatCoord;

	//Monte Carlo
	int CounterChild;
	int CounterVisit;
	double WinScore;
	bool AlreadyExpand;


public:
	//Constructor
	GameManager(int _Board[], bool _HasWon, bool _bPlayerOneTurn, int _WhiteScore, int _BlackScore, int WinY, int WinX);
	GameManager(GameManager * src);
	
	/////////////
	// Accessor//
	/////////////

	// Tree Building Value
	int getHeuristicValue() { return HeuristicValue; }
	GameManager * getParent() { return Parent; }
	std::vector<GameManager *> & getChilds() { return Childs; }
	Coord & getLastMove() { return LastMove; }

	// MTDF Bound Value
	int getLowerBound() { return LowerBound; } 
	int getUpperBound() { return UpperBound; } 
	int getBoundDepth() { return BoundDepth; } 

	// Game State Value
	bool getBlackWin() { return BlackWin; }
	bool getWhiteWin() { return WhiteWin; }
	bool getHasWon() { return HasWon; }
	bool getbPlayerOneTurn() { return bPlayerOneTurn; }
	int getWhiteScore() { return WhiteScore; }
	int getBlackScore() { return BlackScore; }
	Coord & getWinPos() { return WinPos; }
	std::vector<Coord> & getListEatCoord() { return ListEatCoord; }
	
	// Move and Board Value
	int getHighestPriority() { return HighestPriority; }
	std::vector<char> & getBoard() { return Board; }
	std::vector<Coord> & getBlackStones() { return BlackStones; }
	std::vector<Coord> & getWhiteStones() { return WhiteStones; }
	std::vector<PotentialMove> & getPotentialMove() { return lPotentialMove; }


	// MCTS Acessor
	int getCounterChild() { return CounterChild; }
	int getCounterVisit() { return CounterVisit; }
	double getWinScore() { return WinScore; }
	bool getAlreadyExpand() { return AlreadyExpand; }

	/////////////
	// Mutator //
	/////////////

	// Tree Building Value
	void setHeuristicValue(int n) { HeuristicValue = n; }
	void setParent(GameManager * Board) { Parent = Board; }
	void setLastMove(Coord & move) { LastMove.y = move.y; LastMove.x = move.x; ;}

	// MTDF Bound Value
	void setLowerBound(int n) { LowerBound = n; }
	void setUpperBound(int n) { UpperBound = n; }
	void setBoundDepth(int n) { BoundDepth = n; }

	// Game State Value
	void setBlackWin(bool b) { BlackWin = b; }
	void setWhiteWin(bool b) { WhiteWin = b; }
	void setHasWon(bool b) { HasWon = b; }
	void setbPlayerOneTurn(bool b) { bPlayerOneTurn = b; }
	void setBlackScore(int n) { BlackScore = n; }
	void setWhiteScore(int n) { WhiteScore = n; }

	// Move and Board Value
	void setHighestPriority(int n) { HighestPriority = n; }
	void setWinCoord(Coord & tmp) { WinPos.y = tmp.y; WinPos.x = tmp.x; }
	void setWinCoord(int y, int x) { WinPos.y = y; WinPos.x = x; }

	// MCTS Acessor
	void setCounterChild(int n) { CounterChild = n; }
	void setCounterVisit(int n) { CounterVisit = n; }
	void InscrementVisit() { CounterVisit++; }
	void setWinScore(double x) { WinScore = x; }
	void AddScore(double x) { WinScore += x; }
	void setAlreadyExpand(bool b) { AlreadyExpand = b; };

};