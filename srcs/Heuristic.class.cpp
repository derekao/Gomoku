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

//	printBoard(Instance);
	for (size_t i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++) {
		y = i / BOARD_HEIGHT;
		x = i % BOARD_WIDTH;
	//	std::cout << "x = " << x << " et y = " << y << " et case =  " << Instance->getBoard()[i] << " et i = " << i << std::endl;

		if ((Instance->getBoard()[i] & Player) != 0) {
			// Horizontal
			if (x < BOARD_WIDTH - 1)
				value +=  CountHorizontalAlignmentScore(Player, Opponent, Instance->getBoard(), i);
//			std::cout << "Value1 = " << value << std::endl;
			// Vertical
			if (y < BOARD_HEIGHT - 1)
				value +=  CountVerticalAlignmentScore(Player, Opponent, Instance->getBoard(), i);
//			std::cout << "Value2 = " << value << std::endl;

			// Diagonnal Right
			if (y < BOARD_HEIGHT - 1 && x < BOARD_WIDTH - 1)
				value += CountDiagonnalRightAlignmentScore(Player, Opponent, Instance->getBoard(), i);
//			std::cout << "Value3 = " << value << std::endl;

			// Diagonnal Left
			if (y < BOARD_HEIGHT - 1 && x > 0)
				value += CountDiagonnalLeftAlignmentScore(Player, Opponent, Instance->getBoard(), i);
//			std::cout << "Value4 = " << value << std::endl;
		}
		else if ((Instance->getBoard()[i] & Opponent) != 0) {
			// Horizontal
			if (x < BOARD_WIDTH - 1)
				value -=  CountHorizontalAlignmentScore(Opponent, Player, Instance->getBoard(), i);
//			std::cout << "Value1 = " << value << std::endl;
			// Vertical
			if (y < BOARD_HEIGHT - 1)
				value -=  CountVerticalAlignmentScore(Opponent, Player, Instance->getBoard(), i);
//			std::cout << "Value2 = " << value << std::endl;

			// Diagonnal Right
			if (y < BOARD_HEIGHT - 1 && x < BOARD_WIDTH - 1)
				value -= CountDiagonnalRightAlignmentScore(Opponent, Player, Instance->getBoard(), i);
//			std::cout << "Value3 = " << value << std::endl;

			// Diagonnal Left
			if (y < BOARD_HEIGHT - 1 && x > 0)
				value -= CountDiagonnalLeftAlignmentScore(Opponent, Player, Instance->getBoard(), i);
//			std::cout << "Value4 = " << value << std::endl;
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
	else if ((Board[y * BOARD_WIDTH + x - 1] & Player) == 0) { // Verifie que l'alignement n'a pas deja etait compté
		
		if ((Board[y * BOARD_WIDTH + x - 1] & Opponent) != 0) // Verifie que l'alignement n'est pas bloqué par l'adversaire
			bBlockStart = true;
		else { // Sinon compte la taille potentiel de l'alignement depuis le début
			for (int tmp = pos - 1; y == tmp / BOARD_HEIGHT && tmp > 0; tmp--) {
				if (Rules::EmptyCase(Board[tmp]))
					potentialSize++;
				if (potentialSize >= 5)
					break ;
			}
		}

		while (y == pos / BOARD_HEIGHT && pos < BOARD_HEIGHT * BOARD_WIDTH && !bBlockEnd) { // Calcule la taille de l'alignement
			if ((Board[pos] & Player) != 0) { // Calcul la taille
				size++;
				if (pos % BOARD_WIDTH == BOARD_WIDTH - 1) // Enregistre si on arrive sur un bord
					bBorder = true;
			}
			else if ((Board[pos] & Opponent) != 0 && iNonFullAlign < size) // Verifie que l'alignement n'est pas bloqué par l'adversaire
				bBlockEnd = true;
			else if (iNonFullAlign == 0) // Permet de compter un alignement avec un seul trou
				iNonFullAlign = size;
			else
				break ;
			pos++;
		}

		if (!bBlockEnd) { // Sinon compte la taille potentiel de l'alignement depuis la fin
			for (; y == pos / BOARD_HEIGHT && pos < BOARD_HEIGHT * BOARD_WIDTH; pos++) {
				if (Rules::EmptyCase(Board[pos]))
					potentialSize++;
				if (potentialSize >= 5)
					break ;
			}
		}
		potentialSize += size;
	}
	return CountHeuristicAlignmentScore(size, potentialSize, bBorder, bBlockStart, bBlockEnd);
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
	else if ((Board[(y - 1) * BOARD_WIDTH + x] & Player) == 0) {
		
		if ((Board[(y - 1) * BOARD_WIDTH + x] & Opponent) != 0)
			bBlockStart = true;
		else {
			for (int tmp = pos - BOARD_WIDTH; tmp > 0; tmp -= BOARD_WIDTH) {
				if (Rules::EmptyCase(Board[tmp]))
					potentialSize++;
				if (potentialSize >= 5)
					break ;
			}
		}

		while (pos < BOARD_HEIGHT * BOARD_WIDTH && !bBlockEnd) {
			if ((Board[pos] & Player) != 0) {
				size++;
				if ((pos / BOARD_HEIGHT) == BOARD_HEIGHT - 1)
					bBorder = true;
			}
			else if ((Board[pos] & Opponent) != 0 && iNonFullAlign < size)
				bBlockEnd = true;
			else if (iNonFullAlign == 0)
				iNonFullAlign = size;
			else
				break;
			pos += BOARD_WIDTH;
		}

		if (!bBlockEnd) {
			for (; pos < BOARD_HEIGHT * BOARD_WIDTH; pos += BOARD_WIDTH) {
				if (Rules::EmptyCase(Board[pos]))
					potentialSize++;
				if (potentialSize >= 5)
					break ;
			}
		}
		potentialSize += size;
	}
	return CountHeuristicAlignmentScore(size, potentialSize, bBorder, bBlockStart, bBlockEnd);
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
	else if ((Board[(y - 1) * BOARD_WIDTH + x - 1] & Player) == 0) {
		
		if ((Board[(y - 1) * BOARD_WIDTH + x - 1] & Opponent) != 0)
			bBlockStart = true;
		else {
			for (int tmp = (y - 1) * BOARD_WIDTH + x - 1; x > 0 && y > 0;) {
				if (Rules::EmptyCase(Board[tmp]))
					potentialSize++;
				if (potentialSize >= 5)
					break ;
				tmp = (y - 1) * BOARD_WIDTH + x - 1;
				x = tmp % BOARD_WIDTH;
				y = tmp / BOARD_HEIGHT;
			}
			x = pos % BOARD_WIDTH;
			y = pos / BOARD_HEIGHT;
		}

		while (x < BOARD_WIDTH && y < BOARD_HEIGHT && !bBlockEnd) {
			if ((Board[pos] & Player) != 0) {
				size++;
				if (x == BOARD_WIDTH - 1 || y == BOARD_HEIGHT - 1)
					bBorder = true;
			}
			else if ((Board[pos] & Opponent) != 0 && iNonFullAlign < size)
				bBlockEnd = true;
			else if (iNonFullAlign == 0)
				iNonFullAlign = size;
			else
				break;
			pos = (y + 1) * BOARD_WIDTH + x + 1;
			x = pos % BOARD_WIDTH;
			y = pos / BOARD_HEIGHT;
		}

		if (!bBlockEnd) {
			while (x < BOARD_WIDTH && y < BOARD_HEIGHT) {
				if (Rules::EmptyCase(Board[pos]))
					potentialSize++;
				if (potentialSize >= 5)
					break ;
				pos = (y + 1) * BOARD_WIDTH + x + 1;
				x = pos % BOARD_WIDTH;
				y = pos / BOARD_HEIGHT;
			}
		}
		potentialSize += size;
	}
	return CountHeuristicAlignmentScore(size, potentialSize, bBorder, bBlockStart, bBlockEnd);
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
	else if ((Board[(y - 1) * BOARD_HEIGHT + x + 1] & Player) == 0) {
		
		if ((Board[(y - 1) * BOARD_HEIGHT + x + 1] & Opponent) != 0)
			bBlockStart = true;
		else {
			for (int tmp = (y - 1) * BOARD_WIDTH + x + 1; x < BOARD_WIDTH && y > 0;) {
				if (Rules::EmptyCase(Board[tmp]))
					potentialSize++;
				if (potentialSize >= 5)
					break ;
				tmp = (y - 1) * BOARD_WIDTH + x + 1;
				x = tmp % BOARD_WIDTH;
				y = tmp / BOARD_HEIGHT;
			}
			x = pos % BOARD_WIDTH;
			y = pos / BOARD_HEIGHT;
		}

		while (x > 0 && y < BOARD_HEIGHT && !bBlockEnd) {
			if ((Board[pos] & Player) != 0) {
				size++;
				if (x == 0 || y == BOARD_HEIGHT - 1)
					bBorder = true;
			}
			else if ((Board[pos] & Opponent) != 0 && iNonFullAlign < size)
				bBlockEnd = true;
			else if (iNonFullAlign == 0)
				iNonFullAlign = size;
			else
				break;
			pos = (y + 1) * BOARD_HEIGHT + x - 1;
			x = pos % BOARD_WIDTH;
			y = pos / BOARD_HEIGHT;
		}

		if (!bBlockEnd) {
			while (x > 0 && y < BOARD_HEIGHT) {
				if (Rules::EmptyCase(Board[pos]))
					potentialSize++;
				if (potentialSize >= 5)
					break ;
				pos = (y + 1) * BOARD_WIDTH + x - 1;
				x = pos % BOARD_WIDTH;
				y = pos / BOARD_HEIGHT;
			}
		}
		potentialSize += size;
	}
	return CountHeuristicAlignmentScore(size, potentialSize, bBorder, bBlockStart, bBlockEnd);
}

int Heuristic::CountHeuristicAlignmentScore(int size, int potentialSize, bool bBorder, bool bBlockStart, bool bBlockEnd) {
	int score = 0;

	score = pow(10, size); // Temporaire
	
	if (size < 5 && potentialSize < 5) { // Alignement inferieur à 5 et potentiellement inferieur à 5
		if ((size == 2 && bBlockStart && !bBlockEnd) || (size == 2 && !bBlockStart && bBlockEnd)) // Peut etre mangé
			score += 0;
		else
			score += 0;
	}
	if (bBorder)
		score += 0;
	return score;
}


















// int Heuristic::BoardValueByAlignment(int Player, int Opponent, GameManager * Instance) {
// 	int value = 0;
// 	int x;
// 	int y;

// 	std::ofstream file("debugVk.txt", std::ios::out | std::ios::trunc);


// //	printBoard(Instance);
// //		std::cout << "------------------------------" << Player << std::endl;
// 	for (size_t i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++) {
// 		y = i / BOARD_HEIGHT;
// 		x = i % BOARD_WIDTH;
// 	//	std::cout << "x = " << x << " et y = " << y << " et case =  " << Instance->getBoard()[i] << " et i = " << i << std::endl;
// 		// file << "y " << y << " x " << x << std::endl;

// 		if ((Instance->getBoard()[i] & Player) != 0) {
// 			// Horizontal
// 			if (x < BOARD_WIDTH - 1) {
// 				if (x == 0)
// 					value +=  pow(10, CountHorizontalAlignmentSize(Player, Instance->getBoard(), i));
// 				else if ((Instance->getBoard()[y * BOARD_HEIGHT + x - 1] & Player) == 0) {

// 					if ((Instance->getBoard()[y * BOARD_HEIGHT + x - 1] & Opponent) != 0)
// 						value +=  pow(10, CountHorizontalAlignmentSize(Player, Instance->getBoard(), i));
// 					else
// 						value +=  pow(10, CountHorizontalAlignmentSize(Player, Instance->getBoard(), i));

// 				}

// 				// file << "Horizontal" << std::endl;
// 			}
// //			std::cout << "Value1 = " << value << std::endl;

// 			// Vertical
// 			if (y < BOARD_HEIGHT - 1) {
// 				if (y == 0)
// 					value +=  pow(10, CountVerticalAlignmentSize(Player, Instance->getBoard(), i));
// 				else if ((Instance->getBoard()[(y - 1) * BOARD_HEIGHT + x] & Player) == 0) {

// 					if ((Instance->getBoard()[(y - 1) * BOARD_HEIGHT + x] & Opponent) != 0)
// 						value +=  pow(10, CountVerticalAlignmentSize(Player, Instance->getBoard(), i));
// 					else
// 						value +=  pow(10, CountVerticalAlignmentSize(Player, Instance->getBoard(), i));

// 				}
// 				// file << "Vertical" << std::endl;
// 			}
// //			std::cout << "Value2 = " << value << std::endl;

// 			// Diagonnal Right
// 			if (y < BOARD_HEIGHT - 1 && x < BOARD_WIDTH - 1) {
// 				if (y == 0 || x == 0)
// 					value +=  pow(10, CountDiagonnalRightAlignmentSize(Player, Instance->getBoard(), i));
// 				else if ((Instance->getBoard()[(y - 1) * BOARD_HEIGHT + x - 1] & Player) == 0) {

// 					if ((Instance->getBoard()[(y - 1) * BOARD_HEIGHT + x - 1] & Opponent) != 0)
// 						value +=  pow(10, CountDiagonnalRightAlignmentSize(Player, Instance->getBoard(), i));
// 					else
// 						value +=  pow(10, CountDiagonnalRightAlignmentSize(Player, Instance->getBoard(), i));

// 				}
// 				// file << "Diagonnal Right" << std::endl;
// 			}
// //			std::cout << "Value3 = " << value << std::endl;

// 			// Diagonnal Left
// 			if (y < BOARD_HEIGHT - 1 && x > 0) {
// 				if (y == 0 || x == BOARD_WIDTH - 1)
// 					value +=  pow(10, CountDiagonnalLeftAlignmentSize(Player, Instance->getBoard(), i));
// 				else if ((Instance->getBoard()[(y - 1) * BOARD_HEIGHT + x + 1] & Player) == 0) {

// 					if ((Instance->getBoard()[(y - 1) * BOARD_HEIGHT + x + 1] & Opponent) != 0)
// 						value +=  pow(10, CountDiagonnalLeftAlignmentSize(Player, Instance->getBoard(), i));
// 					else
// 						value +=  pow(10, CountDiagonnalLeftAlignmentSize(Player, Instance->getBoard(), i));
				
// 				}
// 				// file << "Diagonnal Left" << std::endl;
// 			}
// //			std::cout << "Value4 = " << value << std::endl;
// 		}
// 	}
// 	file << value;
// 	return value;
// }

// int Heuristic::CountHorizontalAlignmentSize(int Player, std::vector<int> & Board, int pos) {
// 	int y = pos / BOARD_HEIGHT;
// 	int size = 0;

// 	while (y == pos / BOARD_HEIGHT && pos < BOARD_HEIGHT * BOARD_WIDTH) {
// 		if ((Board[pos] & Player) != 0)
// 			size++;
// 		else
// 			break;
// 		pos++;
// 	}
// 	return size > 1 ? size : 0;	
// }

// int Heuristic::CountVerticalAlignmentSize(int Player, std::vector<int> & Board, int pos) {
// 	int size = 0;

// 	while (pos < BOARD_HEIGHT * BOARD_WIDTH) {
// 		if ((Board[pos] & Player) != 0)
// 			size++;
// 		else
// 			break;
// 		pos += BOARD_WIDTH;
// 	}
// 	return size > 1 ? size : 0;
// }

// int Heuristic::CountDiagonnalRightAlignmentSize(int Player, std::vector<int> & Board, int pos) {
// 	int x = pos % BOARD_WIDTH;
// 	int y = pos / BOARD_HEIGHT;
// 	int size = 0;

// 	while (x < BOARD_WIDTH && y < BOARD_HEIGHT) {
// 		if ((Board[pos] & Player) != 0)
// 			size++;
// 		else
// 			break;
// 		pos = (y + 1) * BOARD_HEIGHT + x + 1;
// 		x = pos % BOARD_WIDTH;
// 		y = pos / BOARD_HEIGHT;
// 	}
// 	return size > 1 ? size : 0;
// }

// int Heuristic::CountDiagonnalLeftAlignmentSize(int Player, std::vector<int> & Board, int pos) {
// 	int x = pos % BOARD_WIDTH;
// 	int y = pos / BOARD_HEIGHT;
// 	int size = 0;

// 	while (x > 0 && y < BOARD_HEIGHT) {
// 		if ((Board[pos] & Player) != 0)
// 			size++;
// 		else
// 			break;
// 		pos = (y - 1) * BOARD_HEIGHT + x - 1;
// 		x = pos % BOARD_WIDTH;
// 		y = pos / BOARD_HEIGHT;
// 	}
// 	return size > 1 ? size : 0;
// }
