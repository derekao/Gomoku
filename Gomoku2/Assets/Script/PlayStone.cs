using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Runtime.InteropServices; // Dll

public class PlayStone : MonoBehaviour {

	[StructLayout(LayoutKind.Sequential)]
	public struct GameStatus
	{
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 361)]
		public int[] Board;
		[MarshalAs(UnmanagedType.U1)]
		public bool bPlayerOneTurn;
		[MarshalAs(UnmanagedType.U1)]
		public bool HasWon;
		public int WhiteScore;
		public int BlackScore;
		public int WinY;
		public int WinX;
	}

	[DllImport("Extern.dll")]
	public static extern bool CheckDoubleTree(int y, int x, GameStatus Game);

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
		if (GameManager.Instance.currentState.bPlayerOneTurn) {
			OnBlackPlay();
		}
		else {
			OnWhitePlay();
		}
		GameStatus game;
		game.Board = new int[GameManager.Instance.iHeightBoard * GameManager.Instance.iWidthBoard];
		game.bPlayerOneTurn = GameManager.Instance.currentState.bPlayerOneTurn;
		game.HasWon = GameManager.Instance.currentState.hasWon;
		game.WhiteScore = GameManager.Instance.currentState.WhiteScore;
		game.BlackScore = GameManager.Instance.currentState.BlackScore;
		game.WinY = GameManager.Instance.currentState.winY;
		game.WinX = GameManager.Instance.currentState.winX;
		for (int i = 0; i < GameManager.Instance.iHeightBoard; i++)
		{
			for (int j = 0; j < GameManager.Instance.iWidthBoard; j++)
			{
				game.Board[i * GameManager.Instance.iWidthBoard + j] = GameManager.Instance.currentState.Board[i,j];
			}
		}
		Debug.Log(CheckDoubleTree(9, 9, game));
	}

	private void OnBlackPlay() {

		if (!WhiteStoneImage.enabled && !BlackStoneImage.enabled && !ForbiddenImage.enabled && !DoubleTreeImage.enabled) 
		{
			checkStoneEaten();
			BlackStoneImage.enabled = true;
			GameManager.Instance.currentState.bPlayerOneTurn = false;
			GameManager.Instance.currentState.Board[y, x] = GameManager.Stone.Black;
			GameManager.Instance.currentState.iTurn += 1;
			GameManager.BoardHistoric tmp = GameManager.Instance.currentState.Clone();
			GameManager.Instance.lBoardHisto.Insert(0, tmp);
			int win;
			if (GameManager.Instance.currentState.hasWon)
			{
				win = Rules.CheckWin(GameManager.Stone.White, GameManager.Instance.currentState.winY, GameManager.Instance.currentState.winX);
				if (win != 0)
				{
					Rules.youWin(GameManager.Stone.White, GameManager.Stone.Black, GameManager.Instance.currentState.winY, GameManager.Instance.currentState.winX);
				}
			}
			win = Rules.CheckWin(GameManager.Stone.Black, y, x);
			if (win != 0)
			{
					Rules.youWin(GameManager.Stone.Black, GameManager.Stone.White, y, x);
			}
			checkBoardState(y, x);
			Rules.DisplayBoard();
		}

	}

	private void OnWhitePlay() {

		if (!WhiteStoneImage.enabled && !BlackStoneImage.enabled && !ForbiddenImage.enabled && !DoubleTreeImage.enabled)
		{
			checkStoneEaten();
			WhiteStoneImage.enabled = true;
			GameManager.Instance.currentState.bPlayerOneTurn = true;
			GameManager.Instance.currentState.iTurn += 1;
			GameManager.Instance.currentState.Board[y, x] = GameManager.Stone.White;
			GameManager.BoardHistoric tmp = GameManager.Instance.currentState.Clone();
			GameManager.Instance.lBoardHisto.Insert(0, tmp);
			int win;
			if (GameManager.Instance.currentState.hasWon)
			{
				win = Rules.CheckWin(GameManager.Stone.Black, GameManager.Instance.currentState.winY, GameManager.Instance.currentState.winX);
				if (win != 0)
				{
					Rules.youWin(GameManager.Stone.Black, GameManager.Stone.White, GameManager.Instance.currentState.winY, GameManager.Instance.currentState.winX);
				}
			}
			win = Rules.CheckWin(GameManager.Stone.White, y, x);
			if (win != 0)
			{
					Rules.youWin(GameManager.Stone.White, GameManager.Stone.Black, y, x);
			}
			checkBoardState(y, x);
			Rules.DisplayBoard();
		}

	}

	private void checkBoardState(int Height, int Width) {
		int Player1;
		int Player2;
		bool dTree = false;
		Height = (Height <= 5) ? 0 : Height - 5;
		Width = (Width <= 5) ? 0 : Width - 5; 
		int MaxHeight = (Height + 10 >= GameManager.Instance.iHeightBoard - 1) ? GameManager.Instance.iHeightBoard - 1 : Height + 10;
		int MaxWidth = (Width + 10 >= GameManager.Instance.iWidthBoard - 1) ? GameManager.Instance.iWidthBoard - 1 : Width + 10;

		if (GameManager.Instance.currentState.bPlayerOneTurn) {
			Player1 = GameManager.Stone.Black;
			Player2 = GameManager.Stone.White;
		}
		else {
			Player1 = GameManager.Stone.White;
			Player2 = GameManager.Stone.Black;
		}

		for (int i = Height; i <= MaxHeight; i++) {
			for (int j = Width; j <= MaxWidth; j++) {

				if (Rules.EmptyCase(GameManager.Instance.currentState.Board[i, j])) {
					if (GameManager.Instance.currentState.Board[i, j] != 0) {
						Rules.changeBoxState(j , i, Type.Empty);
					}
//					checkForbiddenBox(i, j);
					int win = Rules.CheckWin(Player2, i, j);
					dTree = Rules.checkDoubleTreeBox(i, j);
					if ((dTree && Rules.somethingToEatWithEmpty(Player1, Player2, i, j)) && win == 0 ) 
					{
						dTree = false;
						if ((Player1 & GameManager.Stone.Black) != 0)
							GameManager.Instance.currentState.Board[i, j] -= GameManager.Stone.BlackDoubleTree;
						else
							GameManager.Instance.currentState.Board[i, j] -= GameManager.Stone.WhiteDoubleTree;
						Rules.changeBoxState(j , i, Type.Empty);
						
					}
					else if (win != 0)
					{
						GameManager.Instance.currentState.Board[i, j] = GameManager.Stone.Empty;
						Rules.changeBoxState(j , i, Type.Empty);
					}
				}
			}
		}
		
	}

	private void checkStoneEaten() {
		
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

		if (x >= 3) // Eat Left
			if (GameManager.Instance.currentState.Board[y, x - 1] == Player2 && GameManager.Instance.currentState.Board[y, x - 2] == Player2 && GameManager.Instance.currentState.Board[y, x - 3] == Player1)
			{
				Rules.changeBoxState(x - 1, y, Type.Eat);
				Rules.changeBoxState(x - 2, y, Type.Eat);
			}
		if (x <= GameManager.Instance.iWidthBoard - 3) // Eat Right
			if (GameManager.Instance.currentState.Board[y, x + 1] == Player2 && GameManager.Instance.currentState.Board[y, x + 2] == Player2 && GameManager.Instance.currentState.Board[y, x + 3] == Player1)
			{
				Rules.changeBoxState(x + 1, y, Type.Eat);
				Rules.changeBoxState(x + 2, y, Type.Eat);
			}
		if (y >= 3) // Eat Top
			if (GameManager.Instance.currentState.Board[y - 1, x] == Player2 && GameManager.Instance.currentState.Board[y - 2, x] == Player2 && GameManager.Instance.currentState.Board[y - 3, x] == Player1)
			{
				Rules.changeBoxState(x, y - 1, Type.Eat);
				Rules.changeBoxState(x, y - 2, Type.Eat);
			}
		if (y < GameManager.Instance.iHeightBoard - 3) // Eat Bottom
			if (GameManager.Instance.currentState.Board[y + 1, x] == Player2 && GameManager.Instance.currentState.Board[y + 2, x] == Player2 && GameManager.Instance.currentState.Board[y + 3, x] == Player1)
			{
				Rules.changeBoxState(x, y + 1, Type.Eat);
				Rules.changeBoxState(x, y + 2, Type.Eat);
			}
		if (x >= 3 && y >= 3) // Eat Top Left
			if (GameManager.Instance.currentState.Board[y - 1, x - 1] == Player2 && GameManager.Instance.currentState.Board[y - 2, x - 2] == Player2 && GameManager.Instance.currentState.Board[y - 3, x - 3] == Player1)
			{
				Rules.changeBoxState(x - 1, y - 1, Type.Eat);
				Rules.changeBoxState(x - 2, y - 2, Type.Eat);
			}
		if (x < GameManager.Instance.iWidthBoard - 3 && y >= 3) // Eat Top Right
			if (GameManager.Instance.currentState.Board[y - 1, x + 1] == Player2 && GameManager.Instance.currentState.Board[y - 2, x + 2] == Player2 && GameManager.Instance.currentState.Board[y - 3, x + 3] == Player1)
			{
				Rules.changeBoxState(x + 1, y - 1, Type.Eat);
				Rules.changeBoxState(x + 2, y - 2, Type.Eat);
			}
		if (x < GameManager.Instance.iWidthBoard - 3 && y < GameManager.Instance.iHeightBoard - 3) // Eat Bottom Right
			if (GameManager.Instance.currentState.Board[y + 1, x + 1] == Player2 && GameManager.Instance.currentState.Board[y + 2, x + 2] == Player2 && GameManager.Instance.currentState.Board[y + 3, x + 3] == Player1)
			{
				Rules.changeBoxState(x + 1, y + 1, Type.Eat);
				Rules.changeBoxState(x + 2, y + 2, Type.Eat);
			}
		if (x >= 3 && y < GameManager.Instance.iHeightBoard - 3) // Eat Bottom Left
			if (GameManager.Instance.currentState.Board[y + 1, x - 1] == Player2 && GameManager.Instance.currentState.Board[y + 2, x - 2] == Player2 && GameManager.Instance.currentState.Board[y + 3, x - 3] == Player1)
			{
				Rules.changeBoxState(x - 1, y + 1, Type.Eat);
				Rules.changeBoxState(x - 2, y + 2, Type.Eat);
			}
	}
}
