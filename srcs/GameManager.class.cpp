// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GameManager.class.cpp                              :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/02/28 13:56:49 by semartin          #+#    #+#             //
//   Updated: 2018/02/28 13:56:50 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "GameManager.class.hpp"

GameManager::GameManager(int _Board[], bool _HasWon, bool _bPlayerOneTurn, int _WhiteScore, int _BlackScore, int WinY, int WinX) :
		HeuristicValue(0), Parent(NULL), LastMove(0,0), BlackWin(false), WhiteWin(false), HasWon(_HasWon), bPlayerOneTurn(_bPlayerOneTurn),
		WhiteScore(_WhiteScore), BlackScore(_BlackScore), Board(BOARD_HEIGHT * BOARD_WIDTH), WinPos(WinY, WinX)
	{
		for (int i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++)
		{
			Board[i] = _Board[i];
			if ((Board[i] & STONE_BLACK) != 0)
				BlackStones.push_back(Coord(i / BOARD_WIDTH, i % BOARD_WIDTH));
			else if ((Board[i] & STONE_WHITE) != 0)
				WhiteStones.push_back(Coord(i / BOARD_WIDTH, i % BOARD_WIDTH));
		}
	}