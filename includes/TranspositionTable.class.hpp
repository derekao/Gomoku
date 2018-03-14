#pragma once

#include <map>
#include <string>
#include <vector>

class TranspositionTable {

public:
	static std::string HashBoard(std::vector<int> & board);
	static std::map<std::string, int> TranspoTable;
	
};