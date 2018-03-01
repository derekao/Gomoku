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

MinMax::MinMax(GameManager * src) : Board(src), Solution(Coord(-1,-1))
{
	Compute();
}

void MinMax::Compute()
{
	
}

int MinMax::AlphaBeta(GameManager * Node, int depth, int Alpha, int Beta, bool MaximizingPlayer)
{
	int v;

	if (depth == 0 || Node->getHasWon())
	{
		return Node->getHeuristicValue();
	}
	if (MaximizingPlayer)
	{
		v = INT_MIN;
		PossibleMove possibleMove = PossibleMove(Node);
		std::vector<GameManager *> Childs = possibleMove.getPossibleMove();
		for (size_t i = 0; i < Childs.size(); i++)
		{
			v = std::max(v, AlphaBeta(Childs[i], depth - 1, Alpha, Beta, false));
			Alpha = std::max(Alpha, v);
			if (Beta <= Alpha)
				break;
		}
		return v;
	}
	else
	{
		v = INT_MAX;
		PossibleMove possibleMove = PossibleMove(Node);
		std::vector<GameManager *> Childs = possibleMove.getPossibleMove();
		for (size_t i = 0; i < Childs.size(); i++)
		{
			v = std::min(v, AlphaBeta(Childs[i], depth - 1, Alpha, Beta, true));
			Beta = std::min(Beta, v);
			if (Beta >= Alpha)
				break;
		}
		return v;
	}
}