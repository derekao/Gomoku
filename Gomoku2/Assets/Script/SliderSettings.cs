using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SliderSettings : MonoBehaviour {

	Text SliderValue;
	public string sz;
	public bool isInt;
	public int SliderType;

	// Use this for initialization
	void Start () {
		SliderValue = GetComponent<Text>();

		if (SliderType == 0)
			TextUpdate(PlayerPrefs.GetInt("Depth"));
		else if (SliderType == 1)
			TextUpdate(PlayerPrefs.GetFloat("Timer"));
		else if (SliderType == 2)
			TextUpdate(PlayerPrefs.GetInt("Move"));
		else if (SliderType == 3)
			TextUpdate(PlayerPrefs.GetInt("Algo"));
	}
	
	public void TextUpdate(float Value)
	{
		if (sz == "Algo : ")
		{
			if (Mathf.RoundToInt(Value) == 0)
				SliderValue.text = sz + "MTDF";
			else if (Mathf.RoundToInt(Value) == 1)
				SliderValue.text = sz + "Minimax";
			else if (Mathf.RoundToInt(Value) == 2)
				SliderValue.text = sz + "AlphaBeta";
			else if (Mathf.RoundToInt(Value) == 3)
				SliderValue.text = sz + "Iterative AB";
			else if (Mathf.RoundToInt(Value) == 4)
				SliderValue.text = sz + "Negascout";
			else if (Mathf.RoundToInt(Value) == 5)
				SliderValue.text = sz + "Iterative Neg";
			else if (Mathf.RoundToInt(Value) == 6)
				SliderValue.text = sz + "Monte Carlo";
		}
		else
		{
			if (isInt)
				SliderValue.text = sz + Mathf.RoundToInt(Value);
			else
				SliderValue.text = sz + Math.Round((Decimal)Value, 1, MidpointRounding.AwayFromZero);
		}
	}
}
