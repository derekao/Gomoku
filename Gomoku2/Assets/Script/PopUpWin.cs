using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PopUpWin : MonoBehaviour {

	public void OnExit()
	{
		gameObject.SetActive(false);
		GameManager.Instance.LockPopUp = true;
	}
}
