using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

/// <summary>
/// There must be only one instance of this class
///	The Instance is stocked in GameManager.Instance
/// </summary>
public class GameManager : MonoBehaviour {

	public static GameManager Instance;

	/// <summary>
	/// The class Stone is used to have multiple data in one Cell
	/// Use : (Cell & varriable) != 0 to check if the data is present in the Cell
	/// Use : Cell += varriable to add the data in the Cell
	/// Use : Cell = Stone.Empty to reset the Cell
	/// </summary>
	public class Stone { 
		static public int Empty = 0;
		static public int Black = 1;
		static public int White = 2;
		static public int WhiteForbidden = 4;
		static public int BlackForbidden = 8;
		static public int WhiteDoubleTree = 16;
		static public int BlackDoubleTree = 32;
		static public int PlayArea = 64;
	}

	public class BoardHistoric
	{
		public bool	bPlayerOneTurn = true;
		public int iTurn = 0;
		public int[,] Board;
		public int BlackScore = 0;
		public int WhiteScore = 0;
		public bool BlackWin = false;
		public bool WhiteWin = false;
		public  int winX;
		public  int winY;
		public bool hasWon;

		public BoardHistoric Clone()
		{
			BoardHistoric tmp = new BoardHistoric();
			tmp.bPlayerOneTurn = bPlayerOneTurn;
			tmp.iTurn = iTurn;
			tmp.Board = Board.Clone() as int [,];
			tmp.BlackScore = BlackScore;
			tmp.WhiteScore = WhiteScore;
			tmp.BlackWin = BlackWin;
			tmp.WhiteWin = WhiteWin;
			tmp.winX = winX;
			tmp.winY = winY;
			tmp.hasWon = hasWon;
			return tmp;
		}
	}

	private GameObject PopUpWinPanel;
	public bool LockPopUp = false;
	public bool ActivateIA = true;
	public BoardHistoric currentState;

	public Text DepthText;
	public Text ValueText;
	public Text TimeText;

	// Size of the Board
	public int iWidthBoard = 19;
	public int iHeightBoard = 19;
	public int PlayAreaSize = 2;
	public bool IATurn = false;
	
	// State of the Board
	public List<BoardHistoric> lBoardHisto;
	public List<int[]> EatCoord;

	// Use this for initialization
	void Awake () {
		Instance = this;
		currentState = new BoardHistoric();
		if (lBoardHisto != null) {
			lBoardHisto.Clear();
			EatCoord.Clear();
		}
		else
		{
			lBoardHisto = new List<BoardHistoric>();
			currentState.Board = new int[iHeightBoard, iWidthBoard];
			lBoardHisto.Insert(0, currentState.Clone());
			EatCoord = new List<int[]>();
		}

		PopUpWinPanel = GameObject.Find("PopUpWin");
		PopUpWinPanel.SetActive(false);

		GameObject tmp = GameObject.Find("DepthScore");
		DepthText = tmp.GetComponent<Text>();
		tmp = GameObject.Find("ValueScore");
		ValueText = tmp.GetComponent<Text>();
		tmp = GameObject.Find("TimeScore");
		TimeText = tmp.GetComponent<Text>();

		currentState.iTurn = 0;
		currentState.BlackScore = 0;
		currentState.WhiteScore = 0;
		currentState.BlackWin = false;
		currentState.WhiteWin = false;
		currentState.bPlayerOneTurn = true;
		for (int i = 0; i < iHeightBoard; i++)
		{
			for (int j = 0; j < iWidthBoard; j++)
			{
				currentState.Board[i,j] = Stone.Empty;
			}
		}
	}
	
	// Update is called once per frame
	void Update () {

		if ((currentState.BlackWin || currentState.BlackScore >= 10) && PopUpWinPanel.activeSelf == false && !LockPopUp)
		{
			PopUpWinPanel.SetActive(true);
			Text WinText = GameObject.Find("WinText").GetComponent<Text>();
			WinText.text = "Black has won";
		}
		if ((currentState.WhiteWin || currentState.WhiteScore >= 10) && PopUpWinPanel.activeSelf == false && !LockPopUp)
		{
			PopUpWinPanel.SetActive(true);
			Text WinText = GameObject.Find("WinText").GetComponent<Text>();
			WinText.text = "White has won";
		}
		if (IATurn == true)
		{	
			IATurn = false;
			IA.ComputerPlay();
		}
	}

}
