
#pragma once

#include <map>
#include <string>
#include <vector>

#include "GameManager.class.hpp"

class TranspositionTable {

public:

	static std::string HashBoard(std::vector<char> & board);
	static std::map<std::string, GameManager *> TranspoTable;

	static void Store(GameManager *Node);
	static GameManager * Retrieve(GameManager *Node);
	
};