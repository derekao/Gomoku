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
#include <vector>
#include "Coord.hpp"

#define STONE_EMPTY 0
#define STONE_BLACK 1
#define STONE_WHITE 2
#define STONE_WHITEFORBIDDEN 4
#define STONE_BLACKFORBIDDEN 8
#define STONE_WHITEDOUBLETREE 16
#define STONE_BLACKDOUBLETREE 32

#define BOARD_HEIGHT 19
#define BOARD_WIDTH 19

#define INT_MAX 2147483647
#define INT_MIN -2147483648

class MinMax 
{

private:
	std::vector< std::vector<char> > Board;
	Coord Solution;

	void Compute();
	int AlphaBeta();

	MinMax();

public:
	MinMax(std::vector< std::vector<char>> & Board);
	~MinMax() {};

};