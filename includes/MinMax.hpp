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

#include "Board.class.hpp"

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