using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PrintBoard : MonoBehaviour {

	public void OnClickBoard () {

		string szBoard = "";
		for (int i = 0; i < GameManager.Instance.iHeightBoard; i++)
		{
			for (int j = 0; j < GameManager.Instance.iWidthBoard; j++)
			{
				szBoard += GameManager.Instance.currentState.Board[i,j].ToString();
				szBoard += ' ';
			}
			Debug.Log(szBoard);
			szBoard = "";
		}

		Debug.Log(GameManager.Instance.currentState.BlackScore + " et " + GameManager.Instance.currentState.WhiteScore + " et " + GameManager.Instance.currentState.BlackWin + " et " + GameManager.Instance.currentState.WhiteWin + " et Turn = " + GameManager.Instance.currentState.iTurn + " et " + GameManager.Instance.lBoardHisto.Count);
	}
}
