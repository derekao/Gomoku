﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

static public class Rules {

	/// <summary>
	/// Return True if the Cell dont have any Black or White Stone
	/// </summary>
	public static bool EmptyCase(int Content) {

		if ((Content & GameManager.Stone.Black) == 0 && (Content & GameManager.Stone.White) == 0)
			return true;
		else
			return false;
	}

	/// <summary>
	/// Return True if there is nothing to eat on the board
	/// </summary>
	public static bool somethingToEatOnTheBoard(int Player, int Opponent)
	{
		bool canEat = false;
		for (int i = 0; i < GameManager.Instance.iHeightBoard; i++) {
			for (int j = 0; j < GameManager.Instance.iWidthBoard; j++) {
				if (!canEat && (GameManager.Instance.Board[i, j] & Player) != 0) {
					canEat = somethingToEatWithPlayer(Opponent, i, j);
				}
			}
		}
		return canEat;
	}

	/// <summary>
	/// Return True if you can eat Opponent Stones
	/// </summary>
	public static bool somethingToEatWithPlayer(int Opponent, int i, int j)
	{
		bool canEat = false;
		if (i < GameManager.Instance.iHeightBoard - 3 && (GameManager.Instance.Board[i + 1, j] & Opponent) != 0 && (GameManager.Instance.Board[i + 2, j] & Opponent) != 0 && GameManager.Instance.Board[i + 3, j] == 0) // Bottom
			canEat = true;
		if (j < GameManager.Instance.iWidthBoard - 3 && (GameManager.Instance.Board[i, j + 1] & Opponent) != 0 && (GameManager.Instance.Board[i, j + 2] & Opponent) != 0 && GameManager.Instance.Board[i, j + 3] == 0) // Right
			canEat = true;
		if (i > 3 && j < GameManager.Instance.iWidthBoard - 3 && (GameManager.Instance.Board[i - 1, j + 1] & Opponent) != 0 && (GameManager.Instance.Board[i - 2, j + 2] & Opponent) != 0 && GameManager.Instance.Board[i - 3, j + 3] == 0) // Top Right
			canEat = true;
		if (i < GameManager.Instance.iHeightBoard - 3 && j < GameManager.Instance.iWidthBoard - 3 && (GameManager.Instance.Board[i + 1, j + 1] & Opponent) != 0 && (GameManager.Instance.Board[i + 2, j + 2] & Opponent) != 0 && GameManager.Instance.Board[i + 3, j + 3] == 0) // Bottom Right
			canEat = true;
		if (i > 3 && j > 3 && (GameManager.Instance.Board[i - 1, j - 1] & Opponent) != 0 && (GameManager.Instance.Board[i - 2, j - 2] & Opponent) != 0 && GameManager.Instance.Board[i - 3, j - 3] == 0)  // Top Left
			canEat = true;
		if (i > 3 && (GameManager.Instance.Board[i - 1, j] & Opponent) != 0 && (GameManager.Instance.Board[i - 2, j] & Opponent) != 0 && GameManager.Instance.Board[i - 3, j] == 0) // Top
			canEat = true;
		if (j > 3 && (GameManager.Instance.Board[i, j - 1] & Opponent) != 0 && (GameManager.Instance.Board[i, j - 2] & Opponent) != 0 && GameManager.Instance.Board[i, j - 3] == 0) // Left
			canEat = true;
		if (j > 3 && i < GameManager.Instance.iHeightBoard - 3 && (GameManager.Instance.Board[i - 1, j - 1] & Opponent) != 0 && (GameManager.Instance.Board[i - 2, j - 2] & Opponent) != 0 && GameManager.Instance.Board[i - 3, j - 3] == 0) // Bottom Left
			canEat = true;
		return canEat;
	}

