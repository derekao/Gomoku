using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UpdateScore : MonoBehaviour {

	private int iScore;
	private bool Black;
	private Text Score;

	// Use this for initialization
	void Start () {

		if (gameObject.name == "BlackScore")
			Black = true;
		else if (gameObject.name == "WhiteScore")
			Black = false;
		else
			Debug.Log("Wrong UpdateScore Object");

		if (Black)
		{
			iScore = GameManager.BlackScore;
		}
		else
		{
			iScore = GameManager.WhiteScore;
		}

		Score = gameObject.GetComponent<Text>();
	}
	
	// Update is called once per frame
	void Update () {

		if (Black)
		{
			if (iScore != GameManager.BlackScore)
			{
				iScore = GameManager.BlackScore;
				Score.text = iScore.ToString();
			}
		}
		else
		{
			if (iScore != GameManager.WhiteScore)
			{
				iScore = GameManager.WhiteScore;
				Score.text = iScore.ToString();
			}
		}
		
	}
}
