using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Undo : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	public void OnUndo() {
		if (GameManager.Instance.iTurn <= 0)
			return ;
		GameManager.Instance.lBoardHisto.RemoveAt(0);
		GameManager.Instance.Board = GameManager.Instance.lBoardHisto[0].Clone() as int[,];
		GameManager.Instance.iTurn--;
		GameManager.Instance.bPlayerOneTurn = !GameManager.Instance.bPlayerOneTurn;
		if (GameManager.Instance.lPointHisto[0] == 1) {
			if (GameManager.Instance.bPlayerOneTurn)
				GameManager.Instance.WhiteScore -= 2;
			else
				GameManager.Instance.BlackScore -= 2;
		}
		GameManager.Instance.lPointHisto.RemoveAt(0);
		GameManager.Instance.BlackWin = false;
		GameManager.Instance.WhiteWin = false;
		GameManager.Instance.BlackScore = 0;
		GameManager.Instance.WhiteScore = 0;
		Rules.DisplayBoard(true);
	}
}
