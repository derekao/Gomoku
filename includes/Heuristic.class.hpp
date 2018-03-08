#pragma once

#include <iostream>
#include <cmath>
#include "GameManager.class.hpp"
#include "Rules.class.hpp"

class Heuristic {

private:
	static int CountHorizontalAlignmentScore(int, int, std::vector<int> & , int);
	static int CountVerticalAlignmentScore(int, int, std::vector<int> & , int);
	static int CountDiagonnalRightAlignmentScore(int, int, std::vector<int> & , int);
	static int CountDiagonnalLeftAlignmentScore(int, int, std::vector<int> & , int);
	static int CountHeuristicAlignmentScore(int, int, bool, bool, bool, bool);

	// static void CountHorizontalMenaceSize(int, int, std::vector<int> & , int);
	// static void CountVerticalMenaceSize(int, int, std::vector<int> & , int);
	// static void CountDiagonnalRightMenaceSize(int, int, std::vector<int> & , int);
	// static void CountDiagonnalLeftMenaceSize(int, int, std::vector<int> & , int);

public:
	static int BoardValue(int, int, GameManager *);
	// static void MenaceSearch(int, int, std::vector<int> &, int);

};