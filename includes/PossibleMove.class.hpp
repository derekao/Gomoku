// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PossibleMove.class.hpp                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/03/01 16:35:08 by semartin          #+#    #+#             //
//   Updated: 2018/03/01 16:35:08 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //
 
#pragma once

#include <iostream>
#include <vector>
#include "GameManager.class.hpp"
#include "Rules.class.hpp"
#include "Heuristic.class.hpp"

class PossibleMove
{

private:
	PossibleMove(); //Forbiden Constructor

	GameManager * Board;
	std::vector<GameManager *> tabMove;

	int HighestHeuristicValue;
	int LowestHeuristicValue;

	void Compute();
	bool StoneNearby(int y, int x);

public:
	PossibleMove(GameManager *);
	~PossibleMove() {};

	static void PlayStone(int y, int x, GameManager * Board);
	static bool CheckStoneEaten(int y, int x, GameManager * Board);
	static void CheckBoardState(int Height, int Width, bool SomethingEaten, GameManager * Board);
	static bool DeadStone(int y1, int x1, int y2, int x2, int * iScire, int Player, GameManager * Board);
	static void FindOneMove(GameManager * Node, std::vector<GameManager *> & Childs);

	enum Type { Empty, Black, White, Eat, DoubleTree, Forbidden };

	std::vector<GameManager *> & getPossibleMove() { return tabMove; };

};