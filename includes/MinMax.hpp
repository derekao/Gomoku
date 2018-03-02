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

#include "Coord.hpp"
#include "GameManager.class.hpp"
#include "Rules.class.hpp"
#include "PossibleMove.class.hpp"

class MinMax 
{

private:
	GameManager * Board;
	Coord Solution;

	int Player1;
	int Player2;

	void Compute();
	int AlphaBeta(GameManager * Node, int depth, bool MaximizingPlayer);

	MinMax();

public:
	MinMax(GameManager * src);
	~MinMax() {};

	Coord & getSolution() { return Solution ;};

};