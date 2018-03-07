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
		//PossibleMove::PlayStone(9, 10, &Board);
		//PossibleMove::PlayStone(7, 9, &Board);
		// PossibleMove::PlayStone(10, 9, &Board);
		// PossibleMove::PlayStone(9, 11, &Board);
		// PossibleMove::PlayStone(9, 8, &Board);
		// PossibleMove::PlayStone(11, 10, &Board);
		// PossibleMove::PlayStone(8, 7, &Board);
		// PossibleMove::PlayStone(10, 8, &Board);
		// PossibleMove::PlayStone(7, 6, &Board);
		// PossibleMove::PlayStone(6, 5, &Board);
		// PossibleMove::PlayStone(5, 4, &Board);
		// PossibleMove::PlayStone(10, 11, &Board);
		// PossibleMove::PlayStone(4, 3, &Board);
		// PossibleMove::PlayStone(11, 11, &Board);
		// PossibleMove::PlayStone(3, 2, &Board);
		// PossibleMove::PlayStone(8, 11, &Board);
		 printBoard(&Board);
		for (size_t i = 0; i < Board.getPlayArea().size(); i++)
		{
			std::cout <<  "Width = "<<Board.getPlayArea()[i].Width << " et Height = " << Board.getPlayArea()[i].Height << " et X = " << Board.getPlayArea()[i].Pos.x << " et Y = " << Board.getPlayArea()[i].Pos.y << std::endl;
		}
		MinMax Algo = MinMax(&Board);
		Coord tmp = Algo.getSolution();
		MoveChosed.y = tmp.y;
		MoveChosed.x = tmp.x; 
		return MoveChosed;
	}
}