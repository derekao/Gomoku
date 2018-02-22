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
			iScore = GameManager.Instance.currentState.BlackScore;
		}
		else
		{
			iScore = GameManager.Instance.currentState.WhiteScore;
		}

		Score = gameObject.GetComponent<Text>();
	}
	
	// Update is called once per frame
	void Update () {

		if (Black)
		{
			if (iScore != GameManager.Instance.currentState.BlackScore)
			{
				iScore = GameManager.Instance.currentState.BlackScore;
				Score.text = iScore.ToString();
			}
		}
		else
		{
			if (iScore != GameManager.Instance.currentState.WhiteScore)
			{
				iScore = GameManager.Instance.currentState.WhiteScore;
				Score.text = iScore.ToString();
			}
		}
		
	}
}
