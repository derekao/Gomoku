#include "TranspositionTable.class.hpp"

std::map<std::string, int>  TranspositionTable::TranspoTable;

std::string TranspositionTable::HashBoard(std::vector<int> & board) {
	std::string hash = "";
	int cnt;
	int boardValue;
	size_t j;
	for (size_t i = 0; i <  board.size();) {
		cnt = 0;
		boardValue = board[i];
		j = i;
		for (;board[j] == boardValue && j < board.size(); j++) {
			cnt++;
		}
		hash = hash + std::to_string(cnt) + std::to_string(boardValue);
		i = j; 
	}
	return hash;
}