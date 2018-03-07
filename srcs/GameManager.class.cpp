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

					tmp.Pos.x = (x - AREA_SIZE > 0) ? x - AREA_SIZE : 0;
					tmp.Pos.y = (y - AREA_SIZE > 0) ? y - AREA_SIZE : 0;
					
					tmp.Width = 1;
					tmp.Height = 1;
					for (int i = 1; i <= AREA_SIZE; i++)
					{
						if (x - i >= 0)
							tmp.Width++;
						if (x + i < BOARD_WIDTH)
							tmp.Width++;
						if (y - i >= 0)
							tmp.Height++;
						if (y + i < BOARD_HEIGHT)
							tmp.Height++;
					}
					tmp.Density = 1;
					PlayArea.push_back(tmp);
				}
			}
		}

		// for (size_t i = 0; i < PlayArea.size(); i++)
		// {
		// 	std::cout <<  "Width = "<<PlayArea[i].Width << " et Height = " << PlayArea[i].Height << " et X = " << PlayArea[i].Pos.x << " et Y = " << PlayArea[i].Pos.y << std::endl;
		// }
	}