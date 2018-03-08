#include "Heuristic.class.hpp"
#include <fstream>

// static void printBoard(GameManager * Board)
// {
// 	for (int i = 0; i < 361; i ++)
// 	{
// 		std::cout << Board->getBoard()[i] << " ";
// 		if (i % 19 == 18)
// 			std::cout << std::endl;
// 	}
// }

int Heuristic::BoardValue(int Player, int Opponent, GameManager * Instance) {
	int value = 0;
	int x;
	int y;

	if ((Player == STONE_BLACK && (Instance->getBlackWin() || Instance->getBlackScore() >= 10)) || (Player == STONE_WHITE && (Instance->getWhiteWin() || Instance->getWhiteScore() >= 10))) {
		return MAX_INFINIT;
	}
	else if ((Opponent == STONE_BLACK && (Instance->getBlackWin() || Instance->getBlackScore() >= 10)) || (Opponent == STONE_WHITE && (Instance->getWhiteWin() || Instance->getWhiteScore() >= 10))) {
		return MIN_INFINIT;
	}

	for (size_t i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++) {
		y = i / BOARD_HEIGHT;
		x = i % BOARD_WIDTH;

		if ((Instance->getBoard()[i] & Player) != 0) {
			// Horizontal
			if (x < BOARD_WIDTH - 1)
				value +=  CountHorizontalAlignmentScore(Player, Opponent, Instance->getBoard(), i);

			// Vertical
			if (y < BOARD_HEIGHT - 1)
				value +=  CountVerticalAlignmentScore(Player, Opponent, Instance->getBoard(), i);

			// Diagonnal Right
			if (y < BOARD_HEIGHT - 1 && x < BOARD_WIDTH - 1)
				value += CountDiagonnalRightAlignmentScore(Player, Opponent, Instance->getBoard(), i);

			// Diagonnal Left
			if (y < BOARD_HEIGHT - 1 && x > 0)
				value += CountDiagonnalLeftAlignmentScore(Player, Opponent, Instance->getBoard(), i);
		}
		else if ((Instance->getBoard()[i] & Opponent) != 0) {
			// Horizontal
			if (x < BOARD_WIDTH - 1)
				value -=  CountHorizontalAlignmentScore(Opponent, Player, Instance->getBoard(), i);
			// Vertical
			if (y < BOARD_HEIGHT - 1)
				value -=  CountVerticalAlignmentScore(Opponent, Player, Instance->getBoard(), i);

		// 	// Diagonnal Right
			if (y < BOARD_HEIGHT - 1 && x < BOARD_WIDTH - 1)
				value -= CountDiagonnalRightAlignmentScore(Opponent, Player, Instance->getBoard(), i);

		// 	// Diagonnal Left
			if (y < BOARD_HEIGHT - 1 && x > 0)
				value -= CountDiagonnalLeftAlignmentScore(Opponent, Player, Instance->getBoard(), i);
		}
	}
	return value;
}