	/// <summary>
	/// Return True if the Cell [i,j] allow you yo eat Opponent Stones
	/// </summary>
	public static bool somethingToEatWithEmpty(int Player, int Opponent, int i, int j)
	{
		bool canEat = false;
		if (i < GameManager.Instance.iHeightBoard - 3 && (GameManager.Instance.Board[i + 1, j] & Opponent) != 0 && (GameManager.Instance.Board[i + 2, j] & Opponent) != 0 && (GameManager.Instance.Board[i + 3, j] & Player) != 0) // Bottom
			canEat = true;
		if (j < GameManager.Instance.iWidthBoard - 3 && (GameManager.Instance.Board[i, j + 1] & Opponent) != 0 && (GameManager.Instance.Board[i, j + 2] & Opponent) != 0 && (GameManager.Instance.Board[i, j + 3] & Player) != 0) // Right
			canEat = true;
		if (i > 3 && j < GameManager.Instance.iWidthBoard - 3 && (GameManager.Instance.Board[i - 1, j + 1] & Opponent) != 0 && (GameManager.Instance.Board[i - 2, j + 2] & Opponent) != 0 && (GameManager.Instance.Board[i - 3, j + 3] & Player) != 0) // Top Right
			canEat = true;
		if (i < GameManager.Instance.iHeightBoard - 3 && j < GameManager.Instance.iWidthBoard - 3 && (GameManager.Instance.Board[i + 1, j + 1] & Opponent) != 0 && (GameManager.Instance.Board[i + 2, j + 2] & Opponent) != 0 && (GameManager.Instance.Board[i + 3, j + 3] & Player) != 0) // Bottom Right
			canEat = true;
		if (i > 3 && j > 3 && (GameManager.Instance.Board[i - 1, j - 1] & Opponent) != 0 && (GameManager.Instance.Board[i - 2, j - 2] & Opponent) != 0 && (GameManager.Instance.Board[i - 3, j - 3] & Player) != 0)  //  Top Left
			canEat = true;
		if (i > 3 && (GameManager.Instance.Board[i - 1, j] & Opponent) != 0 && (GameManager.Instance.Board[i - 2, j] & Opponent) != 0 && (GameManager.Instance.Board[i - 3, j] & Player) != 0) // Top
			canEat = true;
		if (j > 3 && (GameManager.Instance.Board[i, j - 1] & Opponent) != 0 && (GameManager.Instance.Board[i, j - 2] & Opponent) != 0 && (GameManager.Instance.Board[i, j - 3] & Player) != 0) // Left
			canEat = true;
		if (j > 3 && i < GameManager.Instance.iHeightBoard - 3 && (GameManager.Instance.Board[i - 1, j - 1] & Opponent) != 0 && (GameManager.Instance.Board[i - 2, j - 2] & Opponent) != 0 && (GameManager.Instance.Board[i - 3, j - 3] & Player) != 0) // Bottom Left
			canEat = true;
		return canEat;
	}

	/// <summary>
	/// Display Stone, DoubleTree and Forbidden case on every board's cell.
	/// </summary>
	static public void DisplayBoard(bool bUndo = false) {

		int Forbidden;
		int ForbiddenOther;
		int DoubleTree;
		int DoubleTreeOther;

		if (GameManager.Instance.bPlayerOneTurn)
		{
			Forbidden = GameManager.Stone.BlackForbidden;
			DoubleTree = GameManager.Stone.BlackDoubleTree;
			ForbiddenOther = GameManager.Stone.WhiteForbidden;
			DoubleTreeOther = GameManager.Stone.WhiteDoubleTree;
		}
		else
		{
			Forbidden = GameManager.Stone.WhiteForbidden;
			DoubleTree = GameManager.Stone.WhiteDoubleTree;
			ForbiddenOther = GameManager.Stone.BlackForbidden;
			DoubleTreeOther = GameManager.Stone.BlackDoubleTree;
		}

		for (int i = 0; i < GameManager.Instance.iHeightBoard; i++)
		{
			for (int j = 0; j < GameManager.Instance.iWidthBoard; j++)
			{
				if (bUndo)
				{
					if ((GameManager.Instance.Board[i, j] & GameManager.Stone.Black) != 0)
					{
						changeBoxState(j, i, PlayStone.Type.Black);
					}
					else if ((GameManager.Instance.Board[i, j] & GameManager.Stone.White) != 0)
					{
						changeBoxState(j, i, PlayStone.Type.White);
					}
					else 
					{
						changeBoxState(j, i, PlayStone.Type.Empty);
					}
				}
				if ((GameManager.Instance.Board[i, j] & Forbidden) != 0)
				{
					changeBoxState(j, i, PlayStone.Type.Forbidden);
				}
				else if ((GameManager.Instance.Board[i, j] & ForbiddenOther) != 0)
				{
					changeBoxState(j, i, PlayStone.Type.Empty);
				}

				if ((GameManager.Instance.Board[i, j] & DoubleTree) != 0)
				{
					changeBoxState(j, i, PlayStone.Type.DoubleTree);
				}
				else if ((GameManager.Instance.Board[i, j] & DoubleTreeOther) != 0)
				{
					changeBoxState(j, i, PlayStone.Type.Empty);
				}
			}
		}
	}

	// Fill Forbidden cell on the GameManager.Board
	private static bool FillForbiddenBoard(int Width, int Height, bool bPlayer) {

		int Player;

		if (bPlayer)
		{
			Player = GameManager.Stone.BlackForbidden;
		}
		else
		{
			Player = GameManager.Stone.WhiteForbidden;
		}

		if ((GameManager.Instance.Board[Height, Width] & Player) == 0)
		{
			GameManager.Instance.Board[Height, Width] += Player;
		}
		return false;
		
	}

	/// <summary>
	/// Return True if there is a double tree on the cell [y,x]
	/// </summary>
	static public bool checkDoubleTreeBox(int y, int x)
	{
		int Player1;

		if (!GameManager.Instance.bPlayerOneTurn)
		{
			Player1 = GameManager.Stone.Black;
		}
		else
		{
			Player1 = GameManager.Stone.White;
		}

		int NumTree = 0;

		//  - X 0 X -
		if (x >= 2 && x < GameManager.Instance.iWidthBoard - 2 && EmptyCase(GameManager.Instance.Board[y, x - 2]) && GameManager.Instance.Board[y, x - 1] == Player1 && GameManager.Instance.Board[y, x + 1] == Player1 && EmptyCase(GameManager.Instance.Board[y, x + 2]))
		{
			NumTree++;
		}
		if (y >= 2 && y < GameManager.Instance.iHeightBoard - 2 && EmptyCase(GameManager.Instance.Board[y - 2, x]) && GameManager.Instance.Board[y - 1, x] == Player1 && GameManager.Instance.Board[y + 1, x] == Player1 && EmptyCase(GameManager.Instance.Board[y + 2, x]))
		{
			NumTree++;
		}
		if (x >= 2 && x < GameManager.Instance.iWidthBoard - 2 && EmptyCase(GameManager.Instance.Board[y, x - 2]) && y >= 2 && y < GameManager.Instance.iHeightBoard - 2
			&& EmptyCase(GameManager.Instance.Board[y - 2, x - 2]) && GameManager.Instance.Board[y - 1, x - 1] == Player1 && GameManager.Instance.Board[y + 1, x + 1] == Player1 && EmptyCase(GameManager.Instance.Board[y + 2, x + 2]))
		{
			NumTree++;
		}
		if (x >= 2 && x < GameManager.Instance.iWidthBoard - 2 && EmptyCase(GameManager.Instance.Board[y, x - 2]) && y >= 2 && y < GameManager.Instance.iHeightBoard - 2
			&& EmptyCase(GameManager.Instance.Board[y + 2, x - 2]) && GameManager.Instance.Board[y + 1, x - 1] == Player1 && GameManager.Instance.Board[y - 1, x + 1] == Player1 && EmptyCase(GameManager.Instance.Board[y - 2, x + 2]))
		{
			NumTree++;
		}

		// - X X 0 -
		if (x >= 3 && x < GameManager.Instance.iWidthBoard - 1 && EmptyCase(GameManager.Instance.Board[y, x - 3]) && GameManager.Instance.Board[y, x - 2] == Player1 && GameManager.Instance.Board[y, x - 1] == Player1 && EmptyCase(GameManager.Instance.Board[y, x + 1]))
		{
			NumTree++;
		}
		if (x >= 1 && x < GameManager.Instance.iWidthBoard - 3 && EmptyCase(GameManager.Instance.Board[y, x - 1]) && GameManager.Instance.Board[y, x + 1] == Player1 && GameManager.Instance.Board[y, x + 2] == Player1 && EmptyCase(GameManager.Instance.Board[y, x + 3]))
		{
			NumTree++;
		}
		if (y >= 3 && y < GameManager.Instance.iHeightBoard - 1 && EmptyCase(GameManager.Instance.Board[y - 3, x]) && GameManager.Instance.Board[y - 2, x] == Player1 && GameManager.Instance.Board[y - 1, x] == Player1 && EmptyCase(GameManager.Instance.Board[y + 1, x]))
		{
			NumTree++;
		}
		if (y >= 1 && y < GameManager.Instance.iHeightBoard - 3 && EmptyCase(GameManager.Instance.Board[y - 1, x]) && GameManager.Instance.Board[y + 1, x] == Player1 && GameManager.Instance.Board[y + 2, x] == Player1 && EmptyCase(GameManager.Instance.Board[y + 3, x]))
		{
			NumTree++;
		}
		if (x >= 3 && x < GameManager.Instance.iWidthBoard - 1 && y >= 3 && y < GameManager.Instance.iHeightBoard - 1
			&& EmptyCase(GameManager.Instance.Board[y - 3, x - 3]) && GameManager.Instance.Board[y - 2, x - 2] == Player1 && GameManager.Instance.Board[y - 1, x - 1] == Player1 && EmptyCase(GameManager.Instance.Board[y + 1, x + 1]))
		{
			NumTree++;
		}
		if (x >= 1 && x < GameManager.Instance.iWidthBoard - 3 && y >= 1 && y < GameManager.Instance.iHeightBoard - 3 
			&& EmptyCase(GameManager.Instance.Board[y - 1, x - 1]) && GameManager.Instance.Board[y + 1, x + 1] == Player1 && GameManager.Instance.Board[y + 2, x + 2] == Player1 && EmptyCase(GameManager.Instance.Board[y + 3, x + 3]))
		{
			NumTree++;
		}
		if (x >= 3 && x < GameManager.Instance.iWidthBoard - 1 && y >= 1 && y < GameManager.Instance.iHeightBoard - 3 
			&& EmptyCase(GameManager.Instance.Board[y + 3, x - 3]) && GameManager.Instance.Board[y + 2, x - 2] == Player1 && GameManager.Instance.Board[y + 1, x - 1] == Player1 && EmptyCase(GameManager.Instance.Board[y - 1, x + 1]))
		{
			NumTree++;
		}
		if (x >= 1 && x < GameManager.Instance.iWidthBoard - 3 && y >= 3 && y < GameManager.Instance.iHeightBoard - 1
			&& EmptyCase(GameManager.Instance.Board[y + 1, x - 1]) && GameManager.Instance.Board[y - 1, x + 1] == Player1 && GameManager.Instance.Board[y - 2, x + 2] == Player1 && EmptyCase(GameManager.Instance.Board[y - 3, x + 3]))
		{
			NumTree++;
		}

		// - X X - 0 -
		if (x >= 4 && x < GameManager.Instance.iWidthBoard - 1 && EmptyCase(GameManager.Instance.Board[y, x - 4]) && GameManager.Instance.Board[y, x - 3] == Player1 && GameManager.Instance.Board[y, x - 2] == Player1 && EmptyCase(GameManager.Instance.Board[y, x - 1])  && EmptyCase(GameManager.Instance.Board[y, x + 1]))
		{
			NumTree++;
		}
		if (x >= 1 && x < GameManager.Instance.iWidthBoard - 4 && EmptyCase(GameManager.Instance.Board[y, x + 4]) && GameManager.Instance.Board[y, x + 3] == Player1 && GameManager.Instance.Board[y, x + 2] == Player1 && EmptyCase(GameManager.Instance.Board[y, x + 1])  && EmptyCase(GameManager.Instance.Board[y, x - 1]))
		{
			NumTree++;
		}
		if (y >= 4 && y < GameManager.Instance.iHeightBoard - 1 && EmptyCase(GameManager.Instance.Board[y - 4, x]) && GameManager.Instance.Board[y - 3, x] == Player1 && GameManager.Instance.Board[y - 2, x] == Player1 && EmptyCase(GameManager.Instance.Board[y - 1, x])  && EmptyCase(GameManager.Instance.Board[y + 1, x]))
		{
			NumTree++;
		}
		if (y >= 1 && y < GameManager.Instance.iHeightBoard - 4 && EmptyCase(GameManager.Instance.Board[y + 4, x]) && GameManager.Instance.Board[y + 3, x] == Player1 && GameManager.Instance.Board[y + 2, x] == Player1 && EmptyCase(GameManager.Instance.Board[y + 1, x])  && EmptyCase(GameManager.Instance.Board[y - 1, x]))
		{
			NumTree++;
		}
		if (x >= 4 && x < GameManager.Instance.iWidthBoard - 1 && y >= 4 && y < GameManager.Instance.iHeightBoard - 1
			&& EmptyCase(GameManager.Instance.Board[y - 4, x - 4]) && GameManager.Instance.Board[y - 3, x - 3] == Player1 && GameManager.Instance.Board[y - 2, x - 2] == Player1 && EmptyCase(GameManager.Instance.Board[y - 1, x - 1])  && EmptyCase(GameManager.Instance.Board[y + 1, x + 1]))
		{
			NumTree++;
		}
		if (x >= 1 && x < GameManager.Instance.iWidthBoard - 4 && y >= 1 && y < GameManager.Instance.iHeightBoard - 4
			&& EmptyCase(GameManager.Instance.Board[y + 4, x + 4]) && GameManager.Instance.Board[y + 3, x + 3] == Player1 && GameManager.Instance.Board[y + 2, x + 2] == Player1 && EmptyCase(GameManager.Instance.Board[y + 1, x + 1])  && EmptyCase(GameManager.Instance.Board[y - 1, x - 1]))
		{
			NumTree++;
		}
		if (x >= 4 && x < GameManager.Instance.iWidthBoard - 1 && y >= 1 && y < GameManager.Instance.iHeightBoard - 4
			&& EmptyCase(GameManager.Instance.Board[y + 4, x - 4]) && GameManager.Instance.Board[y + 3, x - 3] == Player1 && GameManager.Instance.Board[y + 2, x - 2] == Player1 && EmptyCase(GameManager.Instance.Board[y + 1, x - 1])  && EmptyCase(GameManager.Instance.Board[y - 1, x + 1]))
		{
			NumTree++;
		}
		if (x >= 1 && x < GameManager.Instance.iWidthBoard - 4 && y >= 4 && y < GameManager.Instance.iHeightBoard - 1
			&& EmptyCase(GameManager.Instance.Board[y - 4, x + 4]) && GameManager.Instance.Board[y - 3, x + 3] == Player1 && GameManager.Instance.Board[y - 2, x + 2] == Player1 && EmptyCase(GameManager.Instance.Board[y - 1, x + 1])  && EmptyCase(GameManager.Instance.Board[y + 1, x - 1]))
		{
			NumTree++;
		}

		//  - X - 0 X -
		if (x >= 3 && x < GameManager.Instance.iWidthBoard - 2 && EmptyCase(GameManager.Instance.Board[y, x - 3]) && GameManager.Instance.Board[y, x - 2] == Player1 && EmptyCase(GameManager.Instance.Board[y, x - 1]) && GameManager.Instance.Board[y, x + 1] == Player1  && EmptyCase(GameManager.Instance.Board[y, x + 2]))
		{
			NumTree++;
		}
		if (x >= 2 && x < GameManager.Instance.iWidthBoard - 3 && EmptyCase(GameManager.Instance.Board[y, x + 3]) && GameManager.Instance.Board[y, x + 2] == Player1 && EmptyCase(GameManager.Instance.Board[y, x + 1]) && GameManager.Instance.Board[y, x - 1] == Player1  && EmptyCase(GameManager.Instance.Board[y, x - 2]))
		{
			NumTree++;
		}
		if (y >= 3 && y < GameManager.Instance.iHeightBoard - 2 && EmptyCase(GameManager.Instance.Board[y - 3, x]) && GameManager.Instance.Board[y - 2, x] == Player1 && EmptyCase(GameManager.Instance.Board[y - 1, x]) && GameManager.Instance.Board[y + 1, x] == Player1  && EmptyCase(GameManager.Instance.Board[y + 2, x]))
		{
			NumTree++;
		}
		if (y >= 2 && y < GameManager.Instance.iHeightBoard - 3 && EmptyCase(GameManager.Instance.Board[y + 3, x]) && GameManager.Instance.Board[y + 2, x] == Player1 && EmptyCase(GameManager.Instance.Board[y + 1, x]) && GameManager.Instance.Board[y - 1, x] == Player1  && EmptyCase(GameManager.Instance.Board[y - 2, x]))
		{
			NumTree++;
		}
		if (x >= 3 && x < GameManager.Instance.iWidthBoard - 2 && y >= 3 && y < GameManager.Instance.iHeightBoard - 2
			&& EmptyCase(GameManager.Instance.Board[y - 3, x - 3]) && GameManager.Instance.Board[y - 2, x - 2] == Player1 && EmptyCase(GameManager.Instance.Board[y - 1, x - 1]) && GameManager.Instance.Board[y + 1, x + 1] == Player1  && EmptyCase(GameManager.Instance.Board[y + 2, x + 2]))
		{
			NumTree++;
		}
		if (x >= 2 && x < GameManager.Instance.iWidthBoard - 3 && y >= 2 && y < GameManager.Instance.iHeightBoard - 3
			&& EmptyCase(GameManager.Instance.Board[y + 3, x + 3]) && GameManager.Instance.Board[y + 2, x + 2] == Player1 && EmptyCase(GameManager.Instance.Board[y + 1, x + 1]) && GameManager.Instance.Board[y - 1, x - 1] == Player1  && EmptyCase(GameManager.Instance.Board[y - 2, x - 2]))
		{
			NumTree++;
		}
		if (x >= 3 && x < GameManager.Instance.iWidthBoard - 2 && y >= 2 && y < GameManager.Instance.iHeightBoard - 3
			&& EmptyCase(GameManager.Instance.Board[y + 3, x - 3]) && GameManager.Instance.Board[y + 2, x - 2] == Player1 && EmptyCase(GameManager.Instance.Board[y + 1, x - 1]) && GameManager.Instance.Board[y - 1, x + 1] == Player1  && EmptyCase(GameManager.Instance.Board[y - 2, x + 2]))
		{
			NumTree++;
		}
		if (x >= 2 && x < GameManager.Instance.iWidthBoard - 3 && y >= 3 && y < GameManager.Instance.iHeightBoard - 2
			&& EmptyCase(GameManager.Instance.Board[y - 3, x + 3]) && GameManager.Instance.Board[y - 2, x + 2] == Player1 && EmptyCase(GameManager.Instance.Board[y - 1, x + 1]) && GameManager.Instance.Board[y + 1, x - 1] == Player1  && EmptyCase(GameManager.Instance.Board[y + 2, x - 2]))
		{
			NumTree++;
		}

		if (NumTree >= 2)
		{
			if (!GameManager.Instance.bPlayerOneTurn && (GameManager.Instance.Board[y, x] & GameManager.Stone.BlackDoubleTree) == 0)
			{
				GameManager.Instance.Board[y, x] += GameManager.Stone.BlackDoubleTree;
			}
			else if (GameManager.Instance.bPlayerOneTurn && (GameManager.Instance.Board[y, x] & GameManager.Stone.WhiteDoubleTree) == 0)
			{
				GameManager.Instance.Board[y, x] += GameManager.Stone.WhiteDoubleTree;
			}
			return true;
		}
		else 
		{
			if ((GameManager.Instance.Board[y, x] & GameManager.Stone.WhiteDoubleTree) != 0 && GameManager.Instance.bPlayerOneTurn)
				GameManager.Instance.Board[y, x] -= GameManager.Stone.WhiteDoubleTree;
			if ((GameManager.Instance.Board[y, x] & GameManager.Stone.BlackDoubleTree) != 0 && !GameManager.Instance.bPlayerOneTurn)
				GameManager.Instance.Board[y, x] -= GameManager.Stone.BlackDoubleTree;
			return false;
		}
	}

	/// <summary>
	/// Return True [y,x] is Forbidden due to capture
	/// </summary>
	static public void checkForbiddenBox(int y, int x) {

		int Player1;
		int Player2;

		if (GameManager.Instance.bPlayerOneTurn)
		{
			Player1 = GameManager.Stone.Black;
			Player2 = GameManager.Stone.White;
		}
		else
		{
			Player1 = GameManager.Stone.White;
			Player2 = GameManager.Stone.Black;
		}

		bool bEmpty = true;

		if (x >= 1 && x < GameManager.Instance.iWidthBoard - 2) // Gauche
		{
			if (GameManager.Instance.Board[y, x - 1] == Player2 && GameManager.Instance.Board[y, x + 1] == Player1 && GameManager.Instance.Board[y, x + 2] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.Instance.bPlayerOneTurn);
		}
		if (x < GameManager.Instance.iWidthBoard - 1 && x >= 2) // Droite
		{
			if (GameManager.Instance.Board[y, x - 2] == Player2 && GameManager.Instance.Board[y, x - 1] == Player1 && GameManager.Instance.Board[y, x + 1] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.Instance.bPlayerOneTurn);
		}
		if (y >= 1 && y < GameManager.Instance.iHeightBoard - 2) // Haut
		{
			if (GameManager.Instance.Board[y - 1, x] == Player2 && GameManager.Instance.Board[y + 1, x] == Player1 && GameManager.Instance.Board[y + 2, x] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.Instance.bPlayerOneTurn);
		}
		if (y < GameManager.Instance.iHeightBoard - 1 && y >= 2) // Bas
		{
			if (GameManager.Instance.Board[y - 2, x] == Player2 && GameManager.Instance.Board[y - 1, x] == Player1 && GameManager.Instance.Board[y + 1, x] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.Instance.bPlayerOneTurn);
		}
		if (x >= 1 && y >= 1 && y < GameManager.Instance.iHeightBoard - 2 && x < GameManager.Instance.iWidthBoard - 2) // Haut Gauche
		{
			if (GameManager.Instance.Board[y - 1, x - 1] == Player2 && GameManager.Instance.Board[y + 1, x + 1] == Player1 && GameManager.Instance.Board[y + 2, x + 2] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.Instance.bPlayerOneTurn);
		}
		if (x >= 1 && y < GameManager.Instance.iHeightBoard - 1 && x < GameManager.Instance.iWidthBoard - 2 && y >= 2) // Bas Gauche
		{
			if (GameManager.Instance.Board[y + 1, x - 1] == Player2 && GameManager.Instance.Board[y - 1, x + 1] == Player1 && GameManager.Instance.Board[y - 2, x + 2] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.Instance.bPlayerOneTurn);
		}
		if (x < GameManager.Instance.iWidthBoard - 1 && y >= 1 && x >= 2 && y < GameManager.Instance.iHeightBoard - 2) // Haut Droite
		{
			if (GameManager.Instance.Board[y - 1, x + 1] == Player2 && GameManager.Instance.Board[y + 1, x - 1] == Player1 && GameManager.Instance.Board[y + 2, x - 2] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.Instance.bPlayerOneTurn);
		}
		if (x < GameManager.Instance.iWidthBoard - 1 && y < GameManager.Instance.iHeightBoard - 1 && x >= 2 && y >= 2) // Bas Droite
		{
			if (GameManager.Instance.Board[y + 1, x + 1] == Player2 && GameManager.Instance.Board[y - 1, x - 1] == Player1 && GameManager.Instance.Board[y - 2, x - 2] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.Instance.bPlayerOneTurn);
		}
		if (bEmpty)
		{
			GameManager.Instance.Board[y, x] = GameManager.Stone.Empty;
		}
	}

