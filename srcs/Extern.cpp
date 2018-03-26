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
		int PlayerOne, PlayerTwo;
		
		GameManager Board = GameManager(Game.Board, Game.HasWon, Game.bPlayerOneTurn, Game.WhiteScore, Game.BlackScore, Game.WinY, Game.WinX);
		MinMax::MaxDepth = Game.Depth;
		MinMax::MaxTimer = Game.Timer;
		PossibleMove::MaxMove = Game.MaxMove;

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

		std::srand(std::clock());
		Heuristic bestMoves = Heuristic(PlayerOne, PlayerTwo, &Board);
		Heuristic::ramdomMove = (std::rand() % 2 == 0 ? true : false);
		bestMoves.searchMoves();
		
		// PossibleMove::PlayStone(9, 9, &Board);
		// PossibleMove::PlayStone(0, 9, &Board);

		// PossibleMove::PlayStone(9, 8, &Board);
		// PossibleMove::PlayStone(0, 8, &Board);

		// PossibleMove::PlayStone(9, 7, &Board);
		// PossibleMove::PlayStone(0, 0, &Board);
		
		// PossibleMove::PlayStone(9 , 6, &Board);
		// PossibleMove::PlayStone(1, 6, &Board);

		

		// PossibleMove::PlayStone(6, 9, &Board);
		// PossibleMove::PlayStone(10, 9, &Board);

		// PossibleMove::PlayStone(11, 7, &Board);
		// PossibleMove::PlayStone(11, 8, &Board);

		// PossibleMove::PlayStone(12, 7, &Board);
		// PossibleMove::PlayStone(9, 10, &Board);
		
		// PossibleMove::PlayStone(10 ,8, &Board);
		// PossibleMove::PlayStone(12, 6, &Board);

		// PossibleMove::PlayStone(9 ,7, &Board);
		// PossibleMove::PlayStone(13, 7, &Board);

		// PossibleMove::PlayStone(8, 6, &Board);
		// PossibleMove::PlayStone(7, 5, &Board);

		// PossibleMove::PlayStone(12, 10, &Board);
		// PossibleMove::PlayStone(11, 9, &Board);

		// PossibleMove::PlayStone(12, 9, &Board);
		// PossibleMove::PlayStone(10, 7, &Board);

		// PossibleMove::PlayStone(6, 12, &Board);
		// PossibleMove::PlayStone(9, 4, &Board);

		// PossibleMove::PlayStone(7, 11, &Board);
		// PossibleMove::PlayStone(5, 13, &Board);

		// PossibleMove::PlayStone(8, 7, &Board);
		// PossibleMove::PlayStone(10, 11, &Board);


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

		/* YO*/
		//  PossibleMove::PlayStone(9, 9, &Board);
		//  PossibleMove::PlayStone(8, 8, &Board);

		//  PossibleMove::PlayStone(9, 7, &Board);
		//  PossibleMove::PlayStone(9, 8, &Board);

		//  PossibleMove::PlayStone(10, 8, &Board);
		//  PossibleMove::PlayStone(8, 10, &Board);

		// PossibleMove::PlayStone(8, 6, &Board);
		// PossibleMove::PlayStone(11, 9, &Board);
		

		// PossibleMove::PlayStone(11,7, &Board);
		// PossibleMove::PlayStone(7, 8, &Board);

		std::cout << "MDR2" << std::endl;
		printBoard(&Board);
		
		MinMax Algo = MinMax(&Board, Game.Algo);
		Coord tmp = Algo.getSolution();
		MoveChosed.Depth = Algo.getDepth();
		MoveChosed.Time = Algo.getTime();
		MoveChosed.y = tmp.y;
		MoveChosed.x = tmp.x;
		MoveChosed.Value = Algo.getValue();
		return MoveChosed;
	}
}