int Heuristic::CountHorizontalAlignmentScore(int Player, int Opponent, std::vector<int> & Board, int pos) {
	int x = pos % BOARD_WIDTH;
	int y = pos / BOARD_HEIGHT;
	int size = 0;
	int potentialSize = 0;
	int iNonFullAlign = 0;
	bool bBorder = false;
	bool bBlockStart = false;
	bool bBlockEnd = false;

	if (x == 0) // Enregistre si l'alignement commence sur le bord de la map
		bBorder = true;
	if (x > 0 && (Board[y * BOARD_WIDTH + x - 1] & Player) != 0)
		return 0;
	else if (x > 0) { // Verifie que l'alignement n'a pas deja etait compté
		
		if ((Board[y * BOARD_WIDTH + x - 1] & Opponent) != 0) // Verifie que l'alignement n'est pas bloqué par l'adversaire
			bBlockStart = true;
		else { // Sinon compte la taille potentiel de l'alignement depuis le début
			for (int tmp = pos - 1; y == tmp / BOARD_HEIGHT && tmp >= 0; tmp--) {
				if (Rules::EmptyCase(Board[tmp]))
					potentialSize++;
				else
					break;
				if (potentialSize >= 5)
					break ;
			}
		}
	}

	while (y == pos / BOARD_HEIGHT && pos < BOARD_HEIGHT * BOARD_WIDTH && !bBlockEnd) { // Calcule la taille de l'alignement
		if ((Board[pos] & Player) != 0) { // Calcul la taille
			size++;
			if (pos % BOARD_WIDTH == BOARD_WIDTH - 1) // Enregistre si on arrive sur un bord
				bBorder = true;
		}
		else if ((Board[pos] & Opponent) != 0 && (iNonFullAlign == 0 || iNonFullAlign < size)) // Verifie que l'alignement n'est pas bloqué par l'adversaire
			bBlockEnd = true;
		else if (iNonFullAlign == 0) // Permet de compter un alignement avec un seul trou
			iNonFullAlign = size;
		else
			break ;
		pos++;
	}
	if ((iNonFullAlign != 0 && iNonFullAlign < size) || iNonFullAlign == size)
		potentialSize++;
	if (!bBlockEnd) { // Sinon compte la taille potentiel de l'alignement depuis la fin
		for (; y == pos / BOARD_HEIGHT && pos < BOARD_HEIGHT * BOARD_WIDTH; pos++) {
			if (Rules::EmptyCase(Board[pos]))
				potentialSize++;
			else
				break;
			if (potentialSize >= 5)
				break ;
		}
	}
	potentialSize += size;

	return CountHeuristicAlignmentScore(size, potentialSize, bBorder, bBlockStart, bBlockEnd, (iNonFullAlign < size));
}

int Heuristic::CountVerticalAlignmentScore(int Player, int Opponent, std::vector<int> & Board, int pos) {
	int x = pos % BOARD_WIDTH;
	int y = pos / BOARD_HEIGHT;
	int size = 0;
	int potentialSize = 0;
	int iNonFullAlign = 0;
	bool bBorder = false;
	bool bBlockStart = false;
	bool bBlockEnd = false;


	if (y == 0)
		bBorder = true;
	if (y > 0 && (Board[(y - 1) * BOARD_WIDTH + x] & Player) != 0)
		return 0;
	else if (y > 0) {
		
		if ((Board[(y - 1) * BOARD_WIDTH + x] & Opponent) != 0)
			bBlockStart = true;
		else {
			for (int tmp = pos - BOARD_WIDTH; tmp >= 0; tmp -= BOARD_WIDTH) {
				if (Rules::EmptyCase(Board[tmp]))
					potentialSize++;
				else
					break ;
				if (potentialSize >= 5)
					break ;
			}
		}
	}

	while (pos < BOARD_HEIGHT * BOARD_WIDTH && !bBlockEnd) {
		if ((Board[pos] & Player) != 0) {
			size++;
			if ((pos / BOARD_HEIGHT) == BOARD_HEIGHT - 1)
				bBorder = true;
		}
		else if ((Board[pos] & Opponent) != 0 && (iNonFullAlign == 0 || iNonFullAlign < size))
			bBlockEnd = true;
		else if (iNonFullAlign == 0)
			iNonFullAlign = size;
		else
			break;
		pos += BOARD_WIDTH;
	}
	if ((iNonFullAlign != 0 && iNonFullAlign < size) || iNonFullAlign == size)
		potentialSize++;
	if (!bBlockEnd) {
		for (; pos < BOARD_HEIGHT * BOARD_WIDTH; pos += BOARD_WIDTH) {
			if (Rules::EmptyCase(Board[pos]))
				potentialSize++;
			else
				break ;
			if (potentialSize >= 5)
				break ;
		}
	}
	potentialSize += size;

	return CountHeuristicAlignmentScore(size, potentialSize, bBorder, bBlockStart, bBlockEnd, (iNonFullAlign < size));
}

