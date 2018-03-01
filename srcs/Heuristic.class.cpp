#include "Heuristic.class.hpp"
#include <fstream>

int Heuristic::BoardValueByAlignment(int Player, int Opponent, GameManager * Instance) {
	int value = 0;
	int x;
	int y;

	std::ofstream file("debugVk.txt", std::ios::out | std::ios::trunc);


	for (size_t i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++) {
		y = i / BOARD_HEIGHT;
		x = i % BOARD_WIDTH;
		// file << "y " << y << " x " << x << std::endl;

		if ((Instance->getBoard()[i] & Player) != 0) {
			// Horizontal
			if (x < BOARD_WIDTH - 1) {
				if (x == 0)
					value = CountHorizontalAlignmentSize(Player, Instance->getBoard(), i);
				else if ((Instance->getBoard()[y * BOARD_HEIGHT + x - 1] & Player) == 0) {

					if ((Instance->getBoard()[y * BOARD_HEIGHT + x - 1] & Opponent) != 0)
						value = CountHorizontalAlignmentSize(Player, Instance->getBoard(), i);
					else
						value = CountHorizontalAlignmentSize(Player, Instance->getBoard(), i);

				}

				// file << "Horizontal" << std::endl;
			}

			// Vertical
			if (y < BOARD_HEIGHT - 1) {
				if (y == 0)
					value = CountVerticalAlignmentSize(Player, Instance->getBoard(), i);
				else if ((Instance->getBoard()[(y - 1) * BOARD_HEIGHT + x] & Player) == 0) {

					if ((Instance->getBoard()[(y - 1) * BOARD_HEIGHT + x] & Opponent) != 0)
						value = CountVerticalAlignmentSize(Player, Instance->getBoard(), i);
					else
						value = CountVerticalAlignmentSize(Player, Instance->getBoard(), i);

				}
				// file << "Vertical" << std::endl;
			}

			// Diagonnal Right
			if (y < BOARD_HEIGHT - 1 && x < BOARD_WIDTH - 1) {
				if (y == 0 || x == 0)
					value = CountDiagonnalRightAlignmentSize(Player, Instance->getBoard(), i);
				else if ((Instance->getBoard()[(y - 1) * BOARD_HEIGHT + x - 1] & Player) == 0) {

					if ((Instance->getBoard()[(y - 1) * BOARD_HEIGHT + x - 1] & Opponent) != 0)
						value = CountDiagonnalRightAlignmentSize(Player, Instance->getBoard(), i);
					else
						value = CountDiagonnalRightAlignmentSize(Player, Instance->getBoard(), i);

				}
				// file << "Diagonnal Right" << std::endl;
			}

			// Diagonnal Left
			if (y < BOARD_HEIGHT - 1 && x > 0) {
				if (y == 0 || x == BOARD_WIDTH - 1)
					value = CountDiagonnalLeftAlignmentSize(Player, Instance->getBoard(), i);
				else if ((Instance->getBoard()[(y - 1) * BOARD_HEIGHT + x + 1] & Player) == 0) {

					if ((Instance->getBoard()[(y - 1) * BOARD_HEIGHT + x + 1] & Opponent) != 0)
						value = CountDiagonnalLeftAlignmentSize(Player, Instance->getBoard(), i);
					else
						value = CountDiagonnalLeftAlignmentSize(Player, Instance->getBoard(), i);
				
				}
				// file << "Diagonnal Left" << std::endl;
			}
		}
	}
	file << value;
	return value;
}

int Heuristic::CountHorizontalAlignmentSize(int Player, std::vector<int> Board, int pos) {
	int y = pos / BOARD_HEIGHT;
	int size = 0;

	while (y == pos / BOARD_HEIGHT && pos < BOARD_HEIGHT * BOARD_WIDTH) {
		if ((Board[pos] & Player) != 0)
			size++;
		pos++;
	}
	return size > 1 ? size : 0;	
}

int Heuristic::CountVerticalAlignmentSize(int Player, std::vector<int> Board, int pos) {
	int size = 0;

	while (pos < BOARD_HEIGHT * BOARD_WIDTH) {
		if ((Board[pos] & Player) != 0)
			size++;
		pos += BOARD_WIDTH;
	}
	return size > 1 ? size : 0;
}

int Heuristic::CountDiagonnalRightAlignmentSize(int Player, std::vector<int> Board, int pos) {
	int x = pos % BOARD_WIDTH;
	int y = pos / BOARD_HEIGHT;
	int size = 0;

	while (x < BOARD_WIDTH && y < BOARD_HEIGHT) {
		if ((Board[pos] & Player) != 0)
			size++;
		pos = y * BOARD_HEIGHT + x + 1;
		x = pos % BOARD_WIDTH;
		y = pos / BOARD_HEIGHT;
	}
	return size > 1 ? size : 0;
}

int Heuristic::CountDiagonnalLeftAlignmentSize(int Player, std::vector<int> Board, int pos) {
	int x = pos % BOARD_WIDTH;
	int y = pos / BOARD_HEIGHT;
	int size = 0;

	while (x > 0 && y < BOARD_HEIGHT) {
		if ((Board[pos] & Player) != 0)
			size++;
		pos = y * BOARD_HEIGHT + x - 1;
		x = pos % BOARD_WIDTH;
		y = pos / BOARD_HEIGHT;
	}
	return size > 1 ? size : 0;
}
