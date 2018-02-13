using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayStone : MonoBehaviour {

	private GameManager gameManager;

	private GameObject BlackStone;
	private GameObject WhiteStone;
	private GameObject Forbiden;
	private Image BlackStoneImage;
	private Image WhiteStoneImage;
	private Image ForbidenImage;

	private GameObject tmpBlackStone;
	private GameObject tmpWhiteStone;
	private GameObject tmpForbiden;
	private Image tmpBlackStoneImage;
	private Image tmpWhiteStoneImage;
	private Image tmpForbidenImage;

	void Start() {

		gameManager = GameObject.Find("Main Camera").GetComponent<GameManager>();
		for (int i = 0; i < this.transform.childCount; i++)
		{
			Transform result = this.transform.GetChild(i);
			if (result.name == "BlackStone")
			{
				BlackStone = result.gameObject;
				BlackStoneImage = BlackStone.GetComponent<Image>();
			}
			else if (result.name == "WhiteStone")
			{
				WhiteStone = result.gameObject;
				WhiteStoneImage = WhiteStone.GetComponent<Image>();
			}
			else if (result.name == "Forbiden")
			{
				Forbiden = result.gameObject;
				ForbidenImage = Forbiden.GetComponent<Image>();
			}
		}

		if (!BlackStoneImage || !WhiteStoneImage || !ForbidenImage)
		{
			Debug.Log("Wrong Stone Init");
		}

	}

	public void OnClick() {
		Debug.Log(gameManager.iTurn);
		if (gameManager.iTurn >= 10) {
			Debug.Log("test");
			gameManager.Board = gameManager.lBoardHisto[0];
		}
		else if (gameManager.bPlayerOneTurn) {
			OnBlackPlay();
		}
		else {
			OnWhitePlay();
		}
		checkBoardState();
		// changeBoxState(2, 2);
	}
	private void OnBlackPlay() {

		if (!WhiteStoneImage.enabled && !BlackStoneImage.enabled && !ForbidenImage.enabled) 
		{
			string szIndex = this.name.Substring(7, name.Length - 8);
			int iIndex = int.Parse(szIndex) - 1;

			BlackStoneImage.enabled = true;
			gameManager.bPlayerOneTurn = false;
			gameManager.Board[iIndex / gameManager.iHeightBoard, iIndex % gameManager.iWidthBoard] = GameManager.Stone.Black;
			gameManager.lBoardHisto.Add(gameManager.Board);
			gameManager.iTurn += 1;
		}

	}

	private void OnWhitePlay() {

		if (!WhiteStoneImage.enabled && !BlackStoneImage.enabled && !ForbidenImage.enabled)
		{
			string szIndex = this.name.Substring(7, name.Length - 8);
			int iIndex = int.Parse(szIndex) - 1;

			WhiteStoneImage.enabled = true;
			gameManager.bPlayerOneTurn = true;
			gameManager.Board[iIndex / gameManager.iHeightBoard, iIndex % gameManager.iWidthBoard] = GameManager.Stone.White;
			gameManager.lBoardHisto.Add(gameManager.Board);
			gameManager.iTurn += 1;
		}

	}

	private void checkBoardState() {
		for (int i = 0; i < gameManager.iHeightBoard; i++) {
			for (int j = 0; j < gameManager.iWidthBoard; j++) {
				// if (gameManager.Board[i,j].ToString() == "Empty")
					// Debug.Log(gameManager);
			}
		}
	}

	private void checkStoneEaten(int y, int x) {

	}

	private void checkForbidenCase(int y, int x) {

	}

	private void changeBoxState(int id, int type) { //Type: 0 => eat, 1 => Forbiden, 2 => DoubleTree

		GameObject box = GameObject.Find("Stone (" + id + ")");

		for (int i = 0; i < box.transform.childCount; i++)
		{
			Transform result = box.transform.GetChild(i);
			if (result.name == "BlackStone")
			{
				tmpBlackStone = result.gameObject;
				tmpBlackStoneImage = tmpBlackStone.GetComponent<Image>();
			}
			else if (result.name == "WhiteStone")
			{
				tmpWhiteStone = result.gameObject;
				tmpWhiteStoneImage = tmpWhiteStone.GetComponent<Image>();
			}
			else if (result.name == "Forbiden")
			{
				tmpForbiden = result.gameObject;
				tmpForbidenImage = tmpForbiden.GetComponent<Image>();
			}
		}
		if (!tmpBlackStoneImage || !tmpWhiteStoneImage || !tmpForbidenImage)
			Debug.Log("Wrong Stone Init");
		else if (type == 0) {
			if (gameManager.bPlayerOneTurn)
				tmpWhiteStoneImage.enabled = false;
			else
				tmpBlackStoneImage.enabled = false;
		}
		else if (type == 1)
			tmpWhiteStoneImage.enabled = true;
		else if (type == 2)
			tmpWhiteStoneImage.enabled = true;
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
