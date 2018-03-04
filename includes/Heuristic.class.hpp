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
	static int CountHeuristicAlignmentScore(int, int, bool, bool, bool);

public:
	static int BoardValue(int, int, GameManager *);

};