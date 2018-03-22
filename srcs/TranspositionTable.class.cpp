#include "TranspositionTable.class.hpp"

// static void printBoard(GameManager * Board)
// {
// 	for (int i = 0; i < 361; i ++)
// 	{
// 		if (Board->getBoard()[i]  > 2)
// 			std::cout << "0 ";
// 		else
// 			std::cout << (int)Board->getBoard()[i] << " ";
// 		if (i % 19 == 18)
// 			std::cout << std::endl;
// 	}
// }

std::map<std::string, BoardMemory>  TranspositionTable::TranspoTable;

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

void TranspositionTable::Store(BoardMemory & Node) {
	std::string hash = HashBoard(Node.Board->getBoard());
	if (!TranspoTable[hash])
		TranspoTable[hash] = Node;
	else 
	 	std::cout << "wierd stuff" << std::endl;
	// std::cout << TranspoTable.size() << std::endl;
}

BoardMemory & TranspositionTable::Retrieve(GameManager *Node) {
	std::string hash = HashBoard(Node->getBoard());
//	std::cout << hash << std::endl;
//	printBoard(Node);
	if (!TranspoTable[hash])
		return NULL;
	else
	{
		BoardMemory tmp = TranspoTable[hash];
		TranspoTable.erase(hash);
		return tmp;
	}
}