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

int MinMax::MaxDepth;
double MinMax::MaxTimer;

MinMax::~MinMax()
{
	if (AlgoType == ALGO_MTDF || AlgoType == ALGO_ITERATIVE_ALPHABETA || AlgoType == ALGO_MCTS)
	{
		// std::cout << "Destructor start timer  = " << (clock() - startTime) / static_cast<int>(CLOCKS_PER_SEC) << std::endl;
		for (size_t i = 0; i < Board->getChilds().size(); i++)
		{
			DeleteTree(Board->getChilds()[i]);
		}
		// std::cout << "Destructor end timer  = " << (clock() - startTime) / static_cast<int>(CLOCKS_PER_SEC) << std::endl;
	}
}

void MinMax::DeleteTree(GameManager * Node)
{
	for (size_t i = 0; i < Node->getChilds().size(); i++)
	{
		DeleteTree(Node->getChilds()[i]);
	}
	delete Node;
}

MinMax::MinMax(GameManager * src, int _AlgoType) : AlgoType(_AlgoType), Board(src), Solution(Coord(-1,-1))
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
	if (AlgoType == ALGO_MTDF)
		IterativeDeepning();
	else if (AlgoType == ALGO_MINIMAX)
		MiniMaxStart();
	else if (AlgoType == ALGO_ALPHABETA)
		AlphaBetaStart();
	else if (AlgoType == ALGO_ITERATIVE_ALPHABETA)
		IterativeAlphaBetaStart();
	else if (AlgoType == ALGO_MCTS)
		MCTS();

///////////////////////////////
/////////ALGO_MTDF//////////
///////////////////////////////
void MinMax::IterativeDeepning()
{
	if (Board->getBlackWin() || Board->getWhiteWin() || Board->getBlackScore() >= 10 || Board->getWhiteScore() >= 10)
	{
		return;
	}
	ReturnDepth = 0;
	int FirstGuess = 0;
	for (int d = 1; d < MinMax::MaxDepth; d++)
	{
		FirstGuess = MTDF(FirstGuess, d);
		if (TimeOut)
			break;
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
		Solution = BestMove->getLastMove();
		ReturnValue = BestValue;
	}
	TranspositionTable::TranspoTable.clear();
//	std::cout << "_____________________________________________________________LAST LOOP " << ReturnDepth << " timer  = " << Time << " and Value = " << ReturnValue << std::endl;

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
	double timer = (clock() - startTime) / static_cast<double>(CLOCKS_PER_SEC);
	if (timer > MinMax::MaxTimer)
	{
		Time = timer;
		TimeOut = true;
		return 0;
	}
	int Value;
	GameManager *RetrieveNode;
	//Retrive in the Transpo Table
	if ((RetrieveNode = TranspositionTable::Retrieve(Node)))
	{
		if (RetrieveNode->getLowerBound() >= Beta)
		{
			Node->setHeuristicValue(RetrieveNode->getLowerBound());
			return RetrieveNode->getLowerBound();
		}
		if (RetrieveNode->getUpperBound() <= Alpha)
		{
			Node->setHeuristicValue(RetrieveNode->getUpperBound());
			return RetrieveNode->getUpperBound();
		}
		Alpha = std::max(Alpha, RetrieveNode->getLowerBound());
		Beta = std::min(Beta, RetrieveNode->getUpperBound());
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
	if (Node->getBoundDepth() != ReturnDepth + 1)
	{
		Node->setBoundDepth(ReturnDepth + 1);
		Node->setUpperBound(MAX_INFINIT);
		Node->setLowerBound(MIN_INFINIT);
	}
	// Store in the transpo Table
	if (Value <= Alpha)
	{
		Node->setUpperBound(Value);
		TranspositionTable::Store(Node);
	}
	if (Value > Alpha && Value < Beta)
	{
		Node->setLowerBound(Value);
		Node->setUpperBound(Value);
		TranspositionTable::Store(Node);
	}
	if (Value >= Beta)
	{
		Node->setLowerBound(Value);
		TranspositionTable::Store(Node);
	}
	Node->setHeuristicValue(Value);
	return Value;
}

///////////////////////////////
/////////ALGO_MINIMAX//////////
///////////////////////////////
void MinMax::MiniMaxStart()
{
	GameManager *BestMove;
	int Value;
	int v = MIN_INFINIT - 1;

	PossibleMove possibleMove = PossibleMove(Board);
	if (Board->getChilds().empty())
		PossibleMove::FindOneMove(Board);
	std::vector<GameManager *> Childs = Board->getChilds();

	for (size_t i = 0; i < Childs.size(); i++)
	{
		Value = MiniMax(Childs[i], MinMax::MaxDepth - 1, false);
		if (Value > v)
		{
			BestMove = Childs[i];
			v = Value;
		}
		Childs[i]->setHeuristicValue(v);
		Childs[i]->setParent(Board);
	}
	Solution = BestMove->getLastMove();
	for (size_t i = 0; i < Childs.size(); i++)
		delete Childs[i];
	Time = (clock() - startTime) / static_cast<double>(CLOCKS_PER_SEC);
	ReturnDepth = MinMax::MaxDepth;
	ReturnValue = Value;
}

int MinMax::MiniMax(GameManager * Node, int depth, bool MaximizingPlayer)
{
	int v;

	if (depth == 0 || Node->getBlackWin() || Node->getWhiteWin() || Node->getBlackScore() >= 10 || Node->getWhiteScore() >= 10)
	{
		Heuristic init = Heuristic(Player1, Player2, Node);
		int iValue = init.BoardValue();
		return iValue;
	}
	if (MaximizingPlayer)
	{
		v = MIN_INFINIT;
		PossibleMove possibleMove = PossibleMove(Node);
		if (Node->getChilds().empty())
			PossibleMove::FindOneMove(Node);
		std::vector<GameManager *> Childs = Node->getChilds();

		for (size_t i = 0; i < Childs.size(); i++)
		{
			v = std::max(v, MiniMax(Childs[i], depth - 1,false));
			delete Childs[i];
		}
		return v;
	}
	else
	{
		v = MAX_INFINIT;
		PossibleMove possibleMove = PossibleMove(Node);
		if (Node->getChilds().empty())
			PossibleMove::FindOneMove(Node);
		std::vector<GameManager *> Childs = Node->getChilds();

		for (size_t i = 0; i < Childs.size(); i++)
		{
			v = std::min(v, MiniMax(Childs[i], depth - 1, true));
			delete Childs[i];
		}
		return v;
	}
}

///////////////////////////////
/////////ALGO_ALPHABETA////////
///////////////////////////////
void MinMax::AlphaBetaStart()
{
	GameManager *BestMove;
	int Value;
	int v = MIN_INFINIT - 1;
	int Alpha = MIN_INFINIT;
	int Beta = MAX_INFINIT;

	PossibleMove possibleMove = PossibleMove(Board);
	if (Board->getChilds().empty())
		PossibleMove::FindOneMove(Board);
	std::vector<GameManager *> Childs = Board->getChilds();

	for (size_t i = 0; i < Childs.size(); i++)
	{
		Value = AlphaBeta(Childs[i], MinMax::MaxDepth - 1, Alpha, Beta, false);
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
	for (size_t i = 0; i < Childs.size(); i++)
		delete Childs[i];
	Time = (clock() - startTime) / static_cast<double>(CLOCKS_PER_SEC);
	ReturnDepth = MinMax::MaxDepth;
	ReturnValue = Value;
}

int MinMax::AlphaBeta(GameManager * Node, int depth, int Alpha, int Beta, bool MaximizingPlayer)
{
	int v;

	if (depth == 0 || Node->getBlackWin() || Node->getWhiteWin() || Node->getBlackScore() >= 10 || Node->getWhiteScore() >= 10)
	{
		Heuristic init = Heuristic(Player1, Player2, Node);
		int iValue = init.BoardValue();
		return iValue;
	}
	if (MaximizingPlayer)
	{
		v = MIN_INFINIT;
		PossibleMove possibleMove = PossibleMove(Node);
		if (Node->getChilds().empty())
			PossibleMove::FindOneMove(Node);
		std::vector<GameManager *> Childs = Node->getChilds();

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
		if (Node->getChilds().empty())
			PossibleMove::FindOneMove(Node);
		std::vector<GameManager *> Childs = Node->getChilds();

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

/////////////////////////////////////////
/////////ALGO_ITERATIVE_ALPHABETA////////
/////////////////////////////////////////
void MinMax::IterativeAlphaBetaStart()
{
	if (Board->getBlackWin() || Board->getWhiteWin() || Board->getBlackScore() >= 10 || Board->getWhiteScore() >= 10)
	{
		return;
	}
	ReturnDepth = 0;
	int FirstGuess = 0;
	for (int d = 1; d < MinMax::MaxDepth; d++)
	{
		FirstGuess = IterativeAlphaBeta(Board, MIN_INFINIT, MAX_INFINIT, d, true);
		if (TimeOut)
			break;
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
		Solution = BestMove->getLastMove();
		ReturnValue = BestValue;
	}
	//	std::cout << "_____________________________________________________________LAST LOOP " << ReturnDepth << " timer  = " << Time << " and Value = " << ReturnValue << std::endl;

}

int MinMax::IterativeAlphaBeta(GameManager * Node, int Alpha, int Beta, int Depth, bool MaximizingPlayer)
{
	if (TimeOut)
		return 0;
	double timer = (clock() - startTime) / static_cast<double>(CLOCKS_PER_SEC);
	if (timer > MinMax::MaxTimer)
	{
		Time = timer;
		TimeOut = true;
		return 0;
	}
	int Value;
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
			Value = std::max(Value, IterativeAlphaBeta(Node->getChilds()[i], SavedAlpha, Beta, Depth - 1, false));
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
			int tmp = IterativeAlphaBeta(Node->getChilds()[i], Alpha, SavedBeta, Depth - 1, true);
			Value = std::min(Value, tmp);
			SavedBeta = std::min(SavedBeta, Value);
		}
	} 
	Node->setHeuristicValue(Value);
	return Value;
}

///////////////////////////////
/////////ALGO_MCTS/////////////
///////////////////////////////
void MinMax::MCTS()
{
	double timer = (clock() - startTime) / static_cast<double>(CLOCKS_PER_SEC);
	while (timer < MinMax::MaxTimer)
	{
		GameManager * PromisingNode = SelectPromisingNode(Board);;
		if (!(Board->getBlackWin() || Board->getWhiteWin() || Board->getBlackScore() >= 10 || Board->getWhiteScore() >= 10))
		{
			ExpandNode(PromisingNode);
		}
		GameManager * NodeToExplore;
		if (PromisingNode->getPotentialMove().empty())
		{
			PossibleMove::FindOneMove(PromisingNode);
			NodeToExplore = PromisingNode->getChilds().back();
		}
		PossibleMove possibleMove = PossibleMove(PromisingNode, true);
		NodeToExplore = possibleMove.SetOneChild();
		if (NodeToExplore == NULL)
		{
			int i = std::rand() % PromisingNode->getChilds().size();
			NodeToExplore = PromisingNode->getChilds()[i];
		}
		bool BlackWin = SimulateRandomPlayout(NodeToExplore);
		BackPropagation(NodeToExplore, BlackWin);
		timer = (clock() - startTime) / static_cast<double>(CLOCKS_PER_SEC);
	}
	Time = timer;
	GameManager *BestMove = getChildWithMaxScore();
	Solution = BestMove->getLastMove();
	printBoard(BestMove);
	std::cout << "NUM CHILD = " << BestMove->getChilds().size() << " et " <<  BestMove << std::endl;
	std::cout << " y = " << BestMove->getChilds()[0]->getLastMove().y << " et x = " << BestMove->getChilds()[0]->getLastMove().x << std::endl;
}

GameManager * MinMax::getChildWithMaxScore()
{
	int Value = 0;
	GameManager *tmp;

	for (size_t i = 0; i < Board->getChilds().size(); i++)
	{
		std::cout << Board->getChilds()[i]->getCounterVisit() << " And number of win = " <<  Board->getChilds()[i]->getWinScore() << std::endl;
		if (Board->getChilds()[i]->getCounterVisit() > Value)
		{
			Value = Board->getChilds()[i]->getCounterVisit();
			tmp = Board->getChilds()[i];
		}
//		std::cout << "Y-----------------------" << std::endl;
		GameManager * tmpBis;
		for (size_t j = 0;  j < Board->getChilds()[i]->getChilds().size(); j++)
		{
//			std::cout << Board->getChilds()[i]->getChilds()[j]->getCounterVisit() << " And number of win = " <<  Board->getChilds()[i]->getChilds()[j]->getWinScore() << std::endl;
			if (Board->getChilds()[i]->getChilds()[j]->getCounterVisit() > Value)
			{
				Value = Board->getChilds()[i]->getChilds()[j]->getCounterVisit();
				tmpBis = Board->getChilds()[i]->getChilds()[j];
			}
		}
//		std::cout << "X-----------------------" << std::endl;
	}

	return tmp;
}

GameManager * MinMax::SelectPromisingNode(GameManager * Root)
{
	while (Root->getChilds().size() != 0 && Root->getAlreadyExpand() == true)
	{
		Root = findBestNodeWithUCT(Root);
	}
//	std::cout << " ADRESSE = " << Root << std::endl;
	return Root;
}

GameManager * MinMax::findBestNodeWithUCT(GameManager * Node)
{
	int ParentVisit = Node->getCounterVisit();
	double Value = -1;
	double tmp;
	GameManager * ReturnNode = NULL;
	for (size_t i = 0; i < Node->getChilds().size(); i++)
	{
		tmp = UCTValue(ParentVisit, Node->getChilds()[i]->getWinScore(), Node->getChilds()[i]->getCounterVisit());
		if (tmp > Value)
		{
			ReturnNode = Node->getChilds()[i];
			Value = tmp;
		}
	}
//	std::cout << "Return Value" << Value << std::endl;
	if (ReturnNode == NULL)
	{
		std::cerr << "Wierd UTC" << std::endl;
		exit(0);
	}
	return ReturnNode;
}

double MinMax::UCTValue(int TotalVisit, double WinScore, int Visit)
{
	if (Visit == 0)
		return INT_MAX;
	return (WinScore / static_cast<double>(Visit)) + 1.41 * sqrt(log(TotalVisit) / static_cast<double>(Visit));
}

void MinMax::ExpandNode(GameManager * Node)
{
	Node->setAlreadyExpand(true);
	if (Node->getPotentialMove().empty())
	{
		PossibleMove::FindOneMove(Node);
	}
	PossibleMove possibleMove = PossibleMove(Node, true);
	GameManager * tmp = possibleMove.SetOneChild();
	if (!tmp)
//		std::cout << "NULL" << std::endl;
	while (tmp)
	{
		tmp = possibleMove.SetOneChild();
	}
//	std::cout << "NUM CHILD = " << Node->getChilds().size() << " et " <<  Node << std::endl;
//	std::cout << " y = " << Node->getLastMove().y << " et x = " << Node->getLastMove().x << std::endl;
}

void MinMax::BackPropagation(GameManager * Node, bool BlackPlayer)
{
	GameManager * tmpNode = Node;
//	std::cout << "===================" << std::endl;
	while (tmpNode != NULL)
	{
		tmpNode->InscrementVisit();
//		std::cout << "NUM CHILD increment = " << tmpNode->getChilds().size() << " et nb visit =  " << tmpNode->getCounterVisit() << std::endl;
		if (tmpNode->getbPlayerOneTurn() == BlackPlayer)
		{
			tmpNode->AddScore(1); // TODO
		}
		tmpNode = tmpNode->getParent();
	}
//	std::cout << "---------------------------" << std::endl;
}

bool MinMax::SimulateRandomPlayout(GameManager * Node)
{
	GameManager * tmpNode = Node;

	while (!((tmpNode->getBlackWin() || tmpNode->getWhiteWin() || tmpNode->getBlackScore() >= 10 || tmpNode->getWhiteScore() >= 10)))
	{
		if (tmpNode->getPotentialMove().empty())
			PossibleMove::FindOneMove(tmpNode);
		PossibleMove possibleMove = PossibleMove(tmpNode, true);
		GameManager * tmp = possibleMove.SetOneChild();
		if (tmp == NULL)
		{
			int i = std::rand() % tmpNode->getChilds().size();
			tmpNode = tmpNode->getChilds()[i];
		}
		else
			tmpNode = tmp;
	}
	if (tmpNode->getBlackScore() >= 10 || tmpNode->getBlackWin())
		return true;
	else
		return false;
}
