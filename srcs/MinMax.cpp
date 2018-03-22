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
// 		std::cout << (int)Board->getBoard()[i] << " ";
// 		if (i % 19 == 18)
// 			std::cout << std::endl;
// 	}
// }

MinMax::~MinMax()
{
	// std::cout << "Destructor start timer  = " << (clock() - startTime) / static_cast<int>(CLOCKS_PER_SEC) << std::endl;
	for (size_t i = 0; i < Board->getChilds().size(); i++)
	{
		DeleteTree(Board->getChilds()[i]);
	}
	// std::cout << "Destructor end timer  = " << (clock() - startTime) / static_cast<int>(CLOCKS_PER_SEC) << std::endl;
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
	TimeOut = false;

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
	if (Board->getBlackWin() || Board->getWhiteWin() || Board->getBlackScore() >= 10 || Board->getWhiteScore() >= 10)
	{
		return;
	}
	int FirstGuess = 0;
	for (int d = 1; d < MAX_DEPTH; d++)
	{
		FirstGuess = MTDF(FirstGuess, d);
		if (TimeOut)
			break;
		// for (std::map<std::string, BoardMemory *>::iterator it = TranspositionTable::TranspoTable.begin(); it != TranspositionTable::TranspoTable.end(); ++it)
 		//  	delete it->second;
		TranspositionTable::TranspoTable.clear();
		ReturnDepth = d;
		int BestValue = MIN_INFINIT - 1;
		GameManager *BestMove = NULL;;
		for (size_t i = 0; i < Board->getChilds().size(); i++)
		{
			if (Board->getChilds()[i]->getHeuristicValue() > BestValue)
			{
				BestValue = Board->getChilds()[i]->getHeuristicValue();
				BestMove = Board->getChilds()[i];
			}
		}
		if (BestValue != FirstGuess)
		{
			std::cout << "FirstGuess = " <<  FirstGuess << " et BestValue =" << BestValue << std::endl;
		}
		Solution = BestMove->getLastMove();
		ReturnValue = BestValue;
	}
	// for (std::map<std::string, BoardMemory *>::iterator it = TranspositionTable::TranspoTable.begin(); it != TranspositionTable::TranspoTable.end(); ++it)
 	// 	delete it->second;
	TranspositionTable::TranspoTable.clear();
	std::cout << "_____________________________________________________________LAST LOOP " << ReturnDepth << " timer  = " << Time << " and Value = " << ReturnValue << std::endl;

}

int MinMax::MTDF(int FirstGuess, int Depth)
{
	int Value = FirstGuess;
	int UpperBound = MAX_INFINIT;
	int LowerBound = MIN_INFINIT;
	int Beta;
	int i = 0;

	while (LowerBound < UpperBound)
	{
		i++;
		if (Value == LowerBound)
		{
			Beta = Value + 1;
		}
		else
		{
			Beta = Value;
		}
		Value = MemoryAlphaBeta(Board, Beta - 1, Beta, Depth, true);
		if (TimeOut)
			return 0;
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
	if (TimeOut)
		return 0;
	int timer = (clock() - startTime) / static_cast<int>(CLOCKS_PER_SEC);
	if (timer > TIMER_MAX)
	{
		Time = timer;
		TimeOut = true;
		return 0;
	}
	int Value;
	BoardMemory RetrieveNode;
	if ((RetrieveNode = TranspositionTable::Retrieve(Node)))
	{
		if (RetrieveNode.LowerBound >= Beta)
			return RetrieveNode.LowerBound;
		if (RetrieveNode.UpperBound <= Alpha)
			return RetrieveNode.UpperBound;
		Alpha = std::max(Alpha, RetrieveNode.LowerBound);
		Beta = std::min(Beta, RetrieveNode.UpperBound);
	}
	if (Depth == 0 || Node->getBlackWin() || Node->getWhiteWin() || Node->getBlackScore() >= 10 || Node->getWhiteScore() >= 10)
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
		for (size_t i = 0; Value < Beta &&  i < Node->getChilds().size(); i++)
		{
			Value = std::max(Value, MemoryAlphaBeta(Node->getChilds()[i], SavedAlpha, Beta, Depth - 1, false));
			SavedAlpha = std::max(SavedAlpha, Value);
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
			int tmp = MemoryAlphaBeta(Node->getChilds()[i], Alpha, SavedBeta, Depth - 1, true);
			Value = std::min(Value, tmp);
			SavedBeta = std::min(SavedBeta, Value);
		}
	}
	//Fail low result implies an upper bound 
	BoardMemory tmp;
	tmp.Board = Node;
	if (Value <= Alpha)
	{
		tmp.UpperBound = Value;
		TranspositionTable::Store(tmp);
	}
	// Found an accurate minimax value - will not occur if called with zero window 
	if (Value > Alpha && Value < Beta)
	{
		tmp.LowerBound = Value;
		tmp.UpperBound = Value;
		TranspositionTable::Store(tmp);
		//STORE UpperBound AND LowerBound
	}
	//Fail high result implies a lower bound
	if (Value >= Beta)
	{
		tmp.LowerBound = Value;
		TranspositionTable::Store(tmp);
		//SOTRE Node->LowerBound
	}
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