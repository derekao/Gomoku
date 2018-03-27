#include "TranspositionTable.class.hpp"

std::map<std::string, GameManager *>  TranspositionTable::TranspoTable;

std::string TranspositionTable::HashBoard(std::vector<char> & board) {
	std::string hash = "";
	int cnt;
	int boardValue;
	size_t j;
	for (size_t i = 0; i <  board.size();) {
		cnt = 0;
		boardValue = board[i];
		j = i;
		for (;j < board.size() && board[j] == boardValue ; j++) {
			cnt++;
		}
		hash = hash + std::to_string(cnt) + std::to_string(boardValue);
		i = j; 
	}
	return hash;
}

void TranspositionTable::Store(GameManager *Node) {
	std::string hash = HashBoard(Node->getBoard());
	if (!TranspoTable[hash])
		TranspoTable[hash] = Node;
}

GameManager * TranspositionTable::Retrieve(GameManager *Node) {
	std::string hash = HashBoard(Node->getBoard());
	if (!TranspoTable[hash])
		return NULL;
	else
		return TranspoTable[hash];
}