int Heuristic::CountDiagonnalRightAlignmentScore(int Player, int Opponent, std::vector<int> & Board, int pos) {
	int x = pos % BOARD_WIDTH;
	int y = pos / BOARD_HEIGHT;
	int size = 0;
	int potentialSize = 0;
	int iNonFullAlign = 0;
	bool bBorder = false;
	bool bBlockStart = false;
	bool bBlockEnd = false;

	if (y == 0 || x == 0)
		bBorder = true;
	if (y > 0 && x > 0 && (Board[(y - 1) * BOARD_WIDTH + x - 1] & Player) != 0)
		return 0;
	else if (y > 0 && x > 0) {
		
		if ((Board[(y - 1) * BOARD_WIDTH + x - 1] & Opponent) != 0)
			bBlockStart = true;
		else {
			while (x - 1 >= 0 && y - 1 >= 0) {
				if (Rules::EmptyCase(Board[(y - 1) * BOARD_WIDTH + x - 1]))
					potentialSize++;
				else
					break ;
				if (potentialSize >= 5)
					break ;
				x--;
				y--;
			}
			x = pos % BOARD_WIDTH;
			y = pos / BOARD_HEIGHT;
		}
	}
	while (x < BOARD_WIDTH && y < BOARD_HEIGHT && !bBlockEnd) {
		if ((Board[y * BOARD_WIDTH + x] & Player) != 0) {
			size++;
			if (x == BOARD_WIDTH - 1 || y == BOARD_HEIGHT - 1)
				bBorder = true;
		}
		else if ((Board[y * BOARD_WIDTH + x] & Opponent) != 0 && (iNonFullAlign == 0 || iNonFullAlign < size))
			bBlockEnd = true;
		else if (iNonFullAlign == 0)
			iNonFullAlign = size;
		else
			break;
		x++;
		y++;
	}
	if ((iNonFullAlign != 0 && iNonFullAlign < size) || iNonFullAlign == size)
		potentialSize++;
	if (!bBlockEnd) {
		while (x < BOARD_WIDTH && y < BOARD_HEIGHT) {
			if (Rules::EmptyCase(Board[y * BOARD_WIDTH + x]))
				potentialSize++;
			else
				break ;
			if (potentialSize >= 5)
				break ;
			x++;
			y++;
		}
	}
	potentialSize += size;

	return CountHeuristicAlignmentScore(size, potentialSize, bBorder, bBlockStart, bBlockEnd, (iNonFullAlign < size));
}

int Heuristic::CountDiagonnalLeftAlignmentScore(int Player, int Opponent, std::vector<int> & Board, int pos) {
	int x = pos % BOARD_WIDTH;
	int y = pos / BOARD_HEIGHT;
	int size = 0;
	int potentialSize = 0;
	int iNonFullAlign = 0;
	bool bBorder = false;
	bool bBlockStart = false;
	bool bBlockEnd = false;

	if (y == 0 || x == BOARD_WIDTH - 1)
		bBorder = true;
	if (y > 0 && x < BOARD_WIDTH - 1 && (Board[(y - 1) * BOARD_HEIGHT + x + 1] & Player) != 0)
		return 0;
	else if (y > 0 && x < BOARD_WIDTH - 1) {
		
		if ((Board[(y - 1) * BOARD_HEIGHT + x + 1] & Opponent) != 0)
			bBlockStart = true;
		else {
			while (x + 1 <= BOARD_WIDTH && y - 1 >= 0) {
				if (Rules::EmptyCase(Board[(y - 1) * BOARD_WIDTH + x + 1]))
					potentialSize++;
				else
					break ;
				if (potentialSize >= 5)
					break ;
				x++;
				y--;
			}
			x = pos % BOARD_WIDTH;
			y = pos / BOARD_HEIGHT;
		}
	}
	while (x >= 0 && y < BOARD_HEIGHT && !bBlockEnd) {
		if ((Board[y * BOARD_WIDTH + x] & Player) != 0) {
			size++;
			if (x == 0 || y == BOARD_HEIGHT - 1)
				bBorder = true;
		}
		else if ((Board[y * BOARD_WIDTH + x] & Opponent) != 0 && (iNonFullAlign == 0 || iNonFullAlign < size))
			bBlockEnd = true;
		else if (iNonFullAlign == 0)
			iNonFullAlign = size;
		else
			break;
		x--;
		y++;
	}
	if ((iNonFullAlign != 0 && iNonFullAlign < size) || iNonFullAlign == size)
		potentialSize++;
	if (!bBlockEnd) {
		while (x >= 0 && y < BOARD_HEIGHT) {
			if (Rules::EmptyCase(Board[y * BOARD_WIDTH + x]))
				potentialSize++;
			else
				break ;
			if (potentialSize >= 5)
				break ;
			x--;
			y++;
		}
	}
	potentialSize += size;

	return CountHeuristicAlignmentScore(size, potentialSize, bBorder, bBlockStart, bBlockEnd, (iNonFullAlign < size));
}

