using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayStone : MonoBehaviour {

	private enum Type { Empty, Eat, DoubleTree, Forbidden };

	private GameManager gameManager;
	private GameObject BlackStone;
	private GameObject WhiteStone;
	private GameObject Forbidden;
	private Image BlackStoneImage;
	private Image WhiteStoneImage;
	private Image ForbiddenImage;

	private int x;
	private int y;

	void Start() {

		gameManager = GameObject.Find("Main Camera").GetComponent<GameManager>();
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
		}
		if (!BlackStoneImage || !WhiteStoneImage || !ForbiddenImage)
		{
			Debug.Log("Wrong Stone Init 1");
		}

		string szIndex = this.name.Substring(7, name.Length - 8);
		int iIndex = int.Parse(szIndex) - 1;
		y = iIndex / GameManager.iHeightBoard;
		x = iIndex % GameManager.iWidthBoard;

	}

	public void OnClick() {
		if (gameManager.bPlayerOneTurn) {
			OnBlackPlay();
		}
		else {
			OnWhitePlay();
		}
		// changeBoxState(2, 2);
	}
	private void OnBlackPlay() {

		if (!WhiteStoneImage.enabled && !BlackStoneImage.enabled && !ForbiddenImage.enabled) 
		{
			checkBoardState();
			BlackStoneImage.enabled = true;
			gameManager.bPlayerOneTurn = false;
			gameManager.Board[y, x] = GameManager.Stone.Black;
			int[,] tmpArray = gameManager.Board.Clone() as int[,];
			gameManager.lBoardHisto.Add(tmpArray);
			gameManager.iTurn += 1;
			DisplayBoard();
		}

	}

	private void OnWhitePlay() {

		if (!WhiteStoneImage.enabled && !BlackStoneImage.enabled && !ForbiddenImage.enabled)
		{
			checkBoardState();
			WhiteStoneImage.enabled = true;
			gameManager.bPlayerOneTurn = true;
			gameManager.Board[y, x] = GameManager.Stone.White;
			int[,] tmpArray = gameManager.Board.Clone() as int[,];
			gameManager.lBoardHisto.Add(tmpArray);
			gameManager.iTurn += 1;
			DisplayBoard();
		}

	}

	private void DisplayBoard(){

		int Forbidden;
		int ForbiddenOther;
		int DoubleTree;
		int DoubleTreeOther;

		if (gameManager.bPlayerOneTurn)
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
				if ((gameManager.Board[i, j] & Forbidden) != 0)
				{
					changeBoxState(j, i, Type.Forbidden);
				}
				else if ((gameManager.Board[i, j] & ForbiddenOther) != 0)
				{
					changeBoxState(j, i, Type.Empty);
				}

				if ((gameManager.Board[i, j] & DoubleTree) != 0)
				{
					changeBoxState(j, i, Type.Forbidden);
				}
				else if ((gameManager.Board[i, j] & DoubleTreeOther) != 0)
				{
					changeBoxState(j, i, Type.Empty);
				}
			}
		}
	}

	private void checkBoardState() {
		checkStoneEaten();
	}

	private bool EmptyCase(int Content){

		if ((Content & GameManager.Stone.Black) == 0 && (Content & GameManager.Stone.White) == 0)
		{
			return true;
		}
		else
			return false;
	}

	private void checkStoneEaten() {
		
		int Player1;
		int Player2;

		if (gameManager.bPlayerOneTurn)
		{
			Player1 = GameManager.Stone.Black;
			Player2 = GameManager.Stone.White;
		}
		else
		{
			Player1 = GameManager.Stone.White;
			Player2 = GameManager.Stone.Black;
		}

		//
		//  
		//
		if (x >= 3) // Manger à gauche
		{
			if (gameManager.Board[y, x - 1] == Player2 && gameManager.Board[y, x - 2] == Player2 && gameManager.Board[y, x - 3] == Player1)
			{
				changeBoxState(x - 1, y, Type.Eat);
				changeBoxState(x - 2, y, Type.Eat);
			}
			else if (gameManager.Board[y, x - 1] == Player2 && EmptyCase(gameManager.Board[y, x - 2]) && gameManager.Board[y, x - 3] == Player1)
			{
				FillForbiddenBoard(x - 2, y, !gameManager.bPlayerOneTurn);
			}
			else if (EmptyCase(gameManager.Board[y, x - 1]) && gameManager.Board[y, x - 2] == Player2 && gameManager.Board[y, x - 3] == Player1)
			{
				FillForbiddenBoard(x - 1, y, !gameManager.bPlayerOneTurn);
			}

		}
		if (x <= GameManager.iWidthBoard - 3) // Manger à droite
		{
			if (gameManager.Board[y, x + 1] == Player2 && gameManager.Board[y, x + 2] == Player2 && gameManager.Board[y, x + 3] == Player1)
			{
				changeBoxState(x + 1, y, Type.Eat);
				changeBoxState(x + 2, y, Type.Eat);
			}
			else if (gameManager.Board[y, x + 1] == Player2 && EmptyCase(gameManager.Board[y, x + 2]) && gameManager.Board[y, x + 3] == Player1)
			{
				FillForbiddenBoard(x + 2, y, !gameManager.bPlayerOneTurn);
			}
			else if (EmptyCase(gameManager.Board[y, x + 1]) && gameManager.Board[y, x + 2] == Player2 && gameManager.Board[y, x + 3] == Player1)
			{
				FillForbiddenBoard(x + 1, y, !gameManager.bPlayerOneTurn);
			}
		}
		if (y >= 3) // Manger en haut
		{
			if (gameManager.Board[y - 1, x] == Player2 && gameManager.Board[y - 2, x] == Player2 && gameManager.Board[y - 3, x] == Player1)
			{
				changeBoxState(x, y - 1, Type.Eat);
				changeBoxState(x, y - 2, Type.Eat);
			}
			else if (gameManager.Board[y - 1, x] == Player2 && EmptyCase(gameManager.Board[y - 2, x]) && gameManager.Board[y - 3, x] == Player1)
			{
				FillForbiddenBoard(x, y - 2, !gameManager.bPlayerOneTurn);
			}
			else if (EmptyCase(gameManager.Board[y - 1, x]) && gameManager.Board[y - 2, x] == Player2 && gameManager.Board[y - 3, x] == Player1)
			{
				FillForbiddenBoard(x, y - 1, !gameManager.bPlayerOneTurn);
			}
		}
		if (y <= GameManager.iHeightBoard - 3) // Manger en bas
		{
			if (gameManager.Board[y + 1, x] == Player2 && gameManager.Board[y + 2, x] == Player2 && gameManager.Board[y + 3, x] == Player1)
			{
				changeBoxState(x, y + 1, Type.Eat);
				changeBoxState(x, y + 2, Type.Eat);
			}
			else if (gameManager.Board[y + 1, x] == Player2 && EmptyCase(gameManager.Board[y + 2, x]) && gameManager.Board[y + 3, x] == Player1)
			{
				FillForbiddenBoard(x, y + 2, !gameManager.bPlayerOneTurn);
			}
			else if (EmptyCase(gameManager.Board[y + 1, x]) && gameManager.Board[y + 2, x] == Player2 && gameManager.Board[y + 3, x] == Player1)
			{
				FillForbiddenBoard(x, y + 1, !gameManager.bPlayerOneTurn);
			}
		}
		if (x >= 3 && y >= 3) // Manger en haut gauche
		{
			if (gameManager.Board[y - 1, x - 1] == Player2 && gameManager.Board[y - 2, x - 2] == Player2 && gameManager.Board[y - 3, x - 3] == Player1)
			{
				changeBoxState(x - 1, y - 1, Type.Eat);
				changeBoxState(x - 2, y - 2, Type.Eat);
			}
			else if (gameManager.Board[y - 1, x - 1] == Player2 && EmptyCase(gameManager.Board[y - 2, x - 2]) && gameManager.Board[y - 3, x - 3] == Player1)
			{
				FillForbiddenBoard(x - 2, y - 2, !gameManager.bPlayerOneTurn);
			}
			else if (EmptyCase(gameManager.Board[y - 1, x - 1]) && gameManager.Board[y - 2, x - 2] == Player2 && gameManager.Board[y - 3, x - 3] == Player1)
			{
				FillForbiddenBoard(x - 1, y - 1, !gameManager.bPlayerOneTurn);
			}
		}
		if (x <= GameManager.iWidthBoard - 3 && y >= 3) // Manger en haut droite
		{
			if (gameManager.Board[y - 1, x + 1] == Player2 && gameManager.Board[y - 2, x + 2] == Player2 && gameManager.Board[y - 3, x + 3] == Player1)
			{
				changeBoxState(x + 1, y - 1, Type.Eat);
				changeBoxState(x + 2, y - 2, Type.Eat);
			}
			else if (gameManager.Board[y - 1, x + 1] == Player2 && EmptyCase(gameManager.Board[y - 2, x + 2]) && gameManager.Board[y - 3, x + 3] == Player1)
			{
				FillForbiddenBoard(x + 2, y - 2, !gameManager.bPlayerOneTurn);
			}
			else if (EmptyCase(gameManager.Board[y - 1, x + 1]) && gameManager.Board[y - 2, x + 2] == Player2 && gameManager.Board[y - 3, x + 3] == Player1)
			{
				FillForbiddenBoard(x + 1, y - 1, !gameManager.bPlayerOneTurn);
			}
		}
		if (x <= GameManager.iWidthBoard - 3 && y <= GameManager.iHeightBoard - 3) // Manger en bas  droite
		{
			if (gameManager.Board[y + 1, x + 1] == Player2 && gameManager.Board[y + 2, x + 2] == Player2 && gameManager.Board[y + 3, x + 3] == Player1)
			{
				changeBoxState(x + 1, y + 1, Type.Eat);
				changeBoxState(x + 2, y + 2, Type.Eat);
			}
			else if (gameManager.Board[y + 1, x + 1] == Player2 && EmptyCase(gameManager.Board[y + 2, x + 2])  && gameManager.Board[y + 3, x + 3] == Player1)
			{
				FillForbiddenBoard(x + 2, y + 2, !gameManager.bPlayerOneTurn);
			}
			else if (EmptyCase(gameManager.Board[y + 1, x + 1]) && gameManager.Board[y + 2, x + 2] == Player2 && gameManager.Board[y + 3, x + 3] == Player1)
			{
				FillForbiddenBoard(x + 1, y + 1, !gameManager.bPlayerOneTurn);
			}
		}
		if (x >= 3 && y <= GameManager.iHeightBoard - 3) // Manger en bas gauche
		{
			if (gameManager.Board[y + 1, x - 1] == Player2 && gameManager.Board[y + 2, x - 2] == Player2 && gameManager.Board[y + 3, x - 3] == Player1)
			{
				changeBoxState(x - 1, y + 1, Type.Eat);
				changeBoxState(x - 2, y + 2, Type.Eat);
			}
			else if (gameManager.Board[y + 1, x - 1] == Player2 && EmptyCase(gameManager.Board[y + 2, x - 2]) && gameManager.Board[y + 3, x - 3] == Player1)
			{
				FillForbiddenBoard(x - 2, y + 2, !gameManager.bPlayerOneTurn);
			}
			else if (EmptyCase(gameManager.Board[y + 1, x - 1]) && gameManager.Board[y + 2, x - 2] == Player2 && gameManager.Board[y + 3, x - 3] == Player1)
			{
				FillForbiddenBoard(x - 1, y + 1, !gameManager.bPlayerOneTurn);
			}
		}

		//
		//
		//
		if (x >= 1) // Gauche
		{
			if (gameManager.Board[y, x - 1] == Player2 && EmptyCase(gameManager.Board[y, x + 1]) && gameManager.Board[y, x + 2] == Player2)
			{
				FillForbiddenBoard(x + 1, y, gameManager.bPlayerOneTurn);
			}
		}
		if (x <= GameManager.iWidthBoard - 1) // Droite
		{
			if (gameManager.Board[y, x - 2] == Player2 && EmptyCase(gameManager.Board[y, x - 1]) && gameManager.Board[y, x + 1] == Player2)
			{
				FillForbiddenBoard(x - 1, y, gameManager.bPlayerOneTurn);
			}
		}
		if (y >= 1) // Haut
		{
			if (gameManager.Board[y - 1, x] == Player2 && EmptyCase(gameManager.Board[y + 1, x]) && gameManager.Board[y + 2, x] == Player2)
			{
				FillForbiddenBoard(x, y + 1, gameManager.bPlayerOneTurn);
			}
		}
		if (y <= GameManager.iHeightBoard - 1) // Bas
		{
			if (gameManager.Board[y - 2, x] == Player2 && EmptyCase(gameManager.Board[y - 1, x]) && gameManager.Board[y + 1, x] == Player2)
			{
				FillForbiddenBoard(x, y - 1, gameManager.bPlayerOneTurn);
			}
		}
		if (x >= 1 && y >= 1) // Haut Gauche
		{
			if (gameManager.Board[y - 1, x - 1] == Player2 && EmptyCase(gameManager.Board[y + 1, x + 1]) && gameManager.Board[y + 2, x + 2] == Player2)
			{
				FillForbiddenBoard(x + 1, y + 1, gameManager.bPlayerOneTurn);
			}
		}
		if (x >= 1 && y <= GameManager.iHeightBoard - 1) // Bas Gauche
		{
			if (gameManager.Board[y + 1, x - 1] == Player2 && EmptyCase(gameManager.Board[y - 1, x + 1]) && gameManager.Board[y - 2, x + 2] == Player2)
			{
				FillForbiddenBoard(x + 1, y - 1, gameManager.bPlayerOneTurn);
			}
		}
		if (x <= GameManager.iWidthBoard - 1 && y >= 1) // Haut Droite
		{
			if (gameManager.Board[y - 1, x + 1] == Player2 && EmptyCase(gameManager.Board[y + 1, x - 1]) && gameManager.Board[y + 2, x - 2] == Player2)
			{
				FillForbiddenBoard(x - 1, y + 1, gameManager.bPlayerOneTurn);
			}
		}
		if (x <= GameManager.iWidthBoard - 1 && y <= GameManager.iHeightBoard - 1) // Bas Droite
		{
			if (gameManager.Board[y + 1, x + 1] == Player2 && EmptyCase(gameManager.Board[y - 1, x - 1]) && gameManager.Board[y - 2, x - 2] == Player2)
			{
				FillForbiddenBoard(x - 1, y - 1, gameManager.bPlayerOneTurn);
			}
		}
	}

	private void CheckChangedRules(int Width, int Height)
	{
		if (Width >= 0)
	}

	private void FillForbiddenBoard(int Width, int Height, bool bPlayer) {

		int Player;

		if (bPlayer)
		{
			Player = GameManager.Stone.BlackForbidden;
		}
		else
		{
			Player = GameManager.Stone.WhiteForbidden;
		}

		if ((gameManager.Board[Height, Width] & Player) == 0)
		{
			gameManager.Board[Height, Width] += Player;
		}
		
	}

	private void checkForbiddenCase(int y, int x) {

	}

	private void changeBoxState(int Width , int Height, Type type) {

		int id = Width + Height * GameManager.iWidthBoard + 1;
		GameObject box = GameObject.Find("Stone (" + id + ")");
		GameObject tmpBlackStone;
		GameObject tmpWhiteStone;
		GameObject tmpForbidden;
		Image tmpBlackStoneImage = null;
		Image tmpWhiteStoneImage = null;
		Image tmpForbiddenImage = null;

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
		}
		if (!tmpBlackStoneImage || !tmpWhiteStoneImage || !tmpForbiddenImage)
			Debug.Log("Wrong Stone Init 2");
		else if (type == Type.Empty)
		{
			if (tmpForbiddenImage.enabled)
				tmpForbiddenImage.enabled = false;
			if (tmpForbiddenImage.enabled)
				tmpForbiddenImage.enabled = false;
		}
		else if (type == Type.Eat) 
		{
			gameManager.Board[Height, Width] = GameManager.Stone.Empty;
			if (gameManager.bPlayerOneTurn)
			{
				gameManager.BlackScore++;
				tmpWhiteStoneImage.enabled = false;
			}
			else
			{
				gameManager.WhiteScore++;
				tmpBlackStoneImage.enabled = false;
			}
		}
		else if (type == Type.DoubleTree && !tmpForbiddenImage.enabled)
			tmpForbiddenImage.enabled = true;
		else if (type == Type.Forbidden && !tmpForbiddenImage.enabled)
			tmpForbiddenImage.enabled = true;
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
		gameManager.Board[y, x] = GameManager.Stone.Empty;
	}

}
