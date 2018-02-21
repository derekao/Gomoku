using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Runtime.InteropServices; // Dll

public class PlayStone : MonoBehaviour {

	[DllImport("Test.dll")]
	public static extern int Add(int a, int b);

	public enum Type { Empty, Black, White, Eat, DoubleTree, Forbidden };
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

	private static bool win = false;
	private static int winX;
	private static int winY;

	// Inititalization
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
		y = iIndex / GameManager.Instance.iHeightBoard;
		x = iIndex % GameManager.Instance.iWidthBoard;

	}

	/// <summary>
	/// Called by Unity when the Player click on the board
	/// </summary>
	public void OnClick() {
		if (GameManager.Instance.bPlayerOneTurn) {
			OnBlackPlay();
		}
		else {
			OnWhitePlay();
		}
	}

	private void OnBlackPlay() {

		if (!WhiteStoneImage.enabled && !BlackStoneImage.enabled && !ForbiddenImage.enabled && !DoubleTreeImage.enabled) 
		{
			bool eat = checkStoneEaten();
			BlackStoneImage.enabled = true;
			GameManager.Instance.bPlayerOneTurn = false;
			GameManager.Instance.Board[y, x] = GameManager.Stone.Black;
			int[,] tmpArray = GameManager.Instance.Board.Clone() as int[,];
			GameManager.Instance.lBoardHisto.Insert(0, tmpArray);
			GameManager.Instance.lPointHisto.Insert(0, eat ? 1 : 0);
			GameManager.Instance.iTurn += 1;
			if (win)
				CheckWin(GameManager.Stone.White, win);
			CheckWin(GameManager.Stone.Black);
			checkBoardState(y, x);
			Rules.DisplayBoard();
		}

	}

	private void OnWhitePlay() {

		if (!WhiteStoneImage.enabled && !BlackStoneImage.enabled && !ForbiddenImage.enabled && !DoubleTreeImage.enabled)
		{
			bool eat = checkStoneEaten();
			WhiteStoneImage.enabled = true;
			GameManager.Instance.bPlayerOneTurn = true;
			GameManager.Instance.Board[y, x] = GameManager.Stone.White;
			int[,] tmpArray = GameManager.Instance.Board.Clone() as int[,];
			GameManager.Instance.lBoardHisto.Insert(0, tmpArray);
			GameManager.Instance.lPointHisto.Insert(0, eat ? 1 : 0);
			GameManager.Instance.iTurn += 1;
			if (win)
				CheckWin(GameManager.Stone.Black, win);
			CheckWin(GameManager.Stone.White);
			checkBoardState(y, x);
			Rules.DisplayBoard();
		}

	}

	private void youWin(int Player, bool oldCase) 
	{
		if ((Player & GameManager.Stone.Black) != 0 && !Rules.somethingToEatOnTheBoard(GameManager.Stone.White, GameManager.Stone.Black))
			GameManager.Instance.BlackWin = true;
		else if ((Player & GameManager.Stone.White) != 0 && !Rules.somethingToEatOnTheBoard(GameManager.Stone.Black, GameManager.Stone.White))
			GameManager.Instance.WhiteWin = true;
		else if (oldCase)
			win = false;
		else {
			win = true;
			winY = y;
			winX = x;
		}
	}

	// Change the GameManager to Sstop the game if the player has won
	private void CheckWin(int Player, bool oldCase = false)
	{
		int Align = -1;
		int i;
		int j;

		if (oldCase) {
			i = winY;
			j = winX;
		}
		else {
			i = y;
			j = x;
		}

		//Horizontal
		while (GameManager.Instance.Board[i,j] == Player)
		{
			j++;
			Align++;
			if (j >= GameManager.Instance.iWidthBoard)
				break;
		}
		if (oldCase) {
			j = winX;
		}
		else {
			j = x;
		}
		while (GameManager.Instance.Board[i,j] == Player)
		{
			j--;
			Align++;
			if (j < 0)
				break;
		}

		if (Align >= 5)
			youWin(Player, oldCase);

		Align = -1;
		if (oldCase) {
			i = winY;
			j = winX;
		}
		else {
			i = y;
			j = x;
		}
		//Vertical
		while (GameManager.Instance.Board[i,j] == Player)
		{
			i++;
			Align++;
			if (i >= GameManager.Instance.iHeightBoard)
				break;
		}
		if (oldCase) {
			i = winY;
		}
		else {
			i = y;
		}
		while (GameManager.Instance.Board[i,j] == Player)
		{
			i--;
			Align++;
			if (i < 0)
				break;
		}

		if (Align >= 5)
			youWin(Player, oldCase);

		Align = -1;
		if (oldCase) {
			i = winY;
			j = winX;
		}
		else {
			i = y;
			j = x;
		}

		//Diagonal Top->Bottom
		while (GameManager.Instance.Board[i,j] == Player)
		{
			i++;
			j++;
			Align++;
			if (i >= GameManager.Instance.iHeightBoard || j >= GameManager.Instance.iWidthBoard)
				break;
		}
		if (oldCase) {
			i = winY;
			j = winX;
		}
		else {
			i = y;
			j = x;
		}
		while (GameManager.Instance.Board[i,j] == Player)
		{
			i--;
			j--;
			Align++;
			if (i < 0 || j < 0)
				break;
		}

		if (Align >= 5)
			youWin(Player, oldCase);

		Align = -1;
		if (oldCase) {
			i = winY;
			j = winX;
		}
		else {
			i = y;
			j = x;
		}
		//Diagonal Bottom->Top
		while (GameManager.Instance.Board[i,j] == Player)
		{
			i++;
			j--;
			Align++;
			if (i >= GameManager.Instance.iHeightBoard || j < 0)
				break;
		}
		if (oldCase) {
			i = winY;
			j = winX;
		}
		else {
			i = y;
			j = x;
		}
		while (GameManager.Instance.Board[i,j] == Player)
		{
			i--;
			j++;
			Align++;
			if (j >= GameManager.Instance.iWidthBoard || i < 0)
				break;
		}

		if (Align >= 5)
			youWin(Player, oldCase);

			

	}

	private void checkBoardState(int Height, int Width) {
		int Player1;
		int Player2;
		bool dTree = false;
		Height = (Height <= 5) ? 0 : Height - 5;
		Width = (Width <= 5) ? 0 : Width - 5; 
		int MaxHeight = (Height + 9 >= GameManager.Instance.iHeightBoard - 1) ? GameManager.Instance.iHeightBoard - 1 : Height + 9;
		int MaxWidth = (Width + 9 >= GameManager.Instance.iWidthBoard - 1) ? GameManager.Instance.iWidthBoard - 1 : Width + 9;

		if (GameManager.Instance.bPlayerOneTurn) {
			Player1 = GameManager.Stone.Black;
			Player2 = GameManager.Stone.White;
		}
		else {
			Player1 = GameManager.Stone.White;
			Player2 = GameManager.Stone.Black;
		}

		for (int i = Height; i <= MaxHeight; i++) {
			for (int j = Width; j <= MaxWidth; j++) {

				if (Rules.EmptyCase(GameManager.Instance.Board[i, j])) {
					if (GameManager.Instance.Board[i, j] != 0) {
						Rules.changeBoxState(j , i, Type.Empty);
					}
//					checkForbiddenBox(i, j);
					dTree = Rules.checkDoubleTreeBox(i, j);
					if (dTree && Rules.somethingToEatWithEmpty(Player1, Player2, i, j)) {
						dTree = false;
						if ((Player1 & GameManager.Stone.Black) != 0)
							GameManager.Instance.Board[i, j] -= GameManager.Stone.BlackDoubleTree;
						else
							GameManager.Instance.Board[i, j] -= GameManager.Stone.WhiteDoubleTree;
						Rules.changeBoxState(j , i, Type.Empty);
					}
				}
			}
		}
		
	}

	private bool checkStoneEaten() {
		
		bool eat = false;
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

		if (x >= 3) // Eat Left
			if (GameManager.Instance.Board[y, x - 1] == Player2 && GameManager.Instance.Board[y, x - 2] == Player2 && GameManager.Instance.Board[y, x - 3] == Player1)
			{
				eat = true;
				Rules.changeBoxState(x - 1, y, Type.Eat);
				Rules.changeBoxState(x - 2, y, Type.Eat);
			}
		if (x <= GameManager.Instance.iWidthBoard - 3) // Eat Right
			if (GameManager.Instance.Board[y, x + 1] == Player2 && GameManager.Instance.Board[y, x + 2] == Player2 && GameManager.Instance.Board[y, x + 3] == Player1)
			{
				eat = true;
				Rules.changeBoxState(x + 1, y, Type.Eat);
				Rules.changeBoxState(x + 2, y, Type.Eat);
			}
		if (y >= 3) // Eat Top
			if (GameManager.Instance.Board[y - 1, x] == Player2 && GameManager.Instance.Board[y - 2, x] == Player2 && GameManager.Instance.Board[y - 3, x] == Player1)
			{
				eat = true;
				Rules.changeBoxState(x, y - 1, Type.Eat);
				Rules.changeBoxState(x, y - 2, Type.Eat);
			}
		if (y < GameManager.Instance.iHeightBoard - 3) // Eat Bottom
			if (GameManager.Instance.Board[y + 1, x] == Player2 && GameManager.Instance.Board[y + 2, x] == Player2 && GameManager.Instance.Board[y + 3, x] == Player1)
			{
				eat = true;
				Rules.changeBoxState(x, y + 1, Type.Eat);
				Rules.changeBoxState(x, y + 2, Type.Eat);
			}
		if (x >= 3 && y >= 3) // Eat Top Left
			if (GameManager.Instance.Board[y - 1, x - 1] == Player2 && GameManager.Instance.Board[y - 2, x - 2] == Player2 && GameManager.Instance.Board[y - 3, x - 3] == Player1)
			{
				eat = true;
				Rules.changeBoxState(x - 1, y - 1, Type.Eat);
				Rules.changeBoxState(x - 2, y - 2, Type.Eat);
			}
		if (x < GameManager.Instance.iWidthBoard - 3 && y >= 3) // Eat Top Right
			if (GameManager.Instance.Board[y - 1, x + 1] == Player2 && GameManager.Instance.Board[y - 2, x + 2] == Player2 && GameManager.Instance.Board[y - 3, x + 3] == Player1)
			{
				eat = true;
				Rules.changeBoxState(x + 1, y - 1, Type.Eat);
				Rules.changeBoxState(x + 2, y - 2, Type.Eat);
			}
		if (x < GameManager.Instance.iWidthBoard - 3 && y < GameManager.Instance.iHeightBoard - 3) // Eat Bottom Right
			if (GameManager.Instance.Board[y + 1, x + 1] == Player2 && GameManager.Instance.Board[y + 2, x + 2] == Player2 && GameManager.Instance.Board[y + 3, x + 3] == Player1)
			{
				eat = true;
				Rules.changeBoxState(x + 1, y + 1, Type.Eat);
				Rules.changeBoxState(x + 2, y + 2, Type.Eat);
			}
		if (x >= 3 && y < GameManager.Instance.iHeightBoard - 3) // Eat Bottom Left
			if (GameManager.Instance.Board[y + 1, x - 1] == Player2 && GameManager.Instance.Board[y + 2, x - 2] == Player2 && GameManager.Instance.Board[y + 3, x - 3] == Player1)
			{
				eat = true;
				Rules.changeBoxState(x - 1, y + 1, Type.Eat);
				Rules.changeBoxState(x - 2, y + 2, Type.Eat);
			}
		return eat;
	}
}
