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
				szBoard += GameManager.Instance.Board[i,j].ToString();
				szBoard += ' ';
			}
			Debug.Log(szBoard);
			szBoard = "";
		}

		Debug.Log(GameManager.Instance.BlackScore + " et " + GameManager.Instance.WhiteScore + " et " + GameManager.Instance.BlackWin + " et " + GameManager.Instance.WhiteWin);
	}
}
