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
//#include "Area.hpp"

#define STONE_EMPTY 0
#define STONE_BLACK 1
#define STONE_WHITE 2
#define STONE_WHITEFORBIDDEN 4
#define STONE_BLACKFORBIDDEN 8
#define STONE_WHITEDOUBLETREE 16
#define STONE_BLACKDOUBLETREE 32

#define BOARD_HEIGHT 19
#define BOARD_WIDTH 19

#define MAX_INFINIT 1073741824
#define MIN_INFINIT -1073741825

class GameManager
{

private:
	GameManager();

	int HeuristicValue;
	GameManager * Parent;
	Coord LastMove;
//	vector<Area> PlayArea;


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
		HeuristicValue(0), LastMove(0,0), BlackWin(false), WhiteWin(false), HasWon(_HasWon), bPlayerOneTurn(_bPlayerOneTurn),
		WhiteScore(_WhiteScore), BlackScore(_BlackScore), Board(BOARD_HEIGHT * BOARD_WIDTH), WinPos(WinY, WinX)
	{
		for (int i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++)
		{
			Board[i] = _Board[i];
			// if (Board[i] != STONE_EMPTY)
			// {
			// 	int y = i / BOARD_WIDTH;
			// 	int x = i % BOARD_HEIGHT;
			// 	for (size_t i = 0; i < PlayArea.size(); i++)
			// 	{
			// 		if (x >= PlayArea[i].Pos.x && x <= PlayArea[i].Pos.x + PlayArea[i].Width
			// 			&& y => PlayArea[i].Po.x && y <= PlayArea[i].Pos.y + PlayArea.Height)
			// 		{
			// 			if (x == PlayArea[i].Pos.x && x >= 1)
			// 			{
			// 				PlayArea[i].Width++;
			// 				PlayArea[i].Pos.x -= 1;
			// 			}
			// 			if (x == PlayArea[i].Pos.x + PlayArea[i].Width)
			// 			{
			// 				PlayArea[i].Width++;
			// 			}
			// 			if (y == PlayArea[i].Pos.y && y >= 1)
			// 			{
			// 				PlayArea[i].Hight++;
			// 				PlayArea[i].Pos.y -= 1;
			// 			}
			// 			if (y == PlayArea[i].Pos.y + PlayArea[i].Height)
			// 			{
			// 				PlayArea[i].Height++;
			// 			}		
			// 		}
			// 	}
			// }
		}
	};

	GameManager(GameManager const & src) :
		HeuristicValue(src.HeuristicValue), LastMove(0,0), BlackWin(src.BlackWin), WhiteWin(src.WhiteWin), HasWon(src.HasWon), bPlayerOneTurn(src.bPlayerOneTurn),
		WhiteScore(src.WhiteScore), BlackScore( src.BlackScore), Board(src.Board), WinPos(src.WinPos.y, src.WinPos.x)
	{
		return ;
	}

	// Accessor
	int getHeuristicValue() { return HeuristicValue; };
	GameManager * getParent() { return Parent; };
	Coord & getLastMove() { return LastMove; };

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
	void setHeuristicValue(int n) { HeuristicValue = n; };
	void setParent(GameManager * Board) { Parent = Board; };
	void setLastMove(Coord & move) { LastMove.y = move.y; LastMove.x = move.x; ;}

	void setBlackWin(bool b) { BlackWin = b; };
	void setWhiteWin(bool b) { WhiteWin = b; };
	void setHasWon(bool b) { HasWon = b; };
	void setbPlayerOneTurn(bool b) { bPlayerOneTurn = b; };

	void setBlackScore(int n) { BlackScore = n; };
	void setWhiteScore(int n) { WhiteScore = n; };

	void setWinCoord(Coord & tmp) { WinPos.y = tmp.y; WinPos.x = tmp.x; };
	void setWinCoord(int y, int x) { WinPos.y = y; WinPos.x = x; };

};