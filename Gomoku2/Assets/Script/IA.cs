﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices; // Dll

public class IA : MonoBehaviour {

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
	[StructLayout(LayoutKind.Sequential)]
	public struct CoordIA
	{
		public int y;
		public int x;
	};

	[DllImport("Extern.dll")]
	public static extern CoordIA IAPlay(GameStatus Game);

	static public void ComputerPlay()
	{
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
		CoordIA test = IAPlay(game);
		Debug.Log("y = " + test.y + " et x = " +  test.x);
		int id = test.x + test.y * GameManager.Instance.iWidthBoard + 1;
		GameObject box = GameObject.Find("Stone (" + id + ")");
		PlayStone Move = box.GetComponent<PlayStone>();
		if (!GameManager.Instance.currentState.bPlayerOneTurn)
			Move.OnWhitePlay();
		else
			Move.OnBlackPlay();
	}


}