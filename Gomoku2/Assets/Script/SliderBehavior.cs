using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SliderBehavior : MonoBehaviour {

	public int SliderType;
	Slider Instance;

	// Use this for initialization
	void Start () {
		Instance = GetComponent<Slider>();

		if (SliderType == 0)
		{
			int n = PlayerPrefs.GetInt("Depth");
			if (n < 2 || n > 30)
				PlayerPrefs.SetInt("Depth", 2);
			Instance.value = PlayerPrefs.GetInt("Depth");
		}
		else if (SliderType == 1)
		{
			float f = PlayerPrefs.GetFloat("Timer");
			if (f < 0.5f || f > 10.0f)
				PlayerPrefs.SetFloat("Timer", 0.5f);
			Instance.value = PlayerPrefs.GetFloat("Timer");
		}
		else if (SliderType == 2)
		{
			int n = PlayerPrefs.GetInt("Move");
			if (n < 3 || n > 100)
				PlayerPrefs.SetInt("Move", 3);
			Instance.value = PlayerPrefs.GetInt("Move");
		}
		else if (SliderType == 3)
		{
			int n = PlayerPrefs.GetInt("Algo");
			if (n < 0 || n > 7)
				PlayerPrefs.SetInt("Algo", 0);
			Instance.value = PlayerPrefs.GetInt("Algo");
		}
	}
	
	// Update is called once per frame
	public void OnUpdateSlider(float Value)
	{
		if (SliderType == 0)
		{
			PlayerPrefs.SetInt("Depth", Mathf.RoundToInt(Value));
		}
		else if (SliderType == 1)
		{
			PlayerPrefs.SetFloat("Timer", Value);
		}
		else if (SliderType == 2)
		{
			PlayerPrefs.SetInt("Move", Mathf.RoundToInt(Value));
		}
		else if (SliderType == 3)
		{
			PlayerPrefs.SetInt("Algo", Mathf.RoundToInt(Value));
		}
	}
}
