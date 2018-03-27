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
		{
			int n = PlayerPrefs.GetInt("Depth");
			if (n < 2 || n > 30)
				TextUpdate(2);
			else
				TextUpdate(n);
		}
		else if (SliderType == 1)
		{
			float f = PlayerPrefs.GetFloat("Timer");
			if (f < 0.5f || f > 10.0f)
				TextUpdate(0.5f);
			else
				TextUpdate(f);
		}
		else if (SliderType == 2)
		{
			int n = PlayerPrefs.GetInt("Move");
			if (n < 3 || n > 100)
				TextUpdate(3);
			else
				TextUpdate(n);
		}
		else if (SliderType == 3)
		{
			int n = PlayerPrefs.GetInt("Algo");
			if (n < 0 || n > 7)
				TextUpdate(0);
			else
				TextUpdate(n);;
		}
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
