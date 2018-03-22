#pragma once

#include <map>
#include <string>
#include <vector>

#include "GameManager.class.hpp"

class BoardMemory
{
public:
	BoardMemory() : UpperBound(MAX_INFINIT), LowerBound(MIN_INFINIT) {}

	GameManager * Board;
	int UpperBound;
	int LowerBound;
};

class TranspositionTable {

public:

	static std::string HashBoard(std::vector<char> & board);
	static std::map<std::string, BoardMemory> TranspoTable;

	static void Store(BoardMemory & Node);
	static BoardMemory & Retrieve(GameManager * Node);
	
};