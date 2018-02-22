using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Undo : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	public void OnUndo() {
		if (GameManager.Instance.currentState.iTurn <= 0)
			return ;
		GameManager.Instance.lBoardHisto.RemoveAt(0);
		GameManager.Instance.currentState = GameManager.Instance.lBoardHisto[0].Clone();
		Rules.DisplayBoard(true);
	}
}
