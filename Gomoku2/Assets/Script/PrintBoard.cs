using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PrintBoard : MonoBehaviour {

	public void OnClickBoard () {

		string szBoard = "";
		for (int i = 0; i < GameManager.iHeightBoard; i++)
		{
			for (int j = 0; j < GameManager.iWidthBoard; j++)
			{
				szBoard += GameManager.Board[i,j].ToString();
				szBoard += ' ';
			}
			Debug.Log(szBoard);
			szBoard = "";
		}
	}
}
