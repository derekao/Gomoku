// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GameManager.class.hpp                              :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/02/28 13:56:40 by semartin          #+#    #+#             //
//   Updated: 2018/02/28 13:56:41 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>
#include <vector>
#include "Coord.hpp"

#define STONE_EMPTY 0
#define STONE_BLACK 1
#define STONE_WHITE 2
#define STONE_WHITEFORBIDDEN 4
#define STONE_BLACKFORBIDDEN 8
#define STONE_WHITEDOUBLETREE 16
#define STONE_BLACKDOUBLETREE 32

#define BOARD_HEIGHT 19
#define BOARD_WIDTH 19

class GameManager
{

private:
	bool BlackWin;
	bool WhiteWin;
	bool HasWon;
	bool bPlayerOneTurn;

	int WhiteScore;
	int BlackScore;

	std::vector<int> Board;

	Coord WinPos;
	
	std::vector<Coord> ListEatCoord;

public:
	//Constructor
	GameManager(int _Board[], bool _HasWon, bool _bPlayerOneTurn, int _WhiteScore, int _BlackScore, int WinY, int WinX) :
		BlackWin(false), WhiteWin(false), HasWon(_HasWon), bPlayerOneTurn(_bPlayerOneTurn),
		WhiteScore(_WhiteScore), BlackScore(_BlackScore), Board(BOARD_HEIGHT * BOARD_WIDTH), WinPos(WinY, WinX)
	{
		for (int i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++)
		{
			Board[i] = _Board[i];
		}
	};

	// Accessor
	bool getBlackWin() { return BlackWin; };
	bool getWhiteWin() { return WhiteWin; };
	bool getHasWon() { return HasWon; };
	bool getbPlayerOneTurn() { return bPlayerOneTurn; };

	int getWhiteScore() { return WhiteScore; };
	int getBlackScore() { return BlackScore; };

	std::vector<int> & getBoard() { return Board; };

	Coord & getWinPos() { return WinPos; };

	std::vector<Coord> & getListEatCoord() { return ListEatCoord; };

	// Mutator
	void setBlackWin(bool b) { BlackWin = b; };
	void setWhiteWin(bool b) { WhiteWin = b; };
	void setHasWon(bool b) { HasWon = b; };
	void setbPlayerOneTurn(bool b) { bPlayerOneTurn = b; };

	void setBlackScore(int n) { BlackScore = n; };
	void setWhiteScore(int n) { WhiteScore = n; };

	void setWinCoord(Coord & tmp) { WinPos.y = tmp.y; WinPos.x = tmp.x; };
	void setWinCoord(int y, int x) { WinPos.y = y; WinPos.x = x; };

};