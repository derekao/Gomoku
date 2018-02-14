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
			checkStoneEaten();
			BlackStoneImage.enabled = true;
			gameManager.bPlayerOneTurn = false;
			gameManager.Board[y, x] = GameManager.Stone.Black;
			int[,] tmpArray = gameManager.Board.Clone() as int[,];
			gameManager.lBoardHisto.Add(tmpArray);
			gameManager.iTurn += 1;
			checkBoardState();
			DisplayBoard();
		}

	}

	private void OnWhitePlay() {

		if (!WhiteStoneImage.enabled && !BlackStoneImage.enabled && !ForbiddenImage.enabled)
		{
			checkStoneEaten();
			WhiteStoneImage.enabled = true;
			gameManager.bPlayerOneTurn = true;
			gameManager.Board[y, x] = GameManager.Stone.White;
			int[,] tmpArray = gameManager.Board.Clone() as int[,];
			gameManager.lBoardHisto.Add(tmpArray);
			gameManager.iTurn += 1;
			checkBoardState();
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
		// checkStoneEaten();
		for (int i = 0; i < GameManager.iHeightBoard; i++) {
			for (int j = 0; j < GameManager.iWidthBoard; j++) {

				if ((gameManager.Board[i, j] & GameManager.Stone.Black) == 0 && (gameManager.Board[i, j] & GameManager.Stone.White) == 0) {
					if ((gameManager.Board[i, j] & 0) == 0) {
						gameManager.Board[i, j] = GameManager.Stone.Empty;
						changeBoxState(j , i, Type.Empty);
					}
					checkForbiddenBox(i, j);
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

		if (x >= 3) // Manger à gauche
			if (gameManager.Board[y, x - 1] == Player2 && gameManager.Board[y, x - 2] == Player2 && gameManager.Board[y, x - 3] == Player1)
			{
				changeBoxState(x - 1, y, Type.Eat);
				changeBoxState(x - 2, y, Type.Eat);
			}
		if (x <= GameManager.iWidthBoard - 3) // Manger à droite
			if (gameManager.Board[y, x + 1] == Player2 && gameManager.Board[y, x + 2] == Player2 && gameManager.Board[y, x + 3] == Player1)
			{
				changeBoxState(x + 1, y, Type.Eat);
				changeBoxState(x + 2, y, Type.Eat);
			}
		if (y >= 3) // Manger en haut
			if (gameManager.Board[y - 1, x] == Player2 && gameManager.Board[y - 2, x] == Player2 && gameManager.Board[y - 3, x] == Player1)
			{
				changeBoxState(x, y - 1, Type.Eat);
				changeBoxState(x, y - 2, Type.Eat);
			}
		if (y < GameManager.iHeightBoard - 3) // Manger en bas
			if (gameManager.Board[y + 1, x] == Player2 && gameManager.Board[y + 2, x] == Player2 && gameManager.Board[y + 3, x] == Player1)
			{
				changeBoxState(x, y + 1, Type.Eat);
				changeBoxState(x, y + 2, Type.Eat);
			}
		if (x >= 3 && y >= 3) // Manger en haut gauche
			if (gameManager.Board[y - 1, x - 1] == Player2 && gameManager.Board[y - 2, x - 2] == Player2 && gameManager.Board[y - 3, x - 3] == Player1)
			{
				changeBoxState(x - 1, y - 1, Type.Eat);
				changeBoxState(x - 2, y - 2, Type.Eat);
			}
		if (x < GameManager.iWidthBoard - 3 && y >= 3) // Manger en haut droite
			if (gameManager.Board[y - 1, x + 1] == Player2 && gameManager.Board[y - 2, x + 2] == Player2 && gameManager.Board[y - 3, x + 3] == Player1)
			{
				changeBoxState(x + 1, y - 1, Type.Eat);
				changeBoxState(x + 2, y - 2, Type.Eat);
			}
		if (x < GameManager.iWidthBoard - 3 && y < GameManager.iHeightBoard - 3) // Manger en bas  droite
			if (gameManager.Board[y + 1, x + 1] == Player2 && gameManager.Board[y + 2, x + 2] == Player2 && gameManager.Board[y + 3, x + 3] == Player1)
			{
				changeBoxState(x + 1, y + 1, Type.Eat);
				changeBoxState(x + 2, y + 2, Type.Eat);
			}
		if (x >= 3 && y < GameManager.iHeightBoard - 3) // Manger en bas gauche
			if (gameManager.Board[y + 1, x - 1] == Player2 && gameManager.Board[y + 2, x - 2] == Player2 && gameManager.Board[y + 3, x - 3] == Player1)
			{
				changeBoxState(x - 1, y + 1, Type.Eat);
				changeBoxState(x - 2, y + 2, Type.Eat);
			}
	}

	private void FillForbiddenBoard(int Width, int Height, bool bPlayer, bool empty = false) {

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
			if (!empty)
				gameManager.Board[Height, Width] += Player;
			else
				gameManager.Board[Height, Width] -= Player;
		}
		
	}

	private void checkForbiddenBox(int y, int x) {

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

		if (x >= 1 && x < GameManager.iWidthBoard - 2) // Gauche
		{
			if (gameManager.Board[y, x - 1] == Player2 && gameManager.Board[y, x + 1] == Player1 && gameManager.Board[y, x + 2] == Player2)
				FillForbiddenBoard(x, y, gameManager.bPlayerOneTurn);
		}
		if (x < GameManager.iWidthBoard - 1 && x >= 2) // Droite
		{
			if (gameManager.Board[y, x - 2] == Player2 && gameManager.Board[y, x - 1] == Player1 && gameManager.Board[y, x + 1] == Player2)
				FillForbiddenBoard(x, y, gameManager.bPlayerOneTurn);
		}
		if (y >= 1 && y < GameManager.iHeightBoard - 2) // Haut
		{
			if (gameManager.Board[y - 1, x] == Player2 && gameManager.Board[y + 1, x] == Player1 && gameManager.Board[y + 2, x] == Player2)
				FillForbiddenBoard(x, y, gameManager.bPlayerOneTurn);
		}
		if (y < GameManager.iHeightBoard - 1 && y >= 2) // Bas
		{
			if (gameManager.Board[y - 2, x] == Player2 && gameManager.Board[y - 1, x] == Player1 && gameManager.Board[y + 1, x] == Player2)
				FillForbiddenBoard(x, y, gameManager.bPlayerOneTurn);
		}
		if (x >= 1 && y >= 1 && y < GameManager.iHeightBoard - 2 && x < GameManager.iWidthBoard - 2) // Haut Gauche
		{
			if (gameManager.Board[y - 1, x - 1] == Player2 && gameManager.Board[y + 1, x + 1] == Player1 && gameManager.Board[y + 2, x + 2] == Player2)
				FillForbiddenBoard(x, y, gameManager.bPlayerOneTurn);
		}
		if (x >= 1 && y < GameManager.iHeightBoard - 1 && x < GameManager.iWidthBoard - 2 && y >= 2) // Bas Gauche
		{
			if (gameManager.Board[y + 1, x - 1] == Player2 && gameManager.Board[y - 1, x + 1] == Player1 && gameManager.Board[y - 2, x + 2] == Player2)
				FillForbiddenBoard(x, y, gameManager.bPlayerOneTurn);
		}
		if (x < GameManager.iWidthBoard - 1 && y >= 1 && x >= 2 && y < GameManager.iHeightBoard - 2) // Haut Droite
		{
			if (gameManager.Board[y - 1, x + 1] == Player2 && gameManager.Board[y + 1, x - 1] == Player1 && gameManager.Board[y + 2, x - 2] == Player2)
				FillForbiddenBoard(x, y, gameManager.bPlayerOneTurn);
		}
		if (x < GameManager.iWidthBoard - 1 && y < GameManager.iHeightBoard - 1 && x >= 2 && y >= 2) // Bas Droite
		{
			if (gameManager.Board[y + 1, x + 1] == Player2 && gameManager.Board[y - 1, x - 1] == Player1 && gameManager.Board[y - 2, x - 2] == Player2)
				FillForbiddenBoard(x, y, gameManager.bPlayerOneTurn);
		}
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