int Heuristic::CountHeuristicAlignmentScore(int size, int potentialSize, bool bBorder, bool bBlockStart, bool bBlockEnd, bool bUnbound) {
	int score = 0;

	score = pow(10, size); // Tmp
	
	if (size < 5 && potentialSize < 5) { // Alignement inferieur à 5 et potentiellement inferieur à 5
		if (!bBorder && ((size == 2 && bBlockStart && !bBlockEnd) || (size == 2 && !bBlockStart && bBlockEnd))) // Peut etre mangé
			score += 0;
		else
			score += 0;
	}
	else if (bBorder || bUnbound) {
		score += 0;
	}
	// else if ((bBlockStart && !bBlockEnd) || (!bBlockStart && bBlockEnd)) {

	// }
	// else if () {
		
	// }
	// else if () {
		
	// }
	return score;
}


// void Heuristic::MenaceSearch(int Player, int Opponent, std::vector<int> & Board, int pos) {

// 	CountHorizontalMenaceSize(Player, Opponent, Board, pos);
// 	CountVerticalMenaceSize(Player, Opponent, Board, pos);
// 	CountDiagonnalRightMenaceSize(Player, Opponent, Board, pos);
// 	CountDiagonnalLeftMenaceSize(Player, Opponent, Board, pos);

// }

// void Heuristic::CountHorizontalMenaceSize(int Player, int Opponent, std::vector<int> & Board, int pos) {
// 	int x = pos % BOARD_WIDTH;
// 	int y = pos / BOARD_HEIGHT;
// 	bool bUnboundAlign = false;

// 	for (int tmp = pos; y == tmp / BOARD_HEIGHT; tmp--) {
// 		if (Rules::EmptyCase(Board[tmp]) && !bUnboundAlign) {
// 			bUnboundAlign = true;
// 		}
// 	}
// }

// void Heuristic::CountVerticalMenaceSize(int Player, int Opponent, std::vector<int> & Board, int pos) {
// 	int x = pos % BOARD_WIDTH;
// 	int y = pos / BOARD_HEIGHT;
// 	bool bUnboundAlign = false;

// 	for (int tmp = pos; y == tmp / BOARD_HEIGHT; tmp--) {
// 		if (Rules::EmptyCase(Board[tmp]) && !bUnboundAlign) {
// 			bUnboundAlign = true;
// 		}
// 	}
// }

// void Heuristic::CountDiagonnalRightMenaceSize(int Player, int Opponent, std::vector<int> & Board, int pos) {
// 	int x = pos % BOARD_WIDTH;
// 	int y = pos / BOARD_HEIGHT;
// 	bool bUnboundAlign = false;

// 	for (int tmp = pos; y == tmp / BOARD_HEIGHT; tmp--) {
// 		if (Rules::EmptyCase(Board[tmp]) && !bUnboundAlign) {
// 			bUnboundAlign = true;
// 		}
// 	}
// }

// void Heuristic::CountDiagonnalLeftMenaceSize(int Player, int Opponent, std::vector<int> & Board, int pos) {
// 	int x = pos % BOARD_WIDTH;
// 	int y = pos / BOARD_HEIGHT;
// 	bool bUnboundAlign = false;

// 	for (int tmp = pos; y == tmp / BOARD_HEIGHT; tmp--) {
// 		if (Rules::EmptyCase(Board[tmp]) && !bUnboundAlign) {
// 			bUnboundAlign = true;
// 		}
// 	}
// }

