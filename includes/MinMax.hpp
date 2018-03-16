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

#define TIMER_MAX 0.5f
#define MAX_DEPTH 60

class MinMax 
{

private:
	std::list<GameManager *> MovePlayer;
	std::list<GameManager *> MoveOpponent;
	GameManager * Board;
	Coord Solution;

	clock_t startTime;
	double Time;
	int Depth;

	int Player1;
	int Player2;

	void Compute();
	void IterativeDeepning();
	int MTDF(int FirstGuess, int Depth);
	int MemoryAlphaBeta(GameManager * Node, int Alpha, int Beta, int Depth, bool MaximizingPlayer);
	void DeleteTree(GameManager * Node);

//	int AlphaBeta(GameManager * Node, int depth, int Alpha, int Beta, bool MaximizingPlayer);

	MinMax();

public:
	MinMax(GameManager * src);
	~MinMax();

	int getDepth() { return Depth; };
	Coord & getSolution() { return Solution ;};
	double getTime() { return Time; };

};