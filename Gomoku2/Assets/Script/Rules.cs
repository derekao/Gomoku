using System.Collections;
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
	/// If there is 5 Stones aligned check if you can break the alignement or win eating stone
	/// </summary>
	static public void youWin(int Player, int Opponent, int y, int x) 
	{
		bool Break = breakWin(Player, Opponent, y, x);
		somethingToEatOnTheBoard(Opponent, Player);
		if ((Player & GameManager.Stone.White) == 0 && GameManager.Instance.currentState.hasWon && GameManager.Instance.currentState.WhiteScore < 10)
			GameManager.Instance.currentState.BlackWin = true;
		else if ((Player & GameManager.Stone.Black) == 0 && GameManager.Instance.currentState.hasWon && GameManager.Instance.currentState.BlackScore < 10)
			GameManager.Instance.currentState.WhiteWin = true;
		else if ((Player & GameManager.Stone.Black) != 0 && !Break && !(winByCapture() * 2 + GameManager.Instance.currentState.WhiteScore >= 10 ? true : false))
			GameManager.Instance.currentState.BlackWin = true;
		else if ((Player & GameManager.Stone.White) != 0 && !Break && !(winByCapture() * 2 + GameManager.Instance.currentState.BlackScore >= 10 ? true : false))
			GameManager.Instance.currentState.WhiteWin = true;
		else {
			GameManager.Instance.currentState.hasWon = true;
			GameManager.Instance.currentState.winY = y;
			GameManager.Instance.currentState.winX = x;
		}
		GameManager.Instance.EatCoord.Clear();
	}

	// Private function used in YouWIn
	private static void registerEatCoord(int i, int j) 
	{
		int[] Coord = {i, j};
		GameManager.Instance.EatCoord.Insert(0, Coord);
	}

	// Private function used in YouWIn
	private static void somethingToEatWithPlayer(int Opponent, int i, int j)
	{
		if (i < GameManager.Instance.iHeightBoard - 3 && (GameManager.Instance.currentState.Board[i + 1, j] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i + 2, j] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i + 3, j])) // Bottom
			registerEatCoord(i + 3, j);
		if (j < GameManager.Instance.iWidthBoard - 3 && (GameManager.Instance.currentState.Board[i, j + 1] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i, j + 2] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i, j + 3])) // Right
			registerEatCoord(i, j + 3);
		if (i >= 3 && j < GameManager.Instance.iWidthBoard - 3 && (GameManager.Instance.currentState.Board[i - 1, j + 1] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i - 2, j + 2] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i - 3, j + 3])) // Top Right
			registerEatCoord(i - 3, j + 3);
		if (i < GameManager.Instance.iHeightBoard - 3 && j < GameManager.Instance.iWidthBoard - 3 && (GameManager.Instance.currentState.Board[i + 1, j + 1] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i + 2, j + 2] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i + 3, j + 3])) // Bottom Right
			registerEatCoord(i + 3, j + 3);
		if (i >= 3 && j >= 3 && (GameManager.Instance.currentState.Board[i - 1, j - 1] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i - 2, j - 2] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i - 3, j - 3]))  // Top Left
			registerEatCoord(i - 3, j - 3);
		if (i >= 3 && (GameManager.Instance.currentState.Board[i - 1, j] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i - 2, j] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i - 3, j])) // Top
			registerEatCoord(i - 3, j);
		if (j >= 3 && (GameManager.Instance.currentState.Board[i, j - 1] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i, j - 2] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i, j - 3])) // Left
			registerEatCoord(i, j - 3);
		if (j >= 3 && i < GameManager.Instance.iHeightBoard - 3 && (GameManager.Instance.currentState.Board[i + 1, j - 1] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i + 2, j - 2] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i + 3, j - 3])) // Bottom Left
			registerEatCoord(i + 3, j - 3);
	}

	// Private function used in YouWIn
	static private void somethingToEatOnTheBoard(int Player, int Opponent)
	{
		for (int i = 0; i < GameManager.Instance.iHeightBoard; i++) {
			for (int j = 0; j < GameManager.Instance.iWidthBoard; j++) {
				if ((GameManager.Instance.currentState.Board[i, j] & Player) != 0) {
					somethingToEatWithPlayer(Opponent, i, j);
				}
			}
		}
	}

	// Private function used in YouWIn
	static private int winByCapture()
	{
		int y;
		int x;
		int points = 0;
		int tmpPoints;
		for (int i = 0; i < GameManager.Instance.EatCoord.Count;) {
			tmpPoints = 0;
			y = GameManager.Instance.EatCoord[i][0];
			x = GameManager.Instance.EatCoord[i][1];
			for (int j = i + 1; j < GameManager.Instance.EatCoord.Count;) {
				if ( GameManager.Instance.EatCoord[j][0] == y &&  GameManager.Instance.EatCoord[j][1] == x) {
					GameManager.Instance.EatCoord.RemoveAt(j);
					tmpPoints++;
				}
				else
					j++;
			}
			GameManager.Instance.EatCoord.RemoveAt(i);
			tmpPoints++;
			if (tmpPoints > points)
				points = tmpPoints;
		}
		GameManager.Instance.EatCoord.Clear();
		return points;
	}

	private static void canBeEat(int Player, int Opponent, int i, int j)
	{
		//Top
		if (i >= 2 && i < GameManager.Instance.iHeightBoard - 1 && (GameManager.Instance.currentState.Board[i - 1, j] & Player) != 0 && (GameManager.Instance.currentState.Board[i + 1, j] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i - 2, j])) 
			registerEatCoord(i - 2, j);
		if (i >= 1 && i < GameManager.Instance.iHeightBoard - 2 && (GameManager.Instance.currentState.Board[i + 1, j] & Player) != 0 && (GameManager.Instance.currentState.Board[i + 2, j] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i - 1, j]))
			registerEatCoord(i - 1, j);

		//Bottom
		if (i >= 2 && i < GameManager.Instance.iHeightBoard - 1 && (GameManager.Instance.currentState.Board[i - 1, j] & Player) != 0 && (GameManager.Instance.currentState.Board[i - 2, j] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i + 1, j])) 
			registerEatCoord(i + 1, j);
		if (i >= 1 && i < GameManager.Instance.iHeightBoard - 2 && (GameManager.Instance.currentState.Board[i + 1, j] & Player) != 0 && (GameManager.Instance.currentState.Board[i - 1, j] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i + 2, j]))
			registerEatCoord(i + 2, j);

		//Right
		if (j >= 1 && j < GameManager.Instance.iWidthBoard - 2 && (GameManager.Instance.currentState.Board[i, j + 1] & Player) != 0 && (GameManager.Instance.currentState.Board[i, j - 1] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i, j + 2]))
			registerEatCoord(i, j + 2);
		if (j >= 2 && j < GameManager.Instance.iWidthBoard - 1 && (GameManager.Instance.currentState.Board[i, j - 1] & Player) != 0 && (GameManager.Instance.currentState.Board[i, j - 2] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i, j + 1]))
			registerEatCoord(i, j + 1);

		//Left
		if (j >= 2 && j < GameManager.Instance.iWidthBoard - 1 && (GameManager.Instance.currentState.Board[i, j - 1] & Player) != 0 && (GameManager.Instance.currentState.Board[i, j + 1] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i, j - 2]))
			registerEatCoord(i, j - 2);
		if (j >= 1 && j < GameManager.Instance.iWidthBoard - 2 && (GameManager.Instance.currentState.Board[i, j + 1] & Player) != 0 && (GameManager.Instance.currentState.Board[i, j + 2] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i, j - 1]))
			registerEatCoord(i, j - 1);

		//Top-Right
		if (j >= 2 && j < GameManager.Instance.iWidthBoard - 1 && i >= 1 && i < GameManager.Instance.iHeightBoard - 2 && (GameManager.Instance.currentState.Board[i + 1, j - 1] & Player) != 0 && (GameManager.Instance.currentState.Board[i + 2, j - 2] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i - 1, j + 1]))
			registerEatCoord(i - 1, j + 1);
		if (j >= 1 && j < GameManager.Instance.iWidthBoard - 2 && i >= 2 && i < GameManager.Instance.iHeightBoard - 1 && (GameManager.Instance.currentState.Board[i - 1, j + 1] & Player) != 0 && (GameManager.Instance.currentState.Board[i + 1, j - 1] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i - 2, j + 2]))
			registerEatCoord(i - 2, j + 2);

		//Bot-Left
		if (j >= 2 && j < GameManager.Instance.iWidthBoard - 1 && i >= 1 && i < GameManager.Instance.iHeightBoard - 2 && (GameManager.Instance.currentState.Board[i + 1, j - 1] & Player) != 0 && (GameManager.Instance.currentState.Board[i - 1, j + 1] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i + 2, j - 2]))
			registerEatCoord(i + 2, j - 2);
		if (j >= 1 && j < GameManager.Instance.iWidthBoard - 2 && i >= 2 && i < GameManager.Instance.iHeightBoard - 1 && (GameManager.Instance.currentState.Board[i - 1, j + 1] & Player) != 0 && (GameManager.Instance.currentState.Board[i - 2, j + 2] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i + 1, j - 1]))
			registerEatCoord(i + 1, j - 1);

		//Top-Left
		if (j >= 1 && j < GameManager.Instance.iWidthBoard - 2 && i >= 1 && i < GameManager.Instance.iHeightBoard - 2 && (GameManager.Instance.currentState.Board[i + 1, j + 1] & Player) != 0 && (GameManager.Instance.currentState.Board[i + 2, j + 2] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i - 1, j - 1]))
			registerEatCoord(i - 1, j - 1);
		if (j >= 2 && j < GameManager.Instance.iWidthBoard - 1 && i >= 2 && i < GameManager.Instance.iHeightBoard - 1 && (GameManager.Instance.currentState.Board[i - 1, j - 1] & Player) != 0 && (GameManager.Instance.currentState.Board[i + 1, j + 1] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i - 2, j - 2]))
			registerEatCoord(i - 2, j - 2);

		//Bot-Right
		if (j >= 1 && j < GameManager.Instance.iWidthBoard - 2 && i >= 1 && i < GameManager.Instance.iHeightBoard - 2 && (GameManager.Instance.currentState.Board[i + 1, j + 1] & Player) != 0 && (GameManager.Instance.currentState.Board[i - 1, j - 1] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i + 2, j + 2]))
			registerEatCoord(i + 2, j + 2);
		if (j >= 2 && j < GameManager.Instance.iWidthBoard - 1 && i >= 2 && i < GameManager.Instance.iHeightBoard - 1 && (GameManager.Instance.currentState.Board[i - 1, j - 1] & Player) != 0 && (GameManager.Instance.currentState.Board[i - 2, j - 2] & Opponent) != 0 && EmptyCase(GameManager.Instance.currentState.Board[i + 1, j + 1]))
			registerEatCoord(i + 1, j + 1);

	}


	/// <summary>
	/// Return True if the Cell [i,j] allow you yo eat Opponent Stones
	/// </summary>
	public static bool somethingToEatWithEmpty(int Player, int Opponent, int i, int j)
	{
		bool canEat = false;
		if (i < GameManager.Instance.iHeightBoard - 3 && (GameManager.Instance.currentState.Board[i + 1, j] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i + 2, j] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i + 3, j] & Player) != 0) // Bottom
			canEat = true;
		if (j < GameManager.Instance.iWidthBoard - 3 && (GameManager.Instance.currentState.Board[i, j + 1] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i, j + 2] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i, j + 3] & Player) != 0) // Right
			canEat = true;
		if (i >= 3 && j < GameManager.Instance.iWidthBoard - 3 && (GameManager.Instance.currentState.Board[i - 1, j + 1] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i - 2, j + 2] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i - 3, j + 3] & Player) != 0) // Top Right
			canEat = true;
		if (i < GameManager.Instance.iHeightBoard - 3 && j < GameManager.Instance.iWidthBoard - 3 && (GameManager.Instance.currentState.Board[i + 1, j + 1] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i + 2, j + 2] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i + 3, j + 3] & Player) != 0) // Bottom Right
			canEat = true;
		if (i >= 3 && j >= 3 && (GameManager.Instance.currentState.Board[i - 1, j - 1] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i - 2, j - 2] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i - 3, j - 3] & Player) != 0)  //  Top Left
			canEat = true;
		if (i >= 3 && (GameManager.Instance.currentState.Board[i - 1, j] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i - 2, j] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i - 3, j] & Player) != 0) // Top
			canEat = true;
		if (j >= 3 && (GameManager.Instance.currentState.Board[i, j - 1] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i, j - 2] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i, j - 3] & Player) != 0) // Left
			canEat = true;
		if (j >= 3 && i < GameManager.Instance.iHeightBoard - 3 && (GameManager.Instance.currentState.Board[i + 1, j - 1] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i + 2, j - 2] & Opponent) != 0 && (GameManager.Instance.currentState.Board[i + 3, j - 3] & Player) != 0) // Bottom Left
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

		if (GameManager.Instance.currentState.bPlayerOneTurn)
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
					if ((GameManager.Instance.currentState.Board[i, j] & GameManager.Stone.Black) != 0)
					{
						changeBoxState(j, i, PlayStone.Type.Black);
					}
					else if ((GameManager.Instance.currentState.Board[i, j] & GameManager.Stone.White) != 0)
					{
						changeBoxState(j, i, PlayStone.Type.White);
					}
					else 
					{
						changeBoxState(j, i, PlayStone.Type.Empty);
					}
				}
				if ((GameManager.Instance.currentState.Board[i, j] & Forbidden) != 0)
				{
					changeBoxState(j, i, PlayStone.Type.Forbidden);
				}
				else if ((GameManager.Instance.currentState.Board[i, j] & ForbiddenOther) != 0)
				{
					changeBoxState(j, i, PlayStone.Type.Empty);
				}

				if ((GameManager.Instance.currentState.Board[i, j] & DoubleTree) != 0)
				{
					changeBoxState(j, i, PlayStone.Type.DoubleTree);
				}
				else if ((GameManager.Instance.currentState.Board[i, j] & DoubleTreeOther) != 0)
				{
					changeBoxState(j, i, PlayStone.Type.Empty);
				}
			}
		}
	}

	// Fill Forbidden cell on the GameManager.currentState.Board
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

		if ((GameManager.Instance.currentState.Board[Height, Width] & Player) == 0)
		{
			GameManager.Instance.currentState.Board[Height, Width] += Player;
		}
		return false;
		
	}

	/// <summary>
	/// Return True if there is a double tree on the cell [y,x]
	/// </summary>
	static public bool checkDoubleTreeBox(int y, int x, int Player1)
	{
		int NumTree = 0;

		//  - X 0 X -
		if (x >= 2 && x < GameManager.Instance.iWidthBoard - 2 && EmptyCase(GameManager.Instance.currentState.Board[y, x - 2]) && GameManager.Instance.currentState.Board[y, x - 1] == Player1 && GameManager.Instance.currentState.Board[y, x + 1] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y, x + 2]))
			NumTree++;
		if (y >= 2 && y < GameManager.Instance.iHeightBoard - 2 && EmptyCase(GameManager.Instance.currentState.Board[y - 2, x]) && GameManager.Instance.currentState.Board[y - 1, x] == Player1 && GameManager.Instance.currentState.Board[y + 1, x] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y + 2, x]))
			NumTree++;
		if (x >= 2 && x < GameManager.Instance.iWidthBoard - 2  && y >= 2 && y < GameManager.Instance.iHeightBoard - 2
			&& EmptyCase(GameManager.Instance.currentState.Board[y - 2, x - 2]) && GameManager.Instance.currentState.Board[y - 1, x - 1] == Player1 && GameManager.Instance.currentState.Board[y + 1, x + 1] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y + 2, x + 2]))
			NumTree++;
		if (x >= 2 && x < GameManager.Instance.iWidthBoard - 2 && y >= 2 && y < GameManager.Instance.iHeightBoard - 2
			&& EmptyCase(GameManager.Instance.currentState.Board[y + 2, x - 2]) && GameManager.Instance.currentState.Board[y + 1, x - 1] == Player1 && GameManager.Instance.currentState.Board[y - 1, x + 1] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y - 2, x + 2]))
			NumTree++;

		// - X X 0 -
		if (x >= 3 && x < GameManager.Instance.iWidthBoard - 1 && EmptyCase(GameManager.Instance.currentState.Board[y, x - 3]) && GameManager.Instance.currentState.Board[y, x - 2] == Player1 && GameManager.Instance.currentState.Board[y, x - 1] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y, x + 1]))
			NumTree++;
		if (x >= 1 && x < GameManager.Instance.iWidthBoard - 3 && EmptyCase(GameManager.Instance.currentState.Board[y, x - 1]) && GameManager.Instance.currentState.Board[y, x + 1] == Player1 && GameManager.Instance.currentState.Board[y, x + 2] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y, x + 3]))
			NumTree++;
		if (y >= 3 && y < GameManager.Instance.iHeightBoard - 1 && EmptyCase(GameManager.Instance.currentState.Board[y - 3, x]) && GameManager.Instance.currentState.Board[y - 2, x] == Player1 && GameManager.Instance.currentState.Board[y - 1, x] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y + 1, x]))
			NumTree++;
		if (y >= 1 && y < GameManager.Instance.iHeightBoard - 3 && EmptyCase(GameManager.Instance.currentState.Board[y - 1, x]) && GameManager.Instance.currentState.Board[y + 1, x] == Player1 && GameManager.Instance.currentState.Board[y + 2, x] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y + 3, x]))
			NumTree++;
		if (x >= 3 && x < GameManager.Instance.iWidthBoard - 1 && y >= 3 && y < GameManager.Instance.iHeightBoard - 1
			&& EmptyCase(GameManager.Instance.currentState.Board[y - 3, x - 3]) && GameManager.Instance.currentState.Board[y - 2, x - 2] == Player1 && GameManager.Instance.currentState.Board[y - 1, x - 1] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y + 1, x + 1]))
			NumTree++;
		if (x >= 1 && x < GameManager.Instance.iWidthBoard - 3 && y >= 1 && y < GameManager.Instance.iHeightBoard - 3 
			&& EmptyCase(GameManager.Instance.currentState.Board[y - 1, x - 1]) && GameManager.Instance.currentState.Board[y + 1, x + 1] == Player1 && GameManager.Instance.currentState.Board[y + 2, x + 2] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y + 3, x + 3]))
			NumTree++;
		if (x >= 3 && x < GameManager.Instance.iWidthBoard - 1 && y >= 1 && y < GameManager.Instance.iHeightBoard - 3 
			&& EmptyCase(GameManager.Instance.currentState.Board[y + 3, x - 3]) && GameManager.Instance.currentState.Board[y + 2, x - 2] == Player1 && GameManager.Instance.currentState.Board[y + 1, x - 1] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y - 1, x + 1]))
			NumTree++;
		if (x >= 1 && x < GameManager.Instance.iWidthBoard - 3 && y >= 3 && y < GameManager.Instance.iHeightBoard - 1
			&& EmptyCase(GameManager.Instance.currentState.Board[y + 1, x - 1]) && GameManager.Instance.currentState.Board[y - 1, x + 1] == Player1 && GameManager.Instance.currentState.Board[y - 2, x + 2] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y - 3, x + 3]))
			NumTree++;

		// - X X - 0 -
		if (x >= 4 && x < GameManager.Instance.iWidthBoard - 1 && EmptyCase(GameManager.Instance.currentState.Board[y, x - 4]) && GameManager.Instance.currentState.Board[y, x - 3] == Player1 && GameManager.Instance.currentState.Board[y, x - 2] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y, x - 1])  && EmptyCase(GameManager.Instance.currentState.Board[y, x + 1]))
			NumTree++;
		if (x >= 1 && x < GameManager.Instance.iWidthBoard - 4 && EmptyCase(GameManager.Instance.currentState.Board[y, x + 4]) && GameManager.Instance.currentState.Board[y, x + 3] == Player1 && GameManager.Instance.currentState.Board[y, x + 2] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y, x + 1])  && EmptyCase(GameManager.Instance.currentState.Board[y, x - 1]))
			NumTree++;
		if (y >= 4 && y < GameManager.Instance.iHeightBoard - 1 && EmptyCase(GameManager.Instance.currentState.Board[y - 4, x]) && GameManager.Instance.currentState.Board[y - 3, x] == Player1 && GameManager.Instance.currentState.Board[y - 2, x] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y - 1, x])  && EmptyCase(GameManager.Instance.currentState.Board[y + 1, x]))
			NumTree++;
		if (y >= 1 && y < GameManager.Instance.iHeightBoard - 4 && EmptyCase(GameManager.Instance.currentState.Board[y + 4, x]) && GameManager.Instance.currentState.Board[y + 3, x] == Player1 && GameManager.Instance.currentState.Board[y + 2, x] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y + 1, x])  && EmptyCase(GameManager.Instance.currentState.Board[y - 1, x]))
			NumTree++;
		if (x >= 4 && x < GameManager.Instance.iWidthBoard - 1 && y >= 4 && y < GameManager.Instance.iHeightBoard - 1
			&& EmptyCase(GameManager.Instance.currentState.Board[y - 4, x - 4]) && GameManager.Instance.currentState.Board[y - 3, x - 3] == Player1 && GameManager.Instance.currentState.Board[y - 2, x - 2] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y - 1, x - 1])  && EmptyCase(GameManager.Instance.currentState.Board[y + 1, x + 1]))
			NumTree++;
		if (x >= 1 && x < GameManager.Instance.iWidthBoard - 4 && y >= 1 && y < GameManager.Instance.iHeightBoard - 4
			&& EmptyCase(GameManager.Instance.currentState.Board[y + 4, x + 4]) && GameManager.Instance.currentState.Board[y + 3, x + 3] == Player1 && GameManager.Instance.currentState.Board[y + 2, x + 2] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y + 1, x + 1])  && EmptyCase(GameManager.Instance.currentState.Board[y - 1, x - 1]))
			NumTree++;
		if (x >= 4 && x < GameManager.Instance.iWidthBoard - 1 && y >= 1 && y < GameManager.Instance.iHeightBoard - 4
			&& EmptyCase(GameManager.Instance.currentState.Board[y + 4, x - 4]) && GameManager.Instance.currentState.Board[y + 3, x - 3] == Player1 && GameManager.Instance.currentState.Board[y + 2, x - 2] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y + 1, x - 1])  && EmptyCase(GameManager.Instance.currentState.Board[y - 1, x + 1]))
			NumTree++;
		if (x >= 1 && x < GameManager.Instance.iWidthBoard - 4 && y >= 4 && y < GameManager.Instance.iHeightBoard - 1
			&& EmptyCase(GameManager.Instance.currentState.Board[y - 4, x + 4]) && GameManager.Instance.currentState.Board[y - 3, x + 3] == Player1 && GameManager.Instance.currentState.Board[y - 2, x + 2] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y - 1, x + 1])  && EmptyCase(GameManager.Instance.currentState.Board[y + 1, x - 1]))
			NumTree++;

		// - X - X 0 -
		if (x >= 4 && x < GameManager.Instance.iWidthBoard - 1 && EmptyCase(GameManager.Instance.currentState.Board[y, x - 4]) && GameManager.Instance.currentState.Board[y, x - 3] == Player1 && GameManager.Instance.currentState.Board[y, x - 1] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y, x - 2])  && EmptyCase(GameManager.Instance.currentState.Board[y, x + 1]))
			NumTree++;
		if (x >= 1 && x < GameManager.Instance.iWidthBoard - 4 && EmptyCase(GameManager.Instance.currentState.Board[y, x + 4]) && GameManager.Instance.currentState.Board[y, x + 3] == Player1 && GameManager.Instance.currentState.Board[y, x + 1] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y, x + 2])  && EmptyCase(GameManager.Instance.currentState.Board[y, x - 1]))
			NumTree++;
		if (y >= 4 && y < GameManager.Instance.iHeightBoard - 1 && EmptyCase(GameManager.Instance.currentState.Board[y - 4, x]) && GameManager.Instance.currentState.Board[y - 3, x] == Player1 && GameManager.Instance.currentState.Board[y - 1, x] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y - 2, x])  && EmptyCase(GameManager.Instance.currentState.Board[y + 1, x]))
			NumTree++;
		if (y >= 1 && y < GameManager.Instance.iHeightBoard - 4 && EmptyCase(GameManager.Instance.currentState.Board[y + 4, x]) && GameManager.Instance.currentState.Board[y + 3, x] == Player1 && GameManager.Instance.currentState.Board[y + 1, x] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y + 2, x])  && EmptyCase(GameManager.Instance.currentState.Board[y - 1, x]))
			NumTree++;
		if (x >= 4 && x < GameManager.Instance.iWidthBoard - 1 && y >= 4 && y < GameManager.Instance.iHeightBoard - 1
			&& EmptyCase(GameManager.Instance.currentState.Board[y - 4, x - 4]) && GameManager.Instance.currentState.Board[y - 3, x - 3] == Player1 && GameManager.Instance.currentState.Board[y - 1, x - 1] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y - 2, x - 2])  && EmptyCase(GameManager.Instance.currentState.Board[y + 1, x + 1]))
			NumTree++;
		if (x >= 1 && x < GameManager.Instance.iWidthBoard - 4 && y >= 1 && y < GameManager.Instance.iHeightBoard - 4
			&& EmptyCase(GameManager.Instance.currentState.Board[y + 4, x + 4]) && GameManager.Instance.currentState.Board[y + 3, x + 3] == Player1 && GameManager.Instance.currentState.Board[y + 1, x + 1] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y + 2, x + 2])  && EmptyCase(GameManager.Instance.currentState.Board[y - 1, x - 1]))
			NumTree++;
		if (x >= 4 && x < GameManager.Instance.iWidthBoard - 1 && y >= 1 && y < GameManager.Instance.iHeightBoard - 4
			&& EmptyCase(GameManager.Instance.currentState.Board[y + 4, x - 4]) && GameManager.Instance.currentState.Board[y + 3, x - 3] == Player1 && GameManager.Instance.currentState.Board[y + 1, x - 1] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y + 2, x - 2])  && EmptyCase(GameManager.Instance.currentState.Board[y - 1, x + 1]))
			NumTree++;
		if (x >= 1 && x < GameManager.Instance.iWidthBoard - 4 && y >= 4 && y < GameManager.Instance.iHeightBoard - 1
			&& EmptyCase(GameManager.Instance.currentState.Board[y - 4, x + 4]) && GameManager.Instance.currentState.Board[y - 3, x + 3] == Player1 && GameManager.Instance.currentState.Board[y - 1, x + 1] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y - 2, x + 2])  && EmptyCase(GameManager.Instance.currentState.Board[y + 1, x - 1]))
			NumTree++;

		//  - X - 0 X -
		if (x >= 3 && x < GameManager.Instance.iWidthBoard - 2 && EmptyCase(GameManager.Instance.currentState.Board[y, x - 3]) && GameManager.Instance.currentState.Board[y, x - 2] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y, x - 1]) && GameManager.Instance.currentState.Board[y, x + 1] == Player1  && EmptyCase(GameManager.Instance.currentState.Board[y, x + 2]))
			NumTree++;
		if (x >= 2 && x < GameManager.Instance.iWidthBoard - 3 && EmptyCase(GameManager.Instance.currentState.Board[y, x + 3]) && GameManager.Instance.currentState.Board[y, x + 2] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y, x + 1]) && GameManager.Instance.currentState.Board[y, x - 1] == Player1  && EmptyCase(GameManager.Instance.currentState.Board[y, x - 2]))
			NumTree++;
		if (y >= 3 && y < GameManager.Instance.iHeightBoard - 2 && EmptyCase(GameManager.Instance.currentState.Board[y - 3, x]) && GameManager.Instance.currentState.Board[y - 2, x] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y - 1, x]) && GameManager.Instance.currentState.Board[y + 1, x] == Player1  && EmptyCase(GameManager.Instance.currentState.Board[y + 2, x]))
			NumTree++;
		if (y >= 2 && y < GameManager.Instance.iHeightBoard - 3 && EmptyCase(GameManager.Instance.currentState.Board[y + 3, x]) && GameManager.Instance.currentState.Board[y + 2, x] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y + 1, x]) && GameManager.Instance.currentState.Board[y - 1, x] == Player1  && EmptyCase(GameManager.Instance.currentState.Board[y - 2, x]))
			NumTree++;
		if (x >= 3 && x < GameManager.Instance.iWidthBoard - 2 && y >= 3 && y < GameManager.Instance.iHeightBoard - 2
			&& EmptyCase(GameManager.Instance.currentState.Board[y - 3, x - 3]) && GameManager.Instance.currentState.Board[y - 2, x - 2] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y - 1, x - 1]) && GameManager.Instance.currentState.Board[y + 1, x + 1] == Player1  && EmptyCase(GameManager.Instance.currentState.Board[y + 2, x + 2]))
			NumTree++;
		if (x >= 2 && x < GameManager.Instance.iWidthBoard - 3 && y >= 2 && y < GameManager.Instance.iHeightBoard - 3
			&& EmptyCase(GameManager.Instance.currentState.Board[y + 3, x + 3]) && GameManager.Instance.currentState.Board[y + 2, x + 2] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y + 1, x + 1]) && GameManager.Instance.currentState.Board[y - 1, x - 1] == Player1  && EmptyCase(GameManager.Instance.currentState.Board[y - 2, x - 2]))
			NumTree++;
		if (x >= 3 && x < GameManager.Instance.iWidthBoard - 2 && y >= 2 && y < GameManager.Instance.iHeightBoard - 3
			&& EmptyCase(GameManager.Instance.currentState.Board[y + 3, x - 3]) && GameManager.Instance.currentState.Board[y + 2, x - 2] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y + 1, x - 1]) && GameManager.Instance.currentState.Board[y - 1, x + 1] == Player1  && EmptyCase(GameManager.Instance.currentState.Board[y - 2, x + 2]))
			NumTree++;
		if (x >= 2 && x < GameManager.Instance.iWidthBoard - 3 && y >= 3 && y < GameManager.Instance.iHeightBoard - 2
			&& EmptyCase(GameManager.Instance.currentState.Board[y - 3, x + 3]) && GameManager.Instance.currentState.Board[y - 2, x + 2] == Player1 && EmptyCase(GameManager.Instance.currentState.Board[y - 1, x + 1]) && GameManager.Instance.currentState.Board[y + 1, x - 1] == Player1  && EmptyCase(GameManager.Instance.currentState.Board[y + 2, x - 2]))
			NumTree++;

		if (NumTree >= 2)
		{
			if (!GameManager.Instance.currentState.bPlayerOneTurn && (GameManager.Instance.currentState.Board[y, x] & GameManager.Stone.BlackDoubleTree) == 0)
				GameManager.Instance.currentState.Board[y, x] += GameManager.Stone.BlackDoubleTree;
			else if (GameManager.Instance.currentState.bPlayerOneTurn && (GameManager.Instance.currentState.Board[y, x] & GameManager.Stone.WhiteDoubleTree) == 0)
				GameManager.Instance.currentState.Board[y, x] += GameManager.Stone.WhiteDoubleTree;
			return true;
		}
		else 
		{
			if ((GameManager.Instance.currentState.Board[y, x] & GameManager.Stone.WhiteDoubleTree) != 0 && Player1 == GameManager.Stone.White)
				GameManager.Instance.currentState.Board[y, x] -= GameManager.Stone.WhiteDoubleTree;
			if ((GameManager.Instance.currentState.Board[y, x] & GameManager.Stone.BlackDoubleTree) != 0 && Player1 == GameManager.Stone.Black)
				GameManager.Instance.currentState.Board[y, x] -= GameManager.Stone.BlackDoubleTree;
			return false;
		}
	}

	/// <summary>
	/// Return True [y,x] is Forbidden due to capture
	/// </summary>
	static public void checkForbiddenBox(int y, int x) {

		int Player1;
		int Player2;

		if (GameManager.Instance.currentState.bPlayerOneTurn)
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
			if (GameManager.Instance.currentState.Board[y, x - 1] == Player2 && GameManager.Instance.currentState.Board[y, x + 1] == Player1 && GameManager.Instance.currentState.Board[y, x + 2] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.Instance.currentState.bPlayerOneTurn);
		}
		if (x < GameManager.Instance.iWidthBoard - 1 && x >= 2) // Droite
		{
			if (GameManager.Instance.currentState.Board[y, x - 2] == Player2 && GameManager.Instance.currentState.Board[y, x - 1] == Player1 && GameManager.Instance.currentState.Board[y, x + 1] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.Instance.currentState.bPlayerOneTurn);
		}
		if (y >= 1 && y < GameManager.Instance.iHeightBoard - 2) // Haut
		{
			if (GameManager.Instance.currentState.Board[y - 1, x] == Player2 && GameManager.Instance.currentState.Board[y + 1, x] == Player1 && GameManager.Instance.currentState.Board[y + 2, x] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.Instance.currentState.bPlayerOneTurn);
		}
		if (y < GameManager.Instance.iHeightBoard - 1 && y >= 2) // Bas
		{
			if (GameManager.Instance.currentState.Board[y - 2, x] == Player2 && GameManager.Instance.currentState.Board[y - 1, x] == Player1 && GameManager.Instance.currentState.Board[y + 1, x] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.Instance.currentState.bPlayerOneTurn);
		}
		if (x >= 1 && y >= 1 && y < GameManager.Instance.iHeightBoard - 2 && x < GameManager.Instance.iWidthBoard - 2) // Haut Gauche
		{
			if (GameManager.Instance.currentState.Board[y - 1, x - 1] == Player2 && GameManager.Instance.currentState.Board[y + 1, x + 1] == Player1 && GameManager.Instance.currentState.Board[y + 2, x + 2] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.Instance.currentState.bPlayerOneTurn);
		}
		if (x >= 1 && y < GameManager.Instance.iHeightBoard - 1 && x < GameManager.Instance.iWidthBoard - 2 && y >= 2) // Bas Gauche
		{
			if (GameManager.Instance.currentState.Board[y + 1, x - 1] == Player2 && GameManager.Instance.currentState.Board[y - 1, x + 1] == Player1 && GameManager.Instance.currentState.Board[y - 2, x + 2] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.Instance.currentState.bPlayerOneTurn);
		}
		if (x < GameManager.Instance.iWidthBoard - 1 && y >= 1 && x >= 2 && y < GameManager.Instance.iHeightBoard - 2) // Haut Droite
		{
			if (GameManager.Instance.currentState.Board[y - 1, x + 1] == Player2 && GameManager.Instance.currentState.Board[y + 1, x - 1] == Player1 && GameManager.Instance.currentState.Board[y + 2, x - 2] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.Instance.currentState.bPlayerOneTurn);
		}
		if (x < GameManager.Instance.iWidthBoard - 1 && y < GameManager.Instance.iHeightBoard - 1 && x >= 2 && y >= 2) // Bas Droite
		{
			if (GameManager.Instance.currentState.Board[y + 1, x + 1] == Player2 && GameManager.Instance.currentState.Board[y - 1, x - 1] == Player1 && GameManager.Instance.currentState.Board[y - 2, x - 2] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.Instance.currentState.bPlayerOneTurn);
		}
		if (bEmpty)
		{
			GameManager.Instance.currentState.Board[y, x] = GameManager.Stone.Empty;
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
			GameManager.Instance.currentState.Board[Height, Width] = GameManager.Stone.Empty;
			if (GameManager.Instance.currentState.bPlayerOneTurn)
			{
				GameManager.Instance.currentState.BlackScore++;
				tmpWhiteStoneImage.enabled = false;
			}
			else
			{
				GameManager.Instance.currentState.WhiteScore++;
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

	static private void checkBreak(int lstSize, bool first = false) 
	{
		int y;
		int x;
		int doublon;
		for (int i = 0; i < GameManager.Instance.EatCoord.Count;) {
			doublon = 0;
			y = GameManager.Instance.EatCoord[i][0];
			x = GameManager.Instance.EatCoord[i][1];
			for (int j = i + 1; j < GameManager.Instance.EatCoord.Count;) {
				if ( GameManager.Instance.EatCoord[j][0] == y &&  GameManager.Instance.EatCoord[j][1] == x) {
					GameManager.Instance.EatCoord.RemoveAt(j);
					doublon++;
				}
				else
					j++;
			}
			if (!first && doublon == 0)
				GameManager.Instance.EatCoord.RemoveAt(i);
			else
				i++;
		}
	}

	static private bool breakWin(int Player, int Opponent, int y, int x) 
	{
		int Align = 1;
		int nbAlign = 0;
		int i = y;
		int j = x + 1;
		int lstSize = 0;
		bool stillBreakable;

		canBeEat(Player, Opponent, y, x);
		if (GameManager.Instance.EatCoord.Count > 0) {
			GameManager.Instance.EatCoord.Clear();
			return true;
		}
		//Horizontal
		while (j < GameManager.Instance.iWidthBoard && GameManager.Instance.currentState.Board[i,j] == Player)
		{
			canBeEat(Player, Opponent, i, j);
			j++;
			Align++;
		}
		j = x - 1;
		while (j >= 0 && GameManager.Instance.currentState.Board[i,j] == Player)
		{
			canBeEat(Player, Opponent, i, j);
			j--;
			Align++;
		}
		if (Align >= 5) {
			checkBreak(lstSize, (nbAlign == 0 ? true : false));
			lstSize = GameManager.Instance.EatCoord.Count;
			nbAlign++;
		}
		else {
			GameManager.Instance.EatCoord.RemoveRange(0, GameManager.Instance.EatCoord.Count - lstSize );
		}

		Align = 1;
		i = y + 1;
		j = x;
		//Vertical
		while (i < GameManager.Instance.iHeightBoard && GameManager.Instance.currentState.Board[i,j] == Player)
		{
			canBeEat(Player, Opponent, i, j);
			i++;
			Align++;
		}
		i = y - 1;
		while (i >= 0 && GameManager.Instance.currentState.Board[i,j] == Player)
		{
			canBeEat(Player, Opponent, i, j);
			i--;
			Align++;
		}
		if (Align >= 5) {
			checkBreak(lstSize, (nbAlign == 0 ? true : false));
			lstSize = GameManager.Instance.EatCoord.Count;
			nbAlign++;
		}
		else {
			GameManager.Instance.EatCoord.RemoveRange(0, GameManager.Instance.EatCoord.Count - lstSize );
		}

		Align = 1;
		i = y + 1;
		j = x + 1;
	
		//Diagonal Top->Bottom
		while (i < GameManager.Instance.iHeightBoard && j < GameManager.Instance.iWidthBoard && GameManager.Instance.currentState.Board[i,j] == Player)
		{
			canBeEat( Player, Opponent,  i, j);
			i++;
			j++;
			Align++;
		}
		i = y - 1;
		j = x - 1;
		while (i >= 0 && j >= 0 && GameManager.Instance.currentState.Board[i,j] == Player)
		{
			canBeEat(Player, Opponent, i, j);
			i--;
			j--;
			Align++;
		}
		if (Align >= 5) {
			checkBreak(lstSize, (nbAlign == 0 ? true : false));
			lstSize = GameManager.Instance.EatCoord.Count;
			nbAlign++;
		}
		else {
			GameManager.Instance.EatCoord.RemoveRange(0, GameManager.Instance.EatCoord.Count - lstSize );
		}

		Align = 1;
		i = y + 1;
		j = x - 1;
		//Diagonal Bottom->Top
		while (i < GameManager.Instance.iHeightBoard && j >= 0 && GameManager.Instance.currentState.Board[i,j] == Player)
		{
			canBeEat(Player, Opponent, i, j);
			i++;
			j--;
			Align++;			
		}
		i = y - 1;
		j = x + 1;
		while (j < GameManager.Instance.iWidthBoard && i >= 0 && GameManager.Instance.currentState.Board[i,j] == Player)
		{
			canBeEat(Player, Opponent, i, j);
			i--;
			j++;
			Align++;
			
		}
		if (Align >= 5) {
			checkBreak(lstSize, (nbAlign == 0 ? true : false));
			lstSize = GameManager.Instance.EatCoord.Count;
			nbAlign++;
		}
		else {
			GameManager.Instance.EatCoord.RemoveRange(0, GameManager.Instance.EatCoord.Count - lstSize );
		}
		stillBreakable = GameManager.Instance.EatCoord.Count > 0 ? true : false;
		GameManager.Instance.EatCoord.Clear();
		return stillBreakable;
	}

	/// <summary>
	/// Return the number of 5 Aligned stone around [y,x] (Max 4)
	/// </summary>
	static public int CheckWin(int Player, int y, int x)
	{
		int Align = 1;
		int nbAlign = 0;
		int i = y;
		int j = x + 1;
	
		if ((GameManager.Instance.currentState.Board[y, x] & Player) == 0)
			return 0;
		//Horizontal
		while (j < GameManager.Instance.iWidthBoard && GameManager.Instance.currentState.Board[i,j] == Player)
		{
			j++;
			Align++;
		}
		j = x - 1;
		while (j >= 0 && GameManager.Instance.currentState.Board[i,j] == Player)
		{
			j--;
			Align++;
		}

		if (Align >= 5)
			nbAlign++;

		Align = 1;
		i = y + 1;
		j = x;

		//Vertical
		while (i < GameManager.Instance.iHeightBoard && GameManager.Instance.currentState.Board[i,j] == Player)
		{
			i++;
			Align++;
		}
		i = y - 1;
		while (i >= 0 && GameManager.Instance.currentState.Board[i,j] == Player)
		{
			i--;
			Align++;
		}

		if (Align >= 5)
			nbAlign++;

		Align = 1;
		i = y + 1;
		j = x + 1;
	
		//Diagonal Top->Bottom
		while (i < GameManager.Instance.iHeightBoard && j < GameManager.Instance.iWidthBoard && GameManager.Instance.currentState.Board[i,j] == Player)
		{
			i++;
			j++;
			Align++;
		}
		i = y - 1;
		j = x - 1;
		while (i >= 0 && j >= 0 && GameManager.Instance.currentState.Board[i,j] == Player)
		{
			i--;
			j--;
			Align++;
		}

		if (Align >= 5)
			nbAlign++;

		Align = 1;
		i = y + 1;
		j = x - 1;
		//Diagonal Bottom->Top
		while (i < GameManager.Instance.iHeightBoard && j >= 0 && GameManager.Instance.currentState.Board[i,j] == Player)
		{
			i++;
			j--;
			Align++;
		}
		i = y - 1;
		j = x + 1;
		while (j < GameManager.Instance.iWidthBoard && i >= 0 && GameManager.Instance.currentState.Board[i,j] == Player)
		{
			i--;
			j++;
			Align++;
		}

		if (Align >= 5)
			nbAlign++;
		return nbAlign;
	}

}
