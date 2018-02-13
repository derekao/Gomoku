using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PrintBoard : MonoBehaviour {

	private GameManager gameManager;

	void Start() {

		gameManager = GameObject.Find("Main Camera").GetComponent<GameManager>();
	}
	
	public void OnClickBoard () {

		string szBoard = "";
		for (int i = 0; i < gameManager.iHeightBoard; i++)
		{
			for (int j = 0; j < gameManager.iWidthBoard; j++)
			{
				szBoard += gameManager.Board[i,j].ToString();
				szBoard += ' ';
			}
			Debug.Log(szBoard);
			szBoard = "";
		}
	}
}
