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

static void printBoard(GameManager * Board)
{
	for (int i = 0; i < 361; i ++)
	{
		std::cout << Board->getBoard()[i] << " ";
		if (i % 19 == 18)
			std::cout << std::endl;
	}
}

MinMax::MinMax(GameManager * src) : Board(src), Solution(Coord(-1,-1))
{
	if (Board->getbPlayerOneTurn())
	{
		Player1 = STONE_BLACK;
		Player2 = STONE_WHITE;
	}
	else
	{
		Player1 = STONE_WHITE;
		Player2 = STONE_BLACK;
	}
	Compute();
}

void MinMax::Compute()
{
	GameManager *BestMove;
	int Value;
	int v = INT_MIN;

	PossibleMove possibleMove = PossibleMove(Board);
	std::vector<GameManager *> Childs = possibleMove.getPossibleMove();
	for (size_t i = 0; i < Childs.size(); i++)
	{
		std::cout << "test3 " <<  Childs.size() << std::endl;
		Value = AlphaBeta(Childs[i], 2, false);
		if (Value > v)
		{
			BestMove = Childs[i];
			v = Value;
		}
//		Alpha = std::max(Alpha, v);
//		if (Beta <= Alpha)
//			break;
		Childs[i]->setHeuristicValue(v);
		Childs[i]->setParent(Board);
	}
	Solution = BestMove->getLastMove();
	for (size_t i = 0; i < Childs.size(); i++)
		delete Childs[i];
}

int MinMax::AlphaBeta(GameManager * Node, int depth, bool MaximizingPlayer)
{
	int v;

	if (depth == 0 || Node->getBlackWin() || Node->getWhiteWin())
	{
		int iValue = Heuristic::BoardValueByAlignment(Player1, Player2, Node);
		int bValue = Heuristic::BoardValueByAlignment(Player2, Player1, Node);
		printBoard(Node);
		std::cout << "Heuristic = " << iValue << " - " << bValue << " = " << iValue - bValue << std::endl;
		return iValue - bValue;
	}
	if (MaximizingPlayer)
	{
		v = INT_MIN;
		PossibleMove possibleMove = PossibleMove(Node);
		std::vector<GameManager *> Childs = possibleMove.getPossibleMove();
		for (size_t i = 0; i < Childs.size(); i++)
		{
			v = std::max(v, AlphaBeta(Childs[i], depth - 1, false));
//			Alpha = std::max(Alpha, v);
//			if (Beta <= Alpha)
//				break;
//			Childs[i]->setHeuristicValue(v);
//			Childs[i]->setParent(Board);
			delete Childs[i];
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
			v = std::min(v, AlphaBeta(Childs[i], depth - 1, true));
//			Beta = std::min(Beta, v);
//			if (Beta >= Alpha)
//				break;
//			Childs[i]->setHeuristicValue(v);
//			Childs[i]->setParent(Board);
			delete Childs[i];
		}
		return v;
	}
}