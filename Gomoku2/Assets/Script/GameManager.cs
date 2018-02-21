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
	}

	// Size of the Board
	public int iWidthBoard = 19;
	public int iHeightBoard = 19;
	
	// State of the Board
	public List<int> lPointHisto;
	public List<int[,]> lBoardHisto;
	public bool	bPlayerOneTurn = true;
	public int iTurn = 0;
	public int[,] Board;

	// Win Condition
	public int BlackScore = 0;
	public int WhiteScore = 0;
	public bool BlackWin = false;
	public bool WhiteWin = false;
	private
	GameObject PopUpWinPanel;

	// Use this for initialization
	void Awake () {
		Instance = this;
		if (lBoardHisto != null) {
			lBoardHisto.Clear();
			lPointHisto.Clear();
		}
		else
		{
			lPointHisto = new List<int>();
			lBoardHisto = new List<int[,]>();
			Board = new int[iHeightBoard, iWidthBoard];
			lPointHisto.Insert(0, 0);
			lBoardHisto.Insert(0, Board.Clone() as int[,]);
		}

		PopUpWinPanel = GameObject.Find("PopUpWin");
		PopUpWinPanel.SetActive(false);

		iTurn = 0;
		BlackScore = 0;
		WhiteScore = 0;
		BlackWin = false;
		WhiteWin = false;
		bPlayerOneTurn = true;
		for (int i = 0; i < iHeightBoard; i++)
		{
			for (int j = 0; j < iWidthBoard; j++)
			{
				Board[i,j] = Stone.Empty;
			}
		}
	}
	
	// Update is called once per frame
	void Update () {

		if ((BlackWin || BlackScore >= 10) && PopUpWinPanel.activeSelf == false)
		{
			PopUpWinPanel.SetActive(true);
			Text WinText = GameObject.Find("WinText").GetComponent<Text>();
			WinText.text = "Black has won";
		}
		if ((WhiteWin || WhiteScore >= 10) && PopUpWinPanel.activeSelf == false)
		{
			PopUpWinPanel.SetActive(true);
			Text WinText = GameObject.Find("WinText").GetComponent<Text>();
			WinText.text = "White has won";
		}
	}

}
