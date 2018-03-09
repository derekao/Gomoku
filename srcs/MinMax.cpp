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

// static void printBoard(GameManager * Board)
// {
// 	for (int i = 0; i < 361; i ++)
// 	{
// 		std::cout << Board->getBoard()[i] << " ";
// 		if (i % 19 == 18)
// 			std::cout << std::endl;
// 	}
// }

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
	int v = MIN_INFINIT - 1;
	int Alpha = MIN_INFINIT;
	int Beta = MAX_INFINIT;

	PossibleMove possibleMove = PossibleMove(Board);
	std::vector<GameManager *> Childs = possibleMove.getPossibleMove();
	if (Childs.empty())
	{
		std::cerr << "No possible move !" << std::endl;
		exit (0);
	}
	for (size_t i = 0; i < Childs.size(); i++)
	{
		Value = AlphaBeta(Childs[i], 2, Alpha, Beta, false);
		if (Value > v)
		{
			BestMove = Childs[i];
			v = Value;
		}
		Alpha = std::max(Alpha, v);
		if (Beta <= Alpha)
			break;
		Childs[i]->setHeuristicValue(v);
		Childs[i]->setParent(Board);
	}
	Solution = BestMove->getLastMove();
	std::cout << BestMove->getWhiteWin() << " et " << BestMove->getBlackWin() << " et has won " <<  BestMove->getHasWon() << std::endl;
	for (size_t i = 0; i < Childs.size(); i++)
		delete Childs[i];
}

int MinMax::AlphaBeta(GameManager * Node, int depth, int Alpha, int Beta, bool MaximizingPlayer)
{
	int v;

	if (depth == 0 || Node->getBlackWin() || Node->getWhiteWin() || Node->getBlackScore() >= 10 || Node->getWhiteScore() >= 10)
	{
		int iValue = Heuristic::BoardValue(Player1, Player2, Node);
		return iValue;
	}
	if (MaximizingPlayer)
	{
		v = MIN_INFINIT;
		PossibleMove possibleMove = PossibleMove(Node);
		std::vector<GameManager *> Childs = possibleMove.getPossibleMove();
		if (Childs.empty())
		{
			std::cerr << "No possible move !" << std::endl;
			exit (0);
		}
		for (size_t i = 0; i < Childs.size(); i++)
		{
			v = std::max(v, AlphaBeta(Childs[i], depth - 1, Alpha, Beta, false));
			Alpha = std::max(Alpha, v);
			if (Beta <= Alpha)
			{
				for (; i < Childs.size(); i++)
				{
					delete Childs[i];
				}
				break;
			}
			delete Childs[i];

		}
		return v;
	}
	else
	{
		v = MAX_INFINIT;
		PossibleMove possibleMove = PossibleMove(Node);
		std::vector<GameManager *> Childs = possibleMove.getPossibleMove();
		if (Childs.empty())
		{
			std::cerr << "No possible move !" << std::endl;
			exit (0);
		}
		for (size_t i = 0; i < Childs.size(); i++)
		{
			v = std::min(v, AlphaBeta(Childs[i], depth - 1, Alpha, Beta, true));
			Beta = std::min(Beta, v);
			if (Beta <= Alpha)
			{
				for (; i < Childs.size(); i++)
				{
					delete Childs[i];
				}
				break;
			}
			delete Childs[i];
		}
		return v;
	}
}