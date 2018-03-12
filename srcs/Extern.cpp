// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Extern.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/02/28 17:52:05 by semartin          #+#    #+#             //
//   Updated: 2018/02/28 17:52:05 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Extern.hpp"
#include "PossibleMove.class.hpp"
#include "Heuristic.class.hpp"
#include <fstream>

static void printBoard(GameManager * Board)
{
	for (int i = 0; i < 361; i ++)
	{
		if (Board->getBoard()[i]  > 2)
			std::cout << "0 ";
		else
			std::cout << Board->getBoard()[i] << " ";
		if (i % 19 == 18)
			std::cout << std::endl;
	}
}

// static void printBoard(GameManager * Board)
// {
// 	for (int i = 0; i < 361; i ++)
// 	{
// 		std::cout << Board->getBoard()[i] << " ";
// 		if (i % 19 == 18)
// 			std::cout << std::endl;
// 	}
// }

extern "C" 
{
	/*bool CheckDoubleTree(int y, int x, GameStatus Game)
	{
		std::ofstream file("debug.txt", std::ios::out | std::ios::trunc);
		GameManager test = GameManager(Game.Board, Game.HasWon, Game.bPlayerOneTurn, Game.WhiteScore, Game.BlackScore, Game.WinY, Game.WinX);
		for (int i = 0; i < BOARD_HEIGHT*BOARD_WIDTH; i++)
		{
			file << Game.Board[i] << " ";
			if (i % BOARD_WIDTH == BOARD_WIDTH - 1)
				file << std::endl;
		}
		return Rules::CheckDoubleTreeBox(y, x, &test);
	}*/

	CoordIA IAPlay(GameStatus Game)
	{
		CoordIA MoveChosed;
		GameManager Board = GameManager(Game.Board, Game.HasWon, Game.bPlayerOneTurn, Game.WhiteScore, Game.BlackScore, Game.WinY, Game.WinX);
		
		int PlayerOne, PlayerTwo;
		if (Game.bPlayerOneTurn)
		{
			PlayerOne = STONE_BLACK;
			PlayerTwo = STONE_WHITE;
		}
		else
		{
			PlayerOne = STONE_WHITE;
			PlayerTwo = STONE_BLACK;
		}

		Heuristic bestMoves = Heuristic(PlayerOne, PlayerTwo, &Board);
		bestMoves.searchMoves();
		PossibleMove::PlayStone(0, 0, &Board);
		PossibleMove::PlayStone(1, 1, &Board);
		PossibleMove::PlayStone(9, 9, &Board);
		PossibleMove::PlayStone(1, 2, &Board);
		PossibleMove::PlayStone(0, 1, &Board);
		std::cout << "MDR" << std::endl;
		PossibleMove::PlayStone(1, 3, &Board);
		// PossibleMove::PlayStone(7, 8, &Board);
		// PossibleMove::PlayStone(8, 11, &Board);
		// PossibleMove::PlayStone(6, 7, &Board);
		// PossibleMove::PlayStone(5, 6, &Board);
		// PossibleMove::PlayStone(11, 11, &Board);
		// PossibleMove::PlayStone(7, 11, &Board);
		// PossibleMove::PlayStone(6, 11, &Board);
		//PossibleMove::PlayStone(8, 10, &Board);
		// PossibleMove::PlayStone(11, 11, &Board);
		// PossibleMove::PlayStone(3, 2, &Board);
		// PossibleMove::PlayStone(8, 11, &Board);
		std::cout << "MDR2" << std::endl;
		printBoard(&Board);
		
		MinMax Algo = MinMax(&Board);
		Coord tmp = Algo.getSolution();
		MoveChosed.y = tmp.y;
		MoveChosed.x = tmp.x;
		return MoveChosed;
	}
}