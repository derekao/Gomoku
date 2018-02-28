// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Rules.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/02/28 11:47:01 by semartin          #+#    #+#             //
//   Updated: 2018/02/28 11:47:02 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>
#include "Board.class.hpp"

class Rules
{

private:
	static void somethingToEatWithPlayer(int Opponent, int i, int j, GameManager * Instance)
	static void somethingToEatOnTheBoard(int Player, int Opponent, GameManager * Instance);


public:
	static bool EmptyCase(int Content);
	static void youWin(int Player, int Opponent, int y, int x, GameManager * Instance);

};