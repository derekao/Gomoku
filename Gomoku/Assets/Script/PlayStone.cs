using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayStone : MonoBehaviour {

	private GameManager gameManager;

	private GameObject BlackStone;
	private GameObject WhiteStone;
	private Image BlackStoneImage;
	private Image WhiteStoneImage;
	void Start() {

		gameManager = GameObject.Find("Main Camera").GetComponent<GameManager>();

		for (int i = 0; i < this.transform.childCount; i++)
		{
			Transform result = this.transform.GetChild(i);
			if (result.name == "BlackStone")
			{
				BlackStone = result.gameObject;
			}
			else if (result.name == "WhiteStone")
			{
				WhiteStone = result.gameObject;
			}
			
		}

		BlackStoneImage = BlackStone.GetComponent<Image>();
		WhiteStoneImage = WhiteStone.GetComponent<Image>();

		if (!BlackStoneImage|| !WhiteStoneImage)
		{
			Debug.Log("Wrong Stone Init");
		}

	}

	public void OnClick() {
		if (gameManager.bPlayerOneTurn) {
			OnBlackPlay();
		}
		else {
			OnWhitePlay();
		}
	}
	private void OnBlackPlay() {

		if (!WhiteStoneImage.enabled && !BlackStoneImage.enabled) 
		{
			string szIndex = this.name.Substring(7, name.Length - 8);
			int iIndex = int.Parse(szIndex) - 1;

			BlackStoneImage.enabled = true;
			gameManager.bPlayerOneTurn = false;
			gameManager.Board[iIndex / gameManager.iHeightBoard, iIndex % gameManager.iWidthBoard] = GameManager.Stone.Black;
		}

	}

	private void OnWhitePlay() {

		if (!WhiteStoneImage.enabled && !BlackStoneImage.enabled)
		{
			string szIndex = this.name.Substring(7, name.Length - 8);
			int iIndex = int.Parse(szIndex) - 1;

			WhiteStoneImage.enabled = true;
			gameManager.bPlayerOneTurn = true;
			gameManager.Board[iIndex / gameManager.iHeightBoard, iIndex % gameManager.iWidthBoard] = GameManager.Stone.White;
		}

	}

	public void OnDeleteMove() {

		if (!WhiteStoneImage.enabled)
		{
			WhiteStoneImage.enabled = false;
		}

		if (!BlackStoneImage.enabled)
		{
			BlackStoneImage.enabled = false;
		}

		string szIndex = this.name.Substring(7, name.Length - 8);
		int iIndex = int.Parse(szIndex) - 1;
		gameManager.Board[iIndex / gameManager.iHeightBoard, iIndex % gameManager.iWidthBoard] = GameManager.Stone.Empty;

	}
}
