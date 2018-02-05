using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour {

	public enum Stone {Empty, Black, White};
	public bool	bPlayerOneTurn;
	public int iWidthBoard = 19;
	public int iHeightBoard = 19;
	public Stone[,] Board;
	// Use this for initialization
	void Start () {

		Board = new Stone[iHeightBoard, iWidthBoard];
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
