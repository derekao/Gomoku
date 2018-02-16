using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Undo : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	public void OnUndo() {
		if (GameManager.iTurn <= 0)
			return ;
		GameManager.lBoardHisto.RemoveAt(0);
		GameManager.Board = GameManager.lBoardHisto[0].Clone() as int[,];
		GameManager.iTurn--;
		GameManager.bPlayerOneTurn = !GameManager.bPlayerOneTurn;
		GameManager.BlackWin = false;
		GameManager.WhiteWin = false;
		GameManager.BlackScore = 0;
		GameManager.WhiteScore = 0;
		PlayStone.DisplayBoard(true);
	}
}
