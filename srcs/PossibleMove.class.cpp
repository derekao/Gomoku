// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PossibleMove.class.cpp                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/03/01 16:34:59 by semartin          #+#    #+#             //
//   Updated: 2018/03/01 16:34:59 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "PossibleMove.class.hpp"

PossibleMove::PossibleMove(GameManager * src) : Board(src),
	HighestHeuristicValue(src->getHeuristicValue()), LowestHeuristicValue(src->getHeuristicValue())
{
	Compute();
}

void PossibleMove::Compute()
{
	GameManager * tmp;

	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (!StoneNearby(i, j))
			{
				tmp = new GameManager(*Board);
				if (Board->getbPlayerOneTurn())
				{
					tmp->getBoard()[i * BOARD_WIDTH + j] = STONE_BLACK;
				}
				else
				{
					tmp->getBoard()[i * BOARD_WIDTH + j] = STONE_WHITE;
				}
//				tmp->setHeuristicValue(SUPERFONCTION);
				if (tmp->getHeuristicValue() > HighestHeuristicValue)
				{
					HighestHeuristicValue = tmp->getHeuristicValue();
					tabMove.push_back(tmp);
				}
				else if (tmp->getHeuristicValue() < LowestHeuristicValue)
				{
					std::cerr << "WTF IS THIS VALUE?" << std::endl;
					exit(0);
				}
				else
				{
					delete tmp;
				}
			}
		}
	}
}

// Return True if there is a stone 2 cells around the stone in parameter
bool PossibleMove::StoneNearby(int y, int x)
{
	for (int i = y - 2; i < y + 2; i++)
	{
		if (i < 0)
			continue;
		if (i >= BOARD_HEIGHT)
			break;
		for (int j = x - 2; j < x - 2; j++)
		{
			if (j < 0)
				continue;
			if (j >= BOARD_WIDTH)
				break;
			if (!Rules::EmptyCase(Board->getBoard()[y * BOARD_WIDTH + x]))
				return true;
		}
	}
	return false;
}