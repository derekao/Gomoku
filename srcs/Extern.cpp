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
			std::cout << (int)Board->getBoard()[i] << " ";
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
		// PossibleMove::PlayStone(9, 9, &Board);
		// PossibleMove::PlayStone(8, 18, &Board);

		// PossibleMove::PlayStone(9, 7, &Board);
		// PossibleMove::PlayStone(9, 8, &Board);

		// PossibleMove::PlayStone(10, 8, &Board);
		// PossibleMove::PlayStone(11, 9, &Board);

		// PossibleMove::PlayStone(8, 10, &Board);
		// PossibleMove::PlayStone(11, 7, &Board);
		

		// PossibleMove::PlayStone(7, 8, &Board);
		// PossibleMove::PlayStone(8, 6, &Board);

		// PossibleMove::PlayStone(7, 11, &Board);
		// PossibleMove::PlayStone(6, 12, &Board);

		// PossibleMove::PlayStone(11, 8, &Board);
		// PossibleMove::PlayStone(4, 12, &Board);

		// PossibleMove::PlayStone(5, 12, &Board);
		// PossibleMove::PlayStone(6, 4, &Board);

		// PossibleMove::PlayStone(5, 3, &Board);
		// PossibleMove::PlayStone(8, 4, &Board);

		// PossibleMove::PlayStone(8, 5, &Board);
		// PossibleMove::PlayStone(7, 4, &Board);

		// PossibleMove::PlayStone(9, 4, &Board);
		// PossibleMove::PlayStone(7, 6, &Board);


		// PossibleMove::PlayStone(9, 6, &Board);
		// PossibleMove::PlayStone(10, 3, &Board);

		// PossibleMove::PlayStone(5, 4, &Board);
		// PossibleMove::PlayStone(10, 4, &Board);
		
		// PossibleMove::PlayStone(9, 4, &Board);
		// PossibleMove::PlayStone(7, 3, &Board);


		// PossibleMove::PlayStone(7, 5, &Board);
		// PossibleMove::PlayStone(10, 5, &Board);

		// PossibleMove::PlayStone(10, 2, &Board);
		// PossibleMove::PlayStone(5, 5, &Board);

		// PossibleMove::PlayStone(8, 2, &Board);
		// PossibleMove::PlayStone(4, 6, &Board);

		// PossibleMove::PlayStone(3, 7, &Board);
		// PossibleMove::PlayStone(10, 6, &Board);

		std::cout << "MDR2" << std::endl;
		printBoard(&Board);
		
		MinMax Algo = MinMax(&Board);
		Coord tmp = Algo.getSolution();
		MoveChosed.Depth = Algo.getDepth();
		MoveChosed.Time = Algo.getTime();
		MoveChosed.y = tmp.y;
		MoveChosed.x = tmp.x;
		return MoveChosed;
	}
}