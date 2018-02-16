using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayStone : MonoBehaviour {

	private enum Type { Empty, Black, White, Eat, DoubleTree, Forbidden };
	private GameObject BlackStone;
	private GameObject WhiteStone;
	private GameObject Forbidden;
	private GameObject DoubleTree;
	private Image BlackStoneImage;
	private Image WhiteStoneImage;
	private Image ForbiddenImage;
	private Image DoubleTreeImage;

	private int x;
	private int y;

	void Start() {

		for (int i = 0; i < this.transform.childCount; i++)
		{
			Transform result = this.transform.GetChild(i);
			if (result.name == "BlackStone")
			{
				BlackStone = result.gameObject;
				BlackStoneImage = BlackStone.GetComponent<Image>();
			}
			else if (result.name == "WhiteStone")
			{
				WhiteStone = result.gameObject;
				WhiteStoneImage = WhiteStone.GetComponent<Image>();
			}
			else if (result.name == "Forbiden")
			{
				Forbidden = result.gameObject;
				ForbiddenImage = Forbidden.GetComponent<Image>();
			}
			else if (result.name == "DoubleTree")
			{
				DoubleTree = result.gameObject;
				DoubleTreeImage = DoubleTree.GetComponent<Image>();
			}
		}
		if (!BlackStoneImage || !WhiteStoneImage || !ForbiddenImage || !DoubleTreeImage)
		{
			Debug.Log("Wrong Stone Init 1" + name);
		}

		string szIndex = this.name.Substring(7, name.Length - 8);
		int iIndex = int.Parse(szIndex) - 1;
		y = iIndex / GameManager.iHeightBoard;
		x = iIndex % GameManager.iWidthBoard;

	}

	public void OnClick() {
		if (GameManager.bPlayerOneTurn) {
			OnBlackPlay();
		}
		else {
			OnWhitePlay();
		}
	}

	private void OnBlackPlay() {

		if (!WhiteStoneImage.enabled && !BlackStoneImage.enabled && !ForbiddenImage.enabled && !DoubleTreeImage.enabled) 
		{
			checkStoneEaten();
			BlackStoneImage.enabled = true;
			GameManager.bPlayerOneTurn = false;
			GameManager.Board[y, x] = GameManager.Stone.Black;
			int[,] tmpArray = GameManager.Board.Clone() as int[,];
			GameManager.lBoardHisto.Insert(0, tmpArray);
			GameManager.iTurn += 1;
			CheckWin(GameManager.Stone.Black);
			checkBoardState(y, x);
			DisplayBoard();
		}

	}

	private void OnWhitePlay() {

		if (!WhiteStoneImage.enabled && !BlackStoneImage.enabled && !ForbiddenImage.enabled && !DoubleTreeImage.enabled)
		{
			checkStoneEaten();
			WhiteStoneImage.enabled = true;
			GameManager.bPlayerOneTurn = true;
			GameManager.Board[y, x] = GameManager.Stone.White;
			int[,] tmpArray = GameManager.Board.Clone() as int[,];
			GameManager.lBoardHisto.Insert(0, tmpArray);
			GameManager.iTurn += 1;
			CheckWin(GameManager.Stone.White);
			checkBoardState(y, x);
			DisplayBoard();
		}

	}

	private bool somethingToEat(int Player, int Opponent)
	{
		bool canEat = false;
		for (int i = 0; i < GameManager.iHeightBoard; i++) {
			for (int j = 0; j < GameManager.iWidthBoard; j++) {
				if ((GameManager.Board[i, j] & Player) != 0) {
					if (i < GameManager.iHeightBoard - 3 && (GameManager.Board[i + 1, j] & Opponent) != 0 && (GameManager.Board[i + 2, j] & Opponent) != 0 && GameManager.Board[i + 3, j] == 0) // Bas
						canEat = true;
					if (j < GameManager.iWidthBoard - 3 && (GameManager.Board[i, j + 1] & Opponent) != 0 && (GameManager.Board[i, j + 2] & Opponent) != 0 && GameManager.Board[i, j + 3] == 0) // Droite
						canEat = true;
					if (i > 3 && j < GameManager.iWidthBoard - 3 && (GameManager.Board[i - 1, j + 1] & Opponent) != 0 && (GameManager.Board[i - 2, j + 2] & Opponent) != 0 && GameManager.Board[i - 3, j + 3] == 0) // Haut droite
						canEat = true;
					if (i < GameManager.iHeightBoard - 3 && j < GameManager.iWidthBoard - 3 && (GameManager.Board[i + 1, j + 1] & Opponent) != 0 && (GameManager.Board[i + 2, j + 2] & Opponent) != 0 && GameManager.Board[i + 3, j + 3] == 0) // Bas Droite
						canEat = true;
					if (i > 3 && j > 3 && (GameManager.Board[i - 1, j - 1] & Opponent) != 0 && (GameManager.Board[i - 2, j - 2] & Opponent) != 0 && GameManager.Board[i - 3, j - 3] == 0)  // Haut Gauche
						canEat = true;
					if (i > 3 && (GameManager.Board[i - 1, j] & Opponent) != 0 && (GameManager.Board[i - 2, j] & Opponent) != 0 && GameManager.Board[i - 3, j] == 0) // Haut
						canEat = true;
					if (j > 3 && (GameManager.Board[i, j - 1] & Opponent) != 0 && (GameManager.Board[i, j - 2] & Opponent) != 0 && GameManager.Board[i, j - 3] == 0) // Gauche
						canEat = true;
					if (j > 3 && i < GameManager.iHeightBoard - 3 && (GameManager.Board[i - 1, j - 1] & Opponent) != 0 && (GameManager.Board[i - 2, j - 2] & Opponent) != 0 && GameManager.Board[i - 3, j - 3] == 0) // Bas Gauche
						canEat = true;
				}
			}
		}
		return canEat;
	}

	private void CheckWin(int Player)
	{
		int Align = -1;
		int i = y;
		int j = x;

		//Horizontal
		while (GameManager.Board[i,j] == Player)
		{
			j++;
			Align++;
			if (j >= GameManager.iWidthBoard)
				break;
		}
		j = x;
		while (GameManager.Board[i,j] == Player)
		{
			j--;
			Align++;
			if (j < 0)
				break;
		}

		if (Align >= 5)
		{
			if ((Player & GameManager.Stone.Black) != 0 && !somethingToEat(GameManager.Stone.White, GameManager.Stone.Black))
				GameManager.BlackWin = true;
			else if ((Player & GameManager.Stone.White) != 0 && !somethingToEat(GameManager.Stone.Black, GameManager.Stone.White))
				GameManager.WhiteWin = true;
		}

		Align = -1;
		i = y;
		j = x;
		//Vertical
		while (GameManager.Board[i,j] == Player)
		{
			i++;
			Align++;
			if (i >= GameManager.iHeightBoard)
				break;
		}
		i = y;
		while (GameManager.Board[i,j] == Player)
		{
			i--;
			Align++;
			if (i < 0)
				break;
		}

		if (Align >= 5)
		{
			if ((Player & GameManager.Stone.Black) != 0 && !somethingToEat(GameManager.Stone.White, GameManager.Stone.Black))
				GameManager.BlackWin = true;
			else if ((Player & GameManager.Stone.White) != 0 && !somethingToEat(GameManager.Stone.Black, GameManager.Stone.White))

				GameManager.WhiteWin = true;
		}

		Align = -1;
		i = y;
		j = x;
		//Diagonal Haut->Bas
		while (GameManager.Board[i,j] == Player)
		{
			i++;
			j++;
			Align++;
			if (i >= GameManager.iHeightBoard || j >= GameManager.iWidthBoard)
				break;
		}
		i = y;
		j = x;
		while (GameManager.Board[i,j] == Player)
		{
			i--;
			j--;
			Align++;
			if (i < 0 || j < 0)
				break;
		}

		if (Align >= 5)
		{
			if ((Player & GameManager.Stone.Black) != 0 && !somethingToEat(GameManager.Stone.White, GameManager.Stone.Black))
				GameManager.BlackWin = true;
			else if ((Player & GameManager.Stone.White) != 0 && !somethingToEat(GameManager.Stone.Black, GameManager.Stone.White))
				GameManager.WhiteWin = true;
		}

		Align = -1;
		i = y;
		j = x;
		//Diagonal Bas->Haut
		while (GameManager.Board[i,j] == Player)
		{
			i++;
			j--;
			Align++;
			if (i >= GameManager.iHeightBoard || j < 0)
				break;
		}
		i = y;
		j = x;
		while (GameManager.Board[i,j] == Player)
		{
			i--;
			j++;
			Align++;
			if (j >= GameManager.iWidthBoard || i < 0)
				break;
		}

		if (Align >= 5)
		{
			if ((Player & GameManager.Stone.Black) != 0 && !somethingToEat(GameManager.Stone.White, GameManager.Stone.Black))
				GameManager.BlackWin = true;
			else if ((Player & GameManager.Stone.White) != 0 && !somethingToEat(GameManager.Stone.Black, GameManager.Stone.White))
				GameManager.WhiteWin = true;
		}

			

	}

	static public void DisplayBoard(bool bUndo = false){

		int Forbidden;
		int ForbiddenOther;
		int DoubleTree;
		int DoubleTreeOther;

		if (GameManager.bPlayerOneTurn)
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

		for (int i = 0; i < GameManager.iHeightBoard; i++)
		{
			for (int j = 0; j < GameManager.iWidthBoard; j++)
			{
				if (bUndo)
				{
					if ((GameManager.Board[i, j] & GameManager.Stone.Black) != 0)
					{
						changeBoxState(j, i, Type.Black);
					}
					else if ((GameManager.Board[i, j] & GameManager.Stone.White) != 0)
					{
						changeBoxState(j, i, Type.White);
					}
					else 
					{
						changeBoxState(j, i, Type.Empty);
					}
				}
				if ((GameManager.Board[i, j] & Forbidden) != 0)
				{
					changeBoxState(j, i, Type.Forbidden);
				}
				else if ((GameManager.Board[i, j] & ForbiddenOther) != 0)
				{
					changeBoxState(j, i, Type.Empty);
				}

				if ((GameManager.Board[i, j] & DoubleTree) != 0)
				{
					changeBoxState(j, i, Type.DoubleTree);
				}
				else if ((GameManager.Board[i, j] & DoubleTreeOther) != 0)
				{
					changeBoxState(j, i, Type.Empty);
				}
			}
		}
	}

	private void checkBoardState(int Height, int Width) {
		Height = (Height <= 5) ? 0 : Height - 5;
		Width = (Width <= 5) ? 0 : Width - 5; 
		int MaxHeight = (Height + 9 >= GameManager.iHeightBoard - 1) ? GameManager.iHeightBoard - 1 : Height + 9;
		int MaxWidth = (Width + 9 >= GameManager.iWidthBoard - 1) ? GameManager.iWidthBoard - 1 : Width + 9;

		for (int i = Height; i <= MaxHeight; i++) {
			for (int j = Width; j <= MaxWidth; j++) {

				if (EmptyCase(GameManager.Board[i, j])) {
					if (GameManager.Board[i, j] != 0) {
						changeBoxState(j , i, Type.Empty);
					}
//					checkForbiddenBox(i, j);
					checkDoubleTreeBox(i, j);
				}
			}
		}
		
	}

	private bool EmptyCase(int Content){

		if ((Content & GameManager.Stone.Black) == 0 && (Content & GameManager.Stone.White) == 0)
			return true;
		else
			return false;
	}

	private void checkStoneEaten() {
		
		int Player1;
		int Player2;

		if (GameManager.bPlayerOneTurn)
		{
			Player1 = GameManager.Stone.Black;
			Player2 = GameManager.Stone.White;
		}
		else
		{
			Player1 = GameManager.Stone.White;
			Player2 = GameManager.Stone.Black;
		}

		if (x >= 3) // Manger à gauche
			if (GameManager.Board[y, x - 1] == Player2 && GameManager.Board[y, x - 2] == Player2 && GameManager.Board[y, x - 3] == Player1)
			{
				changeBoxState(x - 1, y, Type.Eat);
				changeBoxState(x - 2, y, Type.Eat);
			}
		if (x <= GameManager.iWidthBoard - 3) // Manger à droite
			if (GameManager.Board[y, x + 1] == Player2 && GameManager.Board[y, x + 2] == Player2 && GameManager.Board[y, x + 3] == Player1)
			{
				changeBoxState(x + 1, y, Type.Eat);
				changeBoxState(x + 2, y, Type.Eat);
			}
		if (y >= 3) // Manger en haut
			if (GameManager.Board[y - 1, x] == Player2 && GameManager.Board[y - 2, x] == Player2 && GameManager.Board[y - 3, x] == Player1)
			{
				changeBoxState(x, y - 1, Type.Eat);
				changeBoxState(x, y - 2, Type.Eat);
			}
		if (y < GameManager.iHeightBoard - 3) // Manger en bas
			if (GameManager.Board[y + 1, x] == Player2 && GameManager.Board[y + 2, x] == Player2 && GameManager.Board[y + 3, x] == Player1)
			{
				changeBoxState(x, y + 1, Type.Eat);
				changeBoxState(x, y + 2, Type.Eat);
			}
		if (x >= 3 && y >= 3) // Manger en haut gauche
			if (GameManager.Board[y - 1, x - 1] == Player2 && GameManager.Board[y - 2, x - 2] == Player2 && GameManager.Board[y - 3, x - 3] == Player1)
			{
				changeBoxState(x - 1, y - 1, Type.Eat);
				changeBoxState(x - 2, y - 2, Type.Eat);
			}
		if (x < GameManager.iWidthBoard - 3 && y >= 3) // Manger en haut droite
			if (GameManager.Board[y - 1, x + 1] == Player2 && GameManager.Board[y - 2, x + 2] == Player2 && GameManager.Board[y - 3, x + 3] == Player1)
			{
				changeBoxState(x + 1, y - 1, Type.Eat);
				changeBoxState(x + 2, y - 2, Type.Eat);
			}
		if (x < GameManager.iWidthBoard - 3 && y < GameManager.iHeightBoard - 3) // Manger en bas  droite
			if (GameManager.Board[y + 1, x + 1] == Player2 && GameManager.Board[y + 2, x + 2] == Player2 && GameManager.Board[y + 3, x + 3] == Player1)
			{
				changeBoxState(x + 1, y + 1, Type.Eat);
				changeBoxState(x + 2, y + 2, Type.Eat);
			}
		if (x >= 3 && y < GameManager.iHeightBoard - 3) // Manger en bas gauche
			if (GameManager.Board[y + 1, x - 1] == Player2 && GameManager.Board[y + 2, x - 2] == Player2 && GameManager.Board[y + 3, x - 3] == Player1)
			{
				changeBoxState(x - 1, y + 1, Type.Eat);
				changeBoxState(x - 2, y + 2, Type.Eat);
			}
	}

	private bool FillForbiddenBoard(int Width, int Height, bool bPlayer) {

		int Player;

		if (bPlayer)
		{
			Player = GameManager.Stone.BlackForbidden;
		}
		else
		{
			Player = GameManager.Stone.WhiteForbidden;
		}

		if ((GameManager.Board[Height, Width] & Player) == 0)
		{
			GameManager.Board[Height, Width] += Player;
		}
		return false;
		
	}

	private void checkDoubleTreeBox(int y, int x)
	{
		int Player1;

		if (!GameManager.bPlayerOneTurn)
		{
			Player1 = GameManager.Stone.Black;
		}
		else
		{
			Player1 = GameManager.Stone.White;
		}

		int NumTree = 0;

		//  - X 0 X -
		if (x >= 2 && x < GameManager.iWidthBoard - 2 && EmptyCase(GameManager.Board[y, x - 2]) && GameManager.Board[y, x - 1] == Player1 && GameManager.Board[y, x + 1] == Player1 && EmptyCase(GameManager.Board[y, x + 2]))
		{
			NumTree++;
		}
		if (y >= 2 && y < GameManager.iHeightBoard - 2 && EmptyCase(GameManager.Board[y - 2, x]) && GameManager.Board[y - 1, x] == Player1 && GameManager.Board[y + 1, x] == Player1 && EmptyCase(GameManager.Board[y + 2, x]))
		{
			NumTree++;
		}
		if (x >= 2 && x < GameManager.iWidthBoard - 2 && EmptyCase(GameManager.Board[y, x - 2]) && y >= 2 && y < GameManager.iHeightBoard - 2
			&& EmptyCase(GameManager.Board[y - 2, x - 2]) && GameManager.Board[y - 1, x - 1] == Player1 && GameManager.Board[y + 1, x + 1] == Player1 && EmptyCase(GameManager.Board[y + 2, x + 2]))
		{
			NumTree++;
		}
		if (x >= 2 && x < GameManager.iWidthBoard - 2 && EmptyCase(GameManager.Board[y, x - 2]) && y >= 2 && y < GameManager.iHeightBoard - 2
			&& EmptyCase(GameManager.Board[y + 2, x - 2]) && GameManager.Board[y + 1, x - 1] == Player1 && GameManager.Board[y - 1, x + 1] == Player1 && EmptyCase(GameManager.Board[y - 2, x + 2]))
		{
			NumTree++;
		}

		// - X X 0 -
		if (x >= 3 && x < GameManager.iWidthBoard - 1 && EmptyCase(GameManager.Board[y, x - 3]) && GameManager.Board[y, x - 2] == Player1 && GameManager.Board[y, x - 1] == Player1 && EmptyCase(GameManager.Board[y, x + 1]))
		{
			NumTree++;
		}
		if (x >= 1 && x < GameManager.iWidthBoard - 3 && EmptyCase(GameManager.Board[y, x - 1]) && GameManager.Board[y, x + 1] == Player1 && GameManager.Board[y, x + 2] == Player1 && EmptyCase(GameManager.Board[y, x + 3]))
		{
			NumTree++;
		}
		if (y >= 3 && y < GameManager.iHeightBoard - 1 && EmptyCase(GameManager.Board[y - 3, x]) && GameManager.Board[y - 2, x] == Player1 && GameManager.Board[y - 1, x] == Player1 && EmptyCase(GameManager.Board[y + 1, x]))
		{
			NumTree++;
		}
		if (y >= 1 && y < GameManager.iHeightBoard - 3 && EmptyCase(GameManager.Board[y - 1, x]) && GameManager.Board[y + 1, x] == Player1 && GameManager.Board[y + 2, x] == Player1 && EmptyCase(GameManager.Board[y + 3, x]))
		{
			NumTree++;
		}
		if (x >= 3 && x < GameManager.iWidthBoard - 1 && y >= 3 && y < GameManager.iHeightBoard - 1
			&& EmptyCase(GameManager.Board[y - 3, x - 3]) && GameManager.Board[y - 2, x - 2] == Player1 && GameManager.Board[y - 1, x - 1] == Player1 && EmptyCase(GameManager.Board[y + 1, x + 1]))
		{
			NumTree++;
		}
		if (x >= 1 && x < GameManager.iWidthBoard - 3 && y >= 1 && y < GameManager.iHeightBoard - 3 
			&& EmptyCase(GameManager.Board[y - 1, x - 1]) && GameManager.Board[y + 1, x + 1] == Player1 && GameManager.Board[y + 2, x + 2] == Player1 && EmptyCase(GameManager.Board[y + 3, x + 3]))
		{
			NumTree++;
		}
		if (x >= 3 && x < GameManager.iWidthBoard - 1 && y >= 1 && y < GameManager.iHeightBoard - 3 
			&& EmptyCase(GameManager.Board[y + 3, x - 3]) && GameManager.Board[y + 2, x - 2] == Player1 && GameManager.Board[y + 1, x - 1] == Player1 && EmptyCase(GameManager.Board[y - 1, x + 1]))
		{
			NumTree++;
		}
		if (x >= 1 && x < GameManager.iWidthBoard - 3 && y >= 3 && y < GameManager.iHeightBoard - 1
			&& EmptyCase(GameManager.Board[y + 1, x - 1]) && GameManager.Board[y - 1, x + 1] == Player1 && GameManager.Board[y - 2, x + 2] == Player1 && EmptyCase(GameManager.Board[y - 3, x + 3]))
		{
			NumTree++;
		}

		// - X X - 0 -
		if (x >= 4 && x < GameManager.iWidthBoard - 1 && EmptyCase(GameManager.Board[y, x - 4]) && GameManager.Board[y, x - 3] == Player1 && GameManager.Board[y, x - 2] == Player1 && EmptyCase(GameManager.Board[y, x - 1])  && EmptyCase(GameManager.Board[y, x + 1]))
		{
			NumTree++;
		}
		if (x >= 1 && x < GameManager.iWidthBoard - 4 && EmptyCase(GameManager.Board[y, x + 4]) && GameManager.Board[y, x + 3] == Player1 && GameManager.Board[y, x + 2] == Player1 && EmptyCase(GameManager.Board[y, x + 1])  && EmptyCase(GameManager.Board[y, x - 1]))
		{
			NumTree++;
		}
		if (y >= 4 && y < GameManager.iHeightBoard - 1 && EmptyCase(GameManager.Board[y - 4, x]) && GameManager.Board[y - 3, x] == Player1 && GameManager.Board[y - 2, x] == Player1 && EmptyCase(GameManager.Board[y - 1, x])  && EmptyCase(GameManager.Board[y + 1, x]))
		{
			NumTree++;
		}
		if (y >= 1 && y < GameManager.iHeightBoard - 4 && EmptyCase(GameManager.Board[y + 4, x]) && GameManager.Board[y + 3, x] == Player1 && GameManager.Board[y + 2, x] == Player1 && EmptyCase(GameManager.Board[y + 1, x])  && EmptyCase(GameManager.Board[y - 1, x]))
		{
			NumTree++;
		}
		if (x >= 4 && x < GameManager.iWidthBoard - 1 && y >= 4 && y < GameManager.iHeightBoard - 1
			&& EmptyCase(GameManager.Board[y - 4, x - 4]) && GameManager.Board[y - 3, x - 3] == Player1 && GameManager.Board[y - 2, x - 2] == Player1 && EmptyCase(GameManager.Board[y - 1, x - 1])  && EmptyCase(GameManager.Board[y + 1, x + 1]))
		{
			NumTree++;
		}
		if (x >= 1 && x < GameManager.iWidthBoard - 4 && y >= 1 && y < GameManager.iHeightBoard - 4
			&& EmptyCase(GameManager.Board[y + 4, x + 4]) && GameManager.Board[y + 3, x + 3] == Player1 && GameManager.Board[y + 2, x + 2] == Player1 && EmptyCase(GameManager.Board[y + 1, x + 1])  && EmptyCase(GameManager.Board[y - 1, x - 1]))
		{
			NumTree++;
		}
		if (x >= 4 && x < GameManager.iWidthBoard - 1 && y >= 1 && y < GameManager.iHeightBoard - 4
			&& EmptyCase(GameManager.Board[y + 4, x - 4]) && GameManager.Board[y + 3, x - 3] == Player1 && GameManager.Board[y + 2, x - 2] == Player1 && EmptyCase(GameManager.Board[y + 1, x - 1])  && EmptyCase(GameManager.Board[y - 1, x + 1]))
		{
			NumTree++;
		}
		if (x >= 1 && x < GameManager.iWidthBoard - 4 && y >= 4 && y < GameManager.iHeightBoard - 1
			&& EmptyCase(GameManager.Board[y - 4, x + 4]) && GameManager.Board[y - 3, x + 3] == Player1 && GameManager.Board[y - 2, x + 2] == Player1 && EmptyCase(GameManager.Board[y - 1, x + 1])  && EmptyCase(GameManager.Board[y + 1, x - 1]))
		{
			NumTree++;
		}

		//  - X - 0 X -
		if (x >= 3 && x < GameManager.iWidthBoard - 2 && EmptyCase(GameManager.Board[y, x - 3]) && GameManager.Board[y, x - 2] == Player1 && EmptyCase(GameManager.Board[y, x - 1]) && GameManager.Board[y, x + 1] == Player1  && EmptyCase(GameManager.Board[y, x + 2]))
		{
			NumTree++;
		}
		if (x >= 2 && x < GameManager.iWidthBoard - 3 && EmptyCase(GameManager.Board[y, x + 3]) && GameManager.Board[y, x + 2] == Player1 && EmptyCase(GameManager.Board[y, x + 1]) && GameManager.Board[y, x - 1] == Player1  && EmptyCase(GameManager.Board[y, x - 2]))
		{
			NumTree++;
		}
		if (y >= 3 && y < GameManager.iHeightBoard - 2 && EmptyCase(GameManager.Board[y - 3, x]) && GameManager.Board[y - 2, x] == Player1 && EmptyCase(GameManager.Board[y - 1, x]) && GameManager.Board[y + 1, x] == Player1  && EmptyCase(GameManager.Board[y + 2, x]))
		{
			NumTree++;
		}
		if (y >= 2 && y < GameManager.iHeightBoard - 3 && EmptyCase(GameManager.Board[y + 3, x]) && GameManager.Board[y + 2, x] == Player1 && EmptyCase(GameManager.Board[y + 1, x]) && GameManager.Board[y - 1, x] == Player1  && EmptyCase(GameManager.Board[y - 2, x]))
		{
			NumTree++;
		}
		if (x >= 3 && x < GameManager.iWidthBoard - 2 && y >= 3 && y < GameManager.iHeightBoard - 2
			&& EmptyCase(GameManager.Board[y - 3, x - 3]) && GameManager.Board[y - 2, x - 2] == Player1 && EmptyCase(GameManager.Board[y - 1, x - 1]) && GameManager.Board[y + 1, x + 1] == Player1  && EmptyCase(GameManager.Board[y + 2, x + 2]))
		{
			NumTree++;
		}
		if (x >= 2 && x < GameManager.iWidthBoard - 3 && y >= 2 && y < GameManager.iHeightBoard - 3
			&& EmptyCase(GameManager.Board[y + 3, x + 3]) && GameManager.Board[y + 2, x + 2] == Player1 && EmptyCase(GameManager.Board[y + 1, x + 1]) && GameManager.Board[y - 1, x - 1] == Player1  && EmptyCase(GameManager.Board[y - 2, x - 2]))
		{
			NumTree++;
		}
		if (x >= 3 && x < GameManager.iWidthBoard - 2 && y >= 2 && y < GameManager.iHeightBoard - 3
			&& EmptyCase(GameManager.Board[y + 3, x - 3]) && GameManager.Board[y + 2, x - 2] == Player1 && EmptyCase(GameManager.Board[y + 1, x - 1]) && GameManager.Board[y - 1, x + 1] == Player1  && EmptyCase(GameManager.Board[y - 2, x + 2]))
		{
			NumTree++;
		}
		if (x >= 2 && x < GameManager.iWidthBoard - 3 && y >= 3 && y < GameManager.iHeightBoard - 2
			&& EmptyCase(GameManager.Board[y - 3, x + 3]) && GameManager.Board[y - 2, x + 2] == Player1 && EmptyCase(GameManager.Board[y - 1, x + 1]) && GameManager.Board[y + 1, x - 1] == Player1  && EmptyCase(GameManager.Board[y + 2, x - 2]))
		{
			NumTree++;
		}




		if (NumTree >= 2)
		{
			if (!GameManager.bPlayerOneTurn && (GameManager.Board[y, x] & GameManager.Stone.BlackDoubleTree) == 0)
			{
				GameManager.Board[y, x] += GameManager.Stone.BlackDoubleTree;
			}
			else if (GameManager.bPlayerOneTurn && (GameManager.Board[y, x] & GameManager.Stone.WhiteDoubleTree) == 0)
			{
				GameManager.Board[y, x] += GameManager.Stone.WhiteDoubleTree;
			}
		}
		else 
		{
			if ((GameManager.Board[y, x] & GameManager.Stone.WhiteDoubleTree) != 0 && GameManager.bPlayerOneTurn)
				GameManager.Board[y, x] -= GameManager.Stone.WhiteDoubleTree;
			if ((GameManager.Board[y, x] & GameManager.Stone.BlackDoubleTree) != 0 && !GameManager.bPlayerOneTurn)
				GameManager.Board[y, x] -= GameManager.Stone.BlackDoubleTree;
		}
	}

	private void checkForbiddenBox(int y, int x) {

		int Player1;
		int Player2;

		if (GameManager.bPlayerOneTurn)
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

		if (x >= 1 && x < GameManager.iWidthBoard - 2) // Gauche
		{
			if (GameManager.Board[y, x - 1] == Player2 && GameManager.Board[y, x + 1] == Player1 && GameManager.Board[y, x + 2] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.bPlayerOneTurn);
		}
		if (x < GameManager.iWidthBoard - 1 && x >= 2) // Droite
		{
			if (GameManager.Board[y, x - 2] == Player2 && GameManager.Board[y, x - 1] == Player1 && GameManager.Board[y, x + 1] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.bPlayerOneTurn);
		}
		if (y >= 1 && y < GameManager.iHeightBoard - 2) // Haut
		{
			if (GameManager.Board[y - 1, x] == Player2 && GameManager.Board[y + 1, x] == Player1 && GameManager.Board[y + 2, x] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.bPlayerOneTurn);
		}
		if (y < GameManager.iHeightBoard - 1 && y >= 2) // Bas
		{
			if (GameManager.Board[y - 2, x] == Player2 && GameManager.Board[y - 1, x] == Player1 && GameManager.Board[y + 1, x] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.bPlayerOneTurn);
		}
		if (x >= 1 && y >= 1 && y < GameManager.iHeightBoard - 2 && x < GameManager.iWidthBoard - 2) // Haut Gauche
		{
			if (GameManager.Board[y - 1, x - 1] == Player2 && GameManager.Board[y + 1, x + 1] == Player1 && GameManager.Board[y + 2, x + 2] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.bPlayerOneTurn);
		}
		if (x >= 1 && y < GameManager.iHeightBoard - 1 && x < GameManager.iWidthBoard - 2 && y >= 2) // Bas Gauche
		{
			if (GameManager.Board[y + 1, x - 1] == Player2 && GameManager.Board[y - 1, x + 1] == Player1 && GameManager.Board[y - 2, x + 2] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.bPlayerOneTurn);
		}
		if (x < GameManager.iWidthBoard - 1 && y >= 1 && x >= 2 && y < GameManager.iHeightBoard - 2) // Haut Droite
		{
			if (GameManager.Board[y - 1, x + 1] == Player2 && GameManager.Board[y + 1, x - 1] == Player1 && GameManager.Board[y + 2, x - 2] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.bPlayerOneTurn);
		}
		if (x < GameManager.iWidthBoard - 1 && y < GameManager.iHeightBoard - 1 && x >= 2 && y >= 2) // Bas Droite
		{
			if (GameManager.Board[y + 1, x + 1] == Player2 && GameManager.Board[y - 1, x - 1] == Player1 && GameManager.Board[y - 2, x - 2] == Player2)
				bEmpty = FillForbiddenBoard(x, y, GameManager.bPlayerOneTurn);
		}
		if (bEmpty)
		{
			GameManager.Board[y, x] = GameManager.Stone.Empty;
		}
	}

	static private void changeBoxState(int Width , int Height, Type type) {

		int id = Width + Height * GameManager.iWidthBoard + 1;
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
		else if (type == Type.Empty)
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
		else if (type == Type.Eat) 
		{
			GameManager.Board[Height, Width] = GameManager.Stone.Empty;
			if (GameManager.bPlayerOneTurn)
			{
				GameManager.BlackScore++;
				tmpWhiteStoneImage.enabled = false;
			}
			else
			{
				GameManager.WhiteScore++;
				tmpBlackStoneImage.enabled = false;
			}
		}
		else if (type == Type.DoubleTree && !tmpDoubleTreeImage.enabled)
			tmpDoubleTreeImage.enabled = true;
		else if (type == Type.Forbidden && !tmpForbiddenImage.enabled)
			tmpForbiddenImage.enabled = true;
		else if (type == Type.Black && !tmpBlackStoneImage.enabled)
			tmpBlackStoneImage.enabled = true;
		else if (type == Type.White && !tmpWhiteStoneImage.enabled)
			tmpWhiteStoneImage.enabled = true;
	}

	public void OnDeleteMove() {

		if (!WhiteStoneImage.enabled)
		{
			WhiteStoneImage.enabled = false;
		}

		if (!BlackStoneImage.enabled)
		{
			BlackStoneImage.enabled = false;
		}
		GameManager.Board[y, x] = GameManager.Stone.Empty;
	}

}
