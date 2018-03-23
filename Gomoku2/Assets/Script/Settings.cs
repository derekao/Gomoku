using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Settings : MonoBehaviour {

	private bool Black;
	private bool isOn;
	Toggle PlayerToggle;

	// Use this for initialization
	void Start () {

		PlayerToggle = GetComponent<Toggle>();

		if (gameObject.name == "BlackToggle")
			Black = true;
		else if (gameObject.name == "WhiteToggle")
			Black = false;
		else
			Debug.Log("Wrong UpdateScore Object");

		if (Black)
		{
			if (PlayerPrefs.GetInt("IABlack") != 0)
				isOn = true;
			else
				isOn = false;
		}
		else
		{
			if (PlayerPrefs.GetInt("IAWhite") != 0)
				isOn = true;
			else
				isOn = false;
		}

		if (isOn)
			PlayerToggle.isOn = true;
		else
			PlayerToggle.isOn = false;

	}
	
	public void OnClick()
	{
		if (PlayerToggle.isOn)
		{
			if (Black)
				PlayerPrefs.SetInt("IABlack", 1);
			else
				PlayerPrefs.SetInt("IAWhite", 1);
		}
		else
		{
			if (Black)
				PlayerPrefs.SetInt("IABlack", 0);
			else
				PlayerPrefs.SetInt("IAWhite", 0);
		}
	}
}
