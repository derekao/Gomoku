// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/03/02 15:42:53 by semartin          #+#    #+#             //
//   Updated: 2018/03/02 15:42:53 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Extern.hpp"

int main()
{
	GameStatus game;
	game.bPlayerOneTurn = true;
	game.HasWon = false;
	game.WhiteScore = 0;
	game.BlackScore = 0;
	game.WinY = -1;
	game.WinX = -1;

	for (int i = 0; i < 361; i ++)
	{
		game.Board[i] = 0;
	}


	// for (int i = 0; i < 361; i ++)
	// {
	// 	std::cout << game.Board[i] << " ";
	// 	if (i % 19 == 18)
	// 		std::cout << std::endl;
	// }

	CoordIA tmp = IAPlay(game);
	std::cout << "x = " << tmp.x << " et y = " << tmp.y << std::endl;
	// while(1);
}