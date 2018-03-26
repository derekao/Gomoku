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
			Instance.value = PlayerPrefs.GetInt("Depth");
		}
		else if (SliderType == 1)
		{
			Instance.value = PlayerPrefs.GetFloat("Timer");
		}
		else if (SliderType == 2)
		{
			Instance.value = PlayerPrefs.GetInt("Move");
		}
		else if (SliderType == 3)
		{
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
