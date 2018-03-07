// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Area.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/03/06 12:19:43 by semartin          #+#    #+#             //
//   Updated: 2018/03/06 12:19:44 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Area.hpp"

void Area::Update(std::vector<Area> & PlayArea, int y, int x)
{
	bool PlayAreaExist = false;
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
		tmp.Pos.x = x - 1;
		tmp.Pos.y = y - 1;
		PlayArea.push_back(tmp);
	}
}