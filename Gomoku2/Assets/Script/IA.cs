using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
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
		public int Depth;
		public double Timer;
		public int Algo;
		public int MaxMove;
	}
	[StructLayout(LayoutKind.Sequential)]
	public struct CoordIA
	{
		public int y;
		public int x;
		public int Depth;
		public double Timer;
		public int Value;
	}

	[DllImport("Extern.dll")]
	public static extern CoordIA IAPlay(GameStatus Game);

	static public void ComputerPlay()
	{
		if (GameManager.Instance.currentState.BlackWin || GameManager.Instance.currentState.BlackScore >= 10 || GameManager.Instance.currentState.WhiteWin || GameManager.Instance.currentState.WhiteScore >= 10)
			return ;
		GameStatus game;
		game.Board = new int[GameManager.Instance.iHeightBoard * GameManager.Instance.iWidthBoard];
		game.bPlayerOneTurn = GameManager.Instance.currentState.bPlayerOneTurn;
		game.HasWon = GameManager.Instance.currentState.hasWon;
		game.WhiteScore = GameManager.Instance.currentState.WhiteScore;
		game.BlackScore = GameManager.Instance.currentState.BlackScore;
		game.WinY = GameManager.Instance.currentState.winY;
		game.WinX = GameManager.Instance.currentState.winX;
		game.Depth = PlayerPrefs.GetInt("Depth");
		game.Timer = PlayerPrefs.GetFloat("Timer");
		game.Algo = PlayerPrefs.GetInt("Algo");
		game.MaxMove = PlayerPrefs.GetInt("Move");

		if (game.Depth < 2 || game.Depth> 30)
			game.Depth = 2;
		if (game.Timer < 0.5f || game.Timer > 10.0f)
			game.Timer = 0.5f;
		if (game.MaxMove < 3 || game.MaxMove > 100)
			game.MaxMove = 3;
		if (game.Algo  < 0 || game.Algo  > 7)
			game.Algo  = 0;

		for (int i = 0; i < GameManager.Instance.iHeightBoard; i++)
		{
			for (int j = 0; j < GameManager.Instance.iWidthBoard; j++)
			{
				game.Board[i * GameManager.Instance.iWidthBoard + j] = GameManager.Instance.currentState.Board[i,j];
			}
		}
		CoordIA test = IAPlay(game);
		Debug.Log("y = " + test.y + " et x = " +  test.x + " et Depth = " + test.Depth + " et Time = " + test.Timer + " et Value = " + test.Value);
		GameManager.Instance.DepthText.text = test.Depth.ToString();
		GameManager.Instance.ValueText.text = test.Value.ToString();
		GameManager.Instance.TimeText.text = test.Timer.ToString();
		int id = test.x + test.y * GameManager.Instance.iWidthBoard + 1;
		GameObject box = GameObject.Find("Stone (" + id + ")");
		PlayStone Move = box.GetComponent<PlayStone>();
		if (!GameManager.Instance.currentState.bPlayerOneTurn)
			Move.OnWhitePlay();
		else
			Move.OnBlackPlay();
	}

	public void ForcePlay()
	{
		GameManager.Instance.IATurn = true;
	}


}
