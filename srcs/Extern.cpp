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
#include <fstream>

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
	//	PossibleMove::PlayStone(9, 8, &Board);
	//	printBoard(&Board);
		MinMax Algo = MinMax(&Board);
		Coord tmp = Algo.getSolution();
		MoveChosed.y = tmp.y;
		MoveChosed.x = tmp.x; 
		return MoveChosed;
	}
}