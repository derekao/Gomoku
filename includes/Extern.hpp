// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Extern.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/02/28 17:52:16 by semartin          #+#    #+#             //
//   Updated: 2018/02/28 17:52:16 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once
#include "GameManager.class.hpp"
#include "Coord.hpp"
#include "MinMax.hpp"
#include "Rules.class.hpp"

extern "C" 
{
	// Share struct between C# and C++ for the IAPlay Param
	struct GameStatus
	{
		int Board[BOARD_HEIGHT * BOARD_WIDTH];
		bool bPlayerOneTurn;
		bool HasWon;
		int WhiteScore;
		int BlackScore;
		int WinY;
		int WinX;
		int Depth;
		double Timer;
		int Algo;
		int MaxMove;

	};

	// Share struct between C# and C++ for the IAPlay return
	struct CoordIA
	{
		int y;
		int x;
		int Depth;
		double Time;
		int Value;
	};

	CoordIA IAPlay(GameStatus);
}