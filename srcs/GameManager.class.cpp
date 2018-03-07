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
		HeuristicValue(0), LastMove(0,0), BlackWin(false), WhiteWin(false), HasWon(_HasWon), bPlayerOneTurn(_bPlayerOneTurn),
		WhiteScore(_WhiteScore), BlackScore(_BlackScore), Board(BOARD_HEIGHT * BOARD_WIDTH), WinPos(WinY, WinX)
	{
		for (int i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++)
		{
			Board[i] = _Board[i];
			if (Board[i] != STONE_EMPTY)
			{
				bool PlayAreaExist = false;
				int y = i / BOARD_WIDTH;
				int x = i % BOARD_HEIGHT;
				for (size_t i = 0; i < PlayArea.size(); i++)
				{
					if (x >= PlayArea[i].Pos.x && x < PlayArea[i].Pos.x + PlayArea[i].Width
						&& y >= PlayArea[i].Pos.x && y < PlayArea[i].Pos.y + PlayArea[i].Height)
					{
						if (x == PlayArea[i].Pos.x && x >= 1)
						{
							PlayArea[i].Width++;
							PlayArea[i].Pos.x -= 1;
						}
						if (x == PlayArea[i].Pos.x + PlayArea[i].Width - 1)
						{
							PlayArea[i].Width++;
						}
						if (y == PlayArea[i].Pos.y && y >= 1)
						{
							PlayArea[i].Height++;
							PlayArea[i].Pos.y -= 1;
						}
						if (y == PlayArea[i].Pos.y + PlayArea[i].Height - 1)
						{
							PlayArea[i].Height++;
						}
						PlayAreaExist = true;
						break;
					}
				}
				if (!PlayAreaExist)
				{
					Area tmp;
					tmp.Width = 1;
					tmp.Height = 1;
					tmp.Pos.x = x - 1;
					tmp.Pos.y = y - 1;
					if (x >= 1)
						tmp.Width++;
					else
						tmp.Pos.x = x;
					if (x < BOARD_WIDTH - 1)
						tmp.Width++;
					if (y >= 1)
						tmp.Height++;
					else
						tmp.Pos.y = y;
					if (y < BOARD_HEIGHT - 1)
						tmp.Height++;
					PlayArea.push_back(tmp);
				}
			}
		}

		// for (size_t i = 0; i < PlayArea.size(); i++)
		// {
		// 	std::cout <<  "Width = "<<PlayArea[i].Width << " et Height = " << PlayArea[i].Height << " et X = " << PlayArea[i].Pos.x << " et Y = " << PlayArea[i].Pos.y << std::endl;
		// }
	}