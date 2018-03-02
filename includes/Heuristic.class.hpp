#pragma once

#include <iostream>
#include <cmath>
#include "GameManager.class.hpp"

class Heuristic {

private:
	static int CountHorizontalAlignmentSize(int, std::vector<int>, int);
	static int CountVerticalAlignmentSize(int, std::vector<int>, int);
	static int CountDiagonnalRightAlignmentSize(int, std::vector<int>, int);
	static int CountDiagonnalLeftAlignmentSize(int, std::vector<int>, int);

public:
	static int BoardValueByAlignment(int, int, GameManager *);

};