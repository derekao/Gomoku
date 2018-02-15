using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GameManager : MonoBehaviour {

	public class Stone { 
		static public int Empty = 0;
		static public int Black = 1;
		static public int White = 2;
		static public int WhiteForbidden = 4;
		static public int BlackForbidden = 8;
		static public int WhiteDoubleTree = 16;
		static public int BlackDoubleTree = 32;
	}

	static public int iWidthBoard = 19;
	static public int iHeightBoard = 19;
	
	static public List<int[,]> lBoardHisto;
	static public bool	bPlayerOneTurn = true;
	static public int iTurn = 0;
	static public int[,] Board;

	static public int BlackScore = 0;
	static public int WhiteScore = 0;
	static public bool BlackWin = false;
	static public bool WhiteWin = false;
	static GameObject PopUpWinPanel;

	// Use this for initialization
	void Awake () {
		if (lBoardHisto != null)
			lBoardHisto.Clear();
		else
		{
			lBoardHisto = new List<int[,]>();
			Board = new int[iHeightBoard, iWidthBoard];
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
