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
#include "GameManager.class.hpp"

class Rules
{

private:
	static void somethingToEatWithPlayer(int Opponent, int i, int j, GameManager * Instance);
	static void somethingToEatOnTheBoard(int Player, int Opponent, GameManager * Instance);
	static bool breakWin(int Player, int Opponent, int y, int x, GameManager * Instance);
	static void checkBreak(bool first, GameManager * Instance);
	static void canBeEat(int Player, int Opponent, int i, int j, GameManager * Instance);
	static int winByCapture(GameManager * Instance);


public:
	static bool EmptyCase(int Content);
	static void youWin(int Player, int Opponent, int y, int x, GameManager * Instance);
	static bool CheckDoubleTreeBox(int y, int x, int Player1, GameManager * Instance);
	static int CheckWin(int Player, int y, int x, GameManager * Instance);
	static bool somethingToEatWithEmpty(int Player, int Opponent, int i, int j, GameManager * Instance);

};