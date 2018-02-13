using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour {

	public List<Stone[,]> lBoardHisto;
	public enum Stone { Empty, Black, White };
	public bool	bPlayerOneTurn;
	public int iWidthBoard = 19;
	public int iHeightBoard = 19;
	public int iTurn = 0;
	public Stone[,] Board;
	// Use this for initialization
	void Start () {
		lBoardHisto = new List<Stone[,]>();
		Board = new Stone[iHeightBoard, iWidthBoard];
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