	/// <summary>
	/// Print the image "Type" on the Board at the [Width,Height] cell
	/// </summary>
	static public void changeBoxState(int Width , int Height, PlayStone.Type type) {

		int id = Width + Height * GameManager.Instance.iWidthBoard + 1;
		GameObject box = GameObject.Find("Stone (" + id + ")");
		GameObject tmpBlackStone;
		GameObject tmpWhiteStone;
		GameObject tmpForbidden;
		GameObject tmpDoubleTree;
		Image tmpBlackStoneImage = null;
		Image tmpWhiteStoneImage = null;
		Image tmpForbiddenImage = null;
		Image tmpDoubleTreeImage = null;

		for (int i = 0; i < box.transform.childCount; i++)
		{
			Transform result = box.transform.GetChild(i);
			if (result.name == "BlackStone")
			{
				tmpBlackStone = result.gameObject;
				tmpBlackStoneImage = tmpBlackStone.GetComponent<Image>();
			}
			else if (result.name == "WhiteStone")
			{
				tmpWhiteStone = result.gameObject;
				tmpWhiteStoneImage = tmpWhiteStone.GetComponent<Image>();
			}
			else if (result.name == "Forbiden")
			{
				tmpForbidden = result.gameObject;
				tmpForbiddenImage = tmpForbidden.GetComponent<Image>();
			}
			else if (result.name == "DoubleTree")
			{
				tmpDoubleTree = result.gameObject;
				tmpDoubleTreeImage = tmpDoubleTree.GetComponent<Image>();
			}
		}
		if (!tmpBlackStoneImage || !tmpWhiteStoneImage || !tmpForbiddenImage || !tmpDoubleTreeImage)
			Debug.Log("Wrong Stone Init 2");
		else if (type == PlayStone.Type.Empty)
		{
			if (tmpForbiddenImage.enabled)
				tmpForbiddenImage.enabled = false;
			if (tmpDoubleTreeImage.enabled)
				tmpDoubleTreeImage.enabled = false;
			if (tmpBlackStoneImage.enabled)
				tmpBlackStoneImage.enabled = false;
			if (tmpWhiteStoneImage.enabled)
				tmpWhiteStoneImage.enabled = false;

		}
		else if (type == PlayStone.Type.Eat) 
		{
			GameManager.Instance.Board[Height, Width] = GameManager.Stone.Empty;
			if (GameManager.Instance.bPlayerOneTurn)
			{
				GameManager.Instance.BlackScore++;
				tmpWhiteStoneImage.enabled = false;
			}
			else
			{
				GameManager.Instance.WhiteScore++;
				tmpBlackStoneImage.enabled = false;
			}
		}
		else if (type == PlayStone.Type.DoubleTree && !tmpDoubleTreeImage.enabled)
			tmpDoubleTreeImage.enabled = true;
		else if (type == PlayStone.Type.Forbidden && !tmpForbiddenImage.enabled)
			tmpForbiddenImage.enabled = true;
		else if (type == PlayStone.Type.Black && !tmpBlackStoneImage.enabled)
			tmpBlackStoneImage.enabled = true;
		else if (type == PlayStone.Type.White && !tmpWhiteStoneImage.enabled)
			tmpWhiteStoneImage.enabled = true;
	}

}
