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

extern "C" 
{
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