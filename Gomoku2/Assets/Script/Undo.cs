using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Undo : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	public void OnUndo() {

		if (GameManager.iTurn == 1)
			return ;
		GameManager.Board = GameManager.lBoardHisto[GameManager.iTurn - 2];
		GameManager.lBoardHisto.RemoveAt(GameManager.iTurn - 1);
		GameManager.iTurn--;
		GameManager.bPlayerOneTurn = !GameManager.bPlayerOneTurn;
		PlayStone.DisplayBoard(true);
	}
}
