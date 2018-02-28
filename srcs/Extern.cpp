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

extern "C" 
{
	bool CheckDoubleTree(int y, int x, GameStatus Game)
	{
		GameManager test = GameManager(Game.Board, Game.HasWon, Game.bPlayerOneTurn, Game.WhiteScore, Game.BlackScore, Game.WinY, Game.WinX);
		return Rules::CheckDoubleTreeBox(y, x, &test);
	}
}