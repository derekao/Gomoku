// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MinMax.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/02/22 14:03:00 by semartin          #+#    #+#             //
//   Updated: 2018/02/22 14:03:01 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "MinMax.hpp"

MinMax::MinMax(std::vector <std::vector<int> > & cpyBoard) : Board(cpyBoard)
{
	Solution = Coord(0,0);
	Compute();
}

void MinMax::Compute()
{

}

int MinMax::AlphaBeta(NODE, int depth, int Alpha, int Beta, bool MaximizingPlayer)
{
	int v;

	if (depth == 0 || NODE == TERMINAL_NODE)
	{
		return HEURISTIC VALUE OF NODE;
	}
	if (MaximizingPlayer)
	{
		v = INT_MIN;
		for each CHILD OF NODE
		{
			v = max(v, AlphaBeta(CHILD, depth - 1, Alpha, Beta, false))
			Alpha = max(Alpha, v);
			if (Beta <= Alpha)
				break;
			return v;
		}
	}
	else
	{
		v = INT_MAX
		for each CHILD OF NODE
		{
			v = min(v, AlphaBeta(CHILD, depth - 1, Alpha, Beta, true))
			Beta = min(Beta, v)
			if (Beta >= Alpha)
				break;
			return v;
		}
	}
}