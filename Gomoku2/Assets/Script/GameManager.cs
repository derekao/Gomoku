﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

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

	// Use this for initialization
	void Start () {
		lBoardHisto = new List<int[,]>();
		Board = new int[iHeightBoard, iWidthBoard];
	}
	
	// Update is called once per frame
	void Update () {
		
	}

}
