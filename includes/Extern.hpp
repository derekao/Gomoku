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
#include "Rules.class.hpp"

extern "C" 
{
	struct GameStatus
	{
		int Board[BOARD_HEIGHT * BOARD_WIDTH];
		bool bPlayerOneTurn;
		bool HasWon;
		int WhiteScore;
		int BlackScore;
		int WinY;
		int WinX;

	};

	bool CheckDoubleTree(int y, int x, GameStatus Game);
}