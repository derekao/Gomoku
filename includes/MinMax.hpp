// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MinMax.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/02/22 14:03:10 by semartin          #+#    #+#             //
//   Updated: 2018/02/22 14:03:11 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>
#include <algorithm> 
#include <vector>
#include <ctime>

#include "Coord.hpp"
#include "GameManager.class.hpp"
#include "Rules.class.hpp"
#include "PossibleMove.class.hpp"
#include "TranspositionTable.class.hpp"

#define ALGO_MTDF 0
#define ALGO_MINIMAX 1
#define ALGO_ALPHABETA 2
#define ALGO_ITERATIVE_ALPHABETA 3
#define ALGO_NEGASCOUT 4
#define ALGO_ITERATIVE_NEGASCOUT 5
#define ALGO_MCTS 6

class MinMax 
{

private:
	int AlgoType;

	std::list<GameManager *> MovePlayer;
	std::list<GameManager *> MoveOpponent;
	GameManager * Board;
	Coord Solution;

	clock_t startTime;
	double Time;
	int ReturnDepth;
	bool TimeOut;
	int ReturnValue;

	int Player1;
	int Player2;

	//ALGO_MTDF
	void IterativeDeepning();
	int MTDF(int FirstGuess, int Depth);
	int MemoryAlphaBeta(GameManager * Node, int Alpha, int Beta, int Depth, bool MaximizingPlayer);
	void DeleteTree(GameManager * Node);

	//ALGO_MINIMAX
	void MiniMaxStart();
	int MiniMax(GameManager * Node, int depth, bool MaximizingPlayer);

	//ALGO_ALPHABETA
	void AlphaBetaStart();
	int AlphaBeta(GameManager * Node, int depth, int Alpha, int Beta, bool MaximizingPlayer);

	//ALGO_ITERATIVE_ALPHABETA
	void IterativeAlphaBetaStart();
	int IterativeAlphaBeta(GameManager * Node, int Alpha, int Beta, int Depth, bool MaximizingPlayer);

	//ALGO_NEGASCOUT
	void NegaScoutStart();
	int NegaScout(GameManager * Node, int depth, int Alpha, int Beta, bool MaximizingPlayer);

	//ALGO_ITERATIVE_NEGASCOUT
	void IterativeNegaScoutStart();
	int IterativeNegaScout(GameManager * Node, int Alpha, int Beta, int Depth);

	//ALGO_MCTS
	void MCTS();
	GameManager * getChildWithMaxScore();
	GameManager * SelectPromisingNode(GameManager * Root);
	GameManager * findBestNodeWithUCT(GameManager * Node);
	double UCTValue(int TotalVisit, double WinScore, int Visit);
	void ExpandNode(GameManager * Node);
	void BackPropagation(GameManager * Node, bool BlackPlayer);
	bool SimulateRandomPlayout(GameManager * Node);

	MinMax();

public:
	MinMax(GameManager * src, int _AlgoType = 6);
	~MinMax();

	int getDepth() { return ReturnDepth; }
	Coord & getSolution() { return Solution ;}
	double getTime() { return Time; }
	int getValue() { return ReturnValue; }

	static int MaxDepth;
	static double MaxTimer;

};