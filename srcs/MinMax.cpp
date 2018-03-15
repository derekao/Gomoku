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

MinMax::~MinMax()
{
	for (size_t i = 0; i < Board->getChilds().size(); i++)
	{
		DeleteTree(Board->getChilds()[i]);
	}
	std::cout << " timer  = " << (clock() - startTime) / CLOCKS_PER_SEC << std::endl;
}

void MinMax::DeleteTree(GameManager * Node)
{
	for (size_t i = 0; i < Node->getChilds().size(); i++)
	{
		DeleteTree(Node->getChilds()[i]);
	}
	delete Node;
}

MinMax::MinMax(GameManager * src) : Board(src), Solution(Coord(-1,-1))
{
	startTime = clock(); 

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
	IterativeDeepning();
}

void MinMax::IterativeDeepning()
{
	int FirstGuess = 0;
	for (int Depth = 1; Depth < MAX_DEPTH; Depth++)
	{
		std::cout << (clock() - startTime) / CLOCKS_PER_SEC  << std::endl;
		FirstGuess = MTDF(FirstGuess, Depth);
		if ((clock() - startTime) / CLOCKS_PER_SEC >= TIMER_MAX)
			break;
		std::cout << FirstGuess << " et " << Depth << " timer  = " << (clock() - startTime) / CLOCKS_PER_SEC << std::endl;
	}

	int BestValue = MIN_INFINIT;
	GameManager *BestMove = NULL;;
	for (size_t i = 0; i < Board->getChilds().size(); i++)
	{
		if (Board->getChilds()[i]->getHeuristicValue() > BestValue)
		{
			BestValue = Board->getChilds()[i]->getHeuristicValue();
			BestMove = Board->getChilds()[i];
		}
	}
	Solution = BestMove->getLastMove();
}

int MinMax::MTDF(int FirstGuess, int Depth)
{
	int Value = FirstGuess;
	int UpperBound = MAX_INFINIT;
	int LowerBound = MIN_INFINIT;
	int Beta;

	while (LowerBound < UpperBound)
	{
		if (Value == LowerBound)
		{
			Beta = Value + 1;
		}
		else
		{
			Beta = Value;
		}
		Value = MemoryAlphaBeta(Board, Beta - 1, Beta, Depth, true);
		if (Value < Beta)
		{
			UpperBound = Value;
		}
		else
		{
			LowerBound = Value;
		}
	}
	return Value;
}

int MinMax::MemoryAlphaBeta(GameManager * Node, int Alpha, int Beta, int Depth, bool MaximizingPlayer)
{
	int Value;
	// if retrieve(n) == OK then /* Transposition table lookup */
	// if n.lowerbound >= beta then return n.lowerbound;
	// if n.upperbound <= alpha then return n.upperbound;
	// alpha := max(alpha, n.lowerbound);
	// beta := min(beta, n.upperbound);
	if (Depth == 0)
	{
		Heuristic init = Heuristic(Player1, Player2, Node);
 		Node->setHeuristicValue(init.BoardValue());
		Value = init.BoardValue();
	}
	else if (MaximizingPlayer)
	{
		Value = MIN_INFINIT;
		int SavedAlpha = Alpha;
		if (Node->getChilds().empty())
		{
			PossibleMove possibleMove = PossibleMove(Node);
			if (Node->getChilds().empty())
				PossibleMove::FindOneMove(Node);
		}
		for (size_t i = 0; Value < Beta && i < Node->getChilds().size(); i++)
		{
			Value = std::max(Value, MemoryAlphaBeta(Node->getChilds()[i], SavedAlpha, Beta, Depth - 1, false));
			SavedAlpha = std::max(Alpha, Value);
		}
	}
	else
	{
		Value = MAX_INFINIT;
		int SavedBeta = Beta;
		if (Node->getChilds().empty())
		{
			PossibleMove possibleMove = PossibleMove(Node);
			if (Node->getChilds().empty())
				PossibleMove::FindOneMove(Node);
		}
		for (size_t i = 0; Value > Alpha && i < Node->getChilds().size(); i++)
		{
			Value = std::min(Value, MemoryAlphaBeta(Node->getChilds()[i], Alpha, SavedBeta, Depth - 1, true));
			SavedBeta = std::min(Beta, Value);
		}
	}
	// //Fail low result implies an upper bound 
	// if (Value <= Alpha)
	// {
	// 	Node->setUpperBoud(Value);
	// 	//STORE Node->UpperBoud;
	// }
	// // Found an accurate minimax value - will not occur if called with zero window 
	// if (Value > Alpha && Value < Beta)
	// {
	// 	Node->setLowerBound(Value);
	// 	Node->setUpperBound(Value);
	// 	//STORE UpperBound AND LowerBound
	// }
	// //Fail high result implies a lower bound
	// if (Value >= Beta)
	// {
	// 	Node->setLowerBound(Value);
	// 	//SOTRE Node->LowerBound
	// 	}
	Node->setHeuristicValue(Value);
	return Value;
}

// void MinMax::Compute()
// {
// 	GameManager *BestMove;
// 	int Value;
// 	int v = MIN_INFINIT - 1;
// 	int Alpha = MIN_INFINIT;
// 	int Beta = MAX_INFINIT;

// 	PossibleMove possibleMove = PossibleMove(Board);
// 	std::vector<GameManager *> Childs = possibleMove.getPossibleMove();
// 	if (Childs.empty())
// 	{
// 		std::cout << "child empty" << std::endl;
// 		PossibleMove::FindOneMove(Board, Childs);
// 	}
// 	for (size_t i = 0; i < Childs.size(); i++)
// 	{
// 		Value = AlphaBeta(Childs[i], 6, Alpha, Beta, false);
// 		if (Value > v)
// 		{
// 			BestMove = Childs[i];
// 			v = Value;
// 		}
// 		Alpha = std::max(Alpha, v);
// 		if (Beta <= Alpha)
// 			break;
// 		Childs[i]->setHeuristicValue(v);
// 		Childs[i]->setParent(Board);
// 	}
// 	Solution = BestMove->getLastMove();
// 	std::cout << BestMove->getWhiteWin() << " et " << BestMove->getBlackWin() << " et has won " <<  BestMove->getHasWon() << std::endl;
// 	for (size_t i = 0; i < Childs.size(); i++)
// 		delete Childs[i];
// }

// int MinMax::AlphaBeta(GameManager * Node, int depth, int Alpha, int Beta, bool MaximizingPlayer)
// {
// 	int v;

// 	if (depth == 0 || Node->getBlackWin() || Node->getWhiteWin() || Node->getBlackScore() >= 10 || Node->getWhiteScore() >= 10)
// 	{
// 		Heuristic init = Heuristic(Player1, Player2, Node);
// 		int iValue = init.BoardValue();
// 		return iValue;
// 	}
// 	if (MaximizingPlayer)
// 	{
// 		v = MIN_INFINIT;
// 		PossibleMove possibleMove = PossibleMove(Node);
// 		std::vector<GameManager *> Childs = possibleMove.getPossibleMove();
// 		if (Childs.empty())
// 		{
// 			PossibleMove::FindOneMove(Node);
// 		}
// 		for (size_t i = 0; i < Childs.size(); i++)
// 		{
// 			v = std::max(v, AlphaBeta(Childs[i], depth - 1, Alpha, Beta, false));
// 			Alpha = std::max(Alpha, v);
// 			if (Beta <= Alpha)
// 			{
// 				for (; i < Childs.size(); i++)
// 				{
// 					delete Childs[i];
// 				}
// 				break;
// 			}
// 			delete Childs[i];

// 		}
// 		return v;
// 	}
// 	else
// 	{
// 		v = MAX_INFINIT;
// 		PossibleMove possibleMove = PossibleMove(Node);
// 		std::vector<GameManager *> Childs = possibleMove.getPossibleMove();
// 		if (Childs.empty())
// 		{
// 			PossibleMove::FindOneMove(Node);
// 		}
// 		for (size_t i = 0; i < Childs.size(); i++)
// 		{
// 			v = std::min(v, AlphaBeta(Childs[i], depth - 1, Alpha, Beta, true));
// 			Beta = std::min(Beta, v);
// 			if (Beta <= Alpha)
// 			{
// 				for (; i < Childs.size(); i++)
// 				{
// 					delete Childs[i];
// 				}
// 				break;
// 			}
// 			delete Childs[i];
// 		}
// 		return v;
// 	}
// }