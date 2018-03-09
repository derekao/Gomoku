#include "Heuristic.class.hpp"

// static void printBoard(GameManager * Board)
// {
// 	for (int i = 0; i < 361; i ++)
// 	{
// 		std::cout << Board->getBoard()[i] << " ";
// 		if (i % 19 == 18)
// 			std::cout << std::endl;
// 	}
// }

Heuristic::Heuristic(int iPlayer, int iOpponent, GameManager * gInstance) 
	: Player(iPlayer), Opponent(iOpponent), Instance(gInstance), HighestPriority(7)
{
}

int Heuristic::BoardValue() {
	int value = 0;
	int pos = 0;
	std::vector<Coord> vPlayer;
	std::vector<Coord> vOpponent;
	
	if ((Player == STONE_BLACK && (Instance->getBlackWin() || Instance->getBlackScore() >= 10)) || (Player == STONE_WHITE && (Instance->getWhiteWin() || Instance->getWhiteScore() >= 10))) {
		return MAX_INFINIT;
	}
	else if ((Opponent == STONE_BLACK && (Instance->getBlackWin() || Instance->getBlackScore() >= 10)) || (Opponent == STONE_WHITE && (Instance->getWhiteWin() || Instance->getWhiteScore() >= 10))) {
		return MIN_INFINIT;
	}
	
	if ((Player & STONE_BLACK ) != 0) {
		vPlayer = Instance->getBlackStones();
		vOpponent = Instance->getWhiteStones();
	}
	else {
		vOpponent = Instance->getBlackStones();
		vPlayer = Instance->getWhiteStones();
	}

	for (size_t i = 0; i < vPlayer.size(); i++) {
		pos = Instance->getBlackStones()[i].y * BOARD_HEIGHT + Instance->getBlackStones()[i].x;

		//Horizontale
		value += CountHorizontalAlignmentScore(pos, true);

		// Vertical
		value += CountVerticalAlignmentScore(pos, true);

		// Diagonnal Right
		value += CountDiagonnalRightAlignmentScore(pos, true);

		// Diagonnal Left
		value += CountDiagonnalLeftAlignmentScore(pos, true);
	}
	for (size_t i = 0; i < vOpponent.size(); i++) {
		pos = Instance->getBlackStones()[i].y * BOARD_HEIGHT + Instance->getBlackStones()[i].x;
		// Horizontal
		value -= CountHorizontalAlignmentScore(pos, false);
		// Vertical
		value -= CountVerticalAlignmentScore(pos, false);
		// Diagonnal Right
		value -= CountDiagonnalRightAlignmentScore(pos, false);
		// Diagonnal Left
		value -= CountDiagonnalLeftAlignmentScore(pos, false);
	}

	return value;
}

int Heuristic::CountHorizontalAlignmentScore(int pos, bool lookFor, bool SearchMove) {
	int x = pos % BOARD_WIDTH;
	int y = pos / BOARD_HEIGHT;
	int size = 0;
	int potentialSize = 0;
	int iNonFullAlign = 0;
	bool bBorderStart = false;
	bool bBorderEnd = false;
	bool bBlockStart = false;
	bool bBlockEnd = false;

	if (x == 0) // Enregistre si l'alignement commence sur le bord de la map
		bBorderStart = true;
	if (x > 0 && (Instance->getBoard()[y * BOARD_WIDTH + x - 1] & lookFor ? Player : Opponent) != 0) {
		return 0;
	}
	else if (x > 0) { // Verifie que l'alignement n'a pas deja etait compté
		
		if ((Instance->getBoard()[y * BOARD_WIDTH + x - 1] & lookFor ? Opponent : Player) != 0) // Verifie que l'alignement n'est pas bloqué par l'adversaire
			bBlockStart = true;
		else { // Sinon compte la taille potentiel de l'alignement depuis le début
			for (int tmp = pos - 1; y == tmp / BOARD_HEIGHT && tmp >= 0; tmp--) {
				if (Rules::EmptyCase(Instance->getBoard()[tmp]))
					potentialSize++;
				else
					break;
				if (potentialSize >= 5)
					break ;
			}
		}
	}

	while (y == pos / BOARD_HEIGHT && pos < BOARD_HEIGHT * BOARD_WIDTH && !bBlockEnd) { // Calcule la taille de l'alignement
		if ((Instance->getBoard()[pos] & lookFor ? Player : Opponent) != 0) { // Calcul la taille
			size++;
			if (pos % BOARD_WIDTH == BOARD_WIDTH - 1) // Enregistre si on arrive sur un bord
				bBorderEnd = true;
		}
		else if ((Instance->getBoard()[pos] & lookFor ? Opponent : Player) != 0 && (iNonFullAlign == 0 || iNonFullAlign < size)) // Verifie que l'alignement n'est pas bloqué par l'adversaire
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
			if (Rules::EmptyCase(Instance->getBoard()[pos]))
				potentialSize++;
			else
				break ;
			if (potentialSize >= 5)
				break ;
		}
	}
	potentialSize += size;
	if (SearchMove) {
		getMovePriority(size, potentialSize, bBorderStart, bBorderEnd, bBlockStart, bBlockEnd, (iNonFullAlign < size) ? iNonFullAlign : 0, pos, HORIZONTAL, lookFor);
		return 0;
	}
	return CountHeuristicAlignmentScore(size, potentialSize, (bBorderStart || bBorderEnd), bBlockStart, bBlockEnd, (iNonFullAlign < size) ? iNonFullAlign : 0);
}

int Heuristic::CountVerticalAlignmentScore(int pos, bool lookFor, bool SearchMove) {
	int x = pos % BOARD_WIDTH;
	int y = pos / BOARD_HEIGHT;
	int size = 0;
	int potentialSize = 0;
	int iNonFullAlign = 0;
	bool bBorderStart = false;
	bool bBorderEnd = false;
	bool bBlockStart = false;
	bool bBlockEnd = false;

	if (y == 0)
		bBorderStart = true;
	if (y > 0 && (Instance->getBoard()[(y - 1) * BOARD_WIDTH + x] & lookFor ? Player : Opponent) != 0) {
		return 0;
	}
	else if (y > 0) {
		
		if ((Instance->getBoard()[(y - 1) * BOARD_WIDTH + x] & lookFor ? Opponent : Player) != 0)
			bBlockStart = true;
		else {
			for (int tmp = pos - BOARD_WIDTH; tmp >= 0; tmp -= BOARD_WIDTH) {
				if (Rules::EmptyCase(Instance->getBoard()[tmp]))
					potentialSize++;
				else
					break ;
				if (potentialSize >= 5)
					break ;
			}
		}
	}

	while (pos < BOARD_HEIGHT * BOARD_WIDTH && !bBlockEnd) {
		if ((Instance->getBoard()[pos] & lookFor ? Player : Opponent) != 0) {
			size++;
			if ((pos / BOARD_HEIGHT) == BOARD_HEIGHT - 1)
				bBorderEnd = true;
		}
		else if ((Instance->getBoard()[pos] & lookFor ? Opponent : Player) != 0 && (iNonFullAlign == 0 || iNonFullAlign < size))
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
			if (Rules::EmptyCase(Instance->getBoard()[pos]))
				potentialSize++;
			else
				break ;
			if (potentialSize >= 5)
				break ;
		}
	}
	potentialSize += size;
	if (SearchMove) {
		getMovePriority(size, potentialSize, bBorderStart, bBorderEnd, bBlockStart, bBlockEnd, (iNonFullAlign < size) ? iNonFullAlign : 0, pos, VERTICAL, lookFor);
		return 0;
	}
	return CountHeuristicAlignmentScore(size, potentialSize, (bBorderStart || bBorderEnd), bBlockStart, bBlockEnd, (iNonFullAlign < size) ? iNonFullAlign : 0);
}

int Heuristic::CountDiagonnalRightAlignmentScore(int pos, bool lookFor, bool SearchMove) {
	int x = pos % BOARD_WIDTH;
	int y = pos / BOARD_HEIGHT;
	int size = 0;
	int potentialSize = 0;
	int iNonFullAlign = 0;
	bool bBorderStart = false;
	bool bBorderEnd = false;
	bool bBlockStart = false;
	bool bBlockEnd = false;

	if (y == 0 || x == 0)
		bBorderStart = true;
	if (y > 0 && x > 0 && (Instance->getBoard()[(y - 1) * BOARD_WIDTH + x - 1] & lookFor ? Player : Opponent) != 0) {
		return 0;
	}
	else if (y > 0 && x > 0) {
		
		if ((Instance->getBoard()[(y - 1) * BOARD_WIDTH + x - 1] & lookFor ? Opponent : Player) != 0)
			bBlockStart = true;
		else {
			while (x - 1 >= 0 && y - 1 >= 0) {
				if (Rules::EmptyCase(Instance->getBoard()[(y - 1) * BOARD_WIDTH + x - 1]))
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
		if ((Instance->getBoard()[y * BOARD_WIDTH + x] & lookFor ? Player : Opponent) != 0) {
			size++;
			if (x == BOARD_WIDTH - 1 || y == BOARD_HEIGHT - 1)
				bBorderEnd = true;
		}
		else if ((Instance->getBoard()[y * BOARD_WIDTH + x] & lookFor ? Opponent : Player) != 0 && (iNonFullAlign == 0 || iNonFullAlign < size))
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
			if (Rules::EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x]))
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
	if (SearchMove) {
		getMovePriority(size, potentialSize, bBorderStart, bBorderEnd, bBlockStart, bBlockEnd, (iNonFullAlign < size) ? iNonFullAlign : 0, pos, DIAGORIGHT, lookFor);
		return 0;
	}
	return CountHeuristicAlignmentScore(size, potentialSize, (bBorderStart || bBorderEnd), bBlockStart, bBlockEnd, (iNonFullAlign < size) ? iNonFullAlign : 0);
}

int Heuristic::CountDiagonnalLeftAlignmentScore(int pos, bool lookFor, bool SearchMove) {
	int x = pos % BOARD_WIDTH;
	int y = pos / BOARD_HEIGHT;
	int size = 0;
	int potentialSize = 0;
	int iNonFullAlign = 0;
	bool bBorderStart = false;
	bool bBorderEnd = false;
	bool bBlockStart = false;
	bool bBlockEnd = false;

	if (y == 0 || x == BOARD_WIDTH - 1)
		bBorderStart = true;
	if (y > 0 && x < BOARD_WIDTH - 1 && (Instance->getBoard()[(y - 1) * BOARD_HEIGHT + x + 1] & lookFor ? Player : Opponent) != 0) {
		return 0;
	}
	else if (y > 0 && x < BOARD_WIDTH - 1) {
		
		if ((Instance->getBoard()[(y - 1) * BOARD_HEIGHT + x + 1] & lookFor ? Opponent : Player) != 0)
			bBlockStart = true;
		else {
			while (x + 1 <= BOARD_WIDTH && y - 1 >= 0) {
				if (Rules::EmptyCase(Instance->getBoard()[(y - 1) * BOARD_WIDTH + x + 1]))
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
		if ((Instance->getBoard()[y * BOARD_WIDTH + x] & lookFor ? Player : Opponent) != 0) {
			size++;
			if (x == 0 || y == BOARD_HEIGHT - 1)
				bBorderEnd = true;
		}
		else if ((Instance->getBoard()[y * BOARD_WIDTH + x] & lookFor ? Opponent : Player) != 0 && (iNonFullAlign == 0 || iNonFullAlign < size))
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
			if (Rules::EmptyCase(Instance->getBoard()[y * BOARD_WIDTH + x]))
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
	if (SearchMove) {
		getMovePriority(size, potentialSize, bBorderStart, bBorderEnd, bBlockStart, bBlockEnd, (iNonFullAlign < size) ? iNonFullAlign : 0, pos, DIAGOLEFT, lookFor);
		return 0;
	}
	return CountHeuristicAlignmentScore(size, potentialSize, (bBorderStart || bBorderEnd), bBlockStart, bBlockEnd, (iNonFullAlign < size) ? iNonFullAlign : 0);
}

int Heuristic::CountHeuristicAlignmentScore(int size, int potentialSize, bool bBorder, bool bBlockStart, bool bBlockEnd, int bUnbound) {
	int score = 0;

	 // Tmp
	
	if (size < 5 && potentialSize < 5) { // Alignement inferieur à 5 et potentiellement inferieur à 5
		if (!bBorder && ((size == 2 && bBlockStart && !bBlockEnd) || (size == 2 && !bBlockStart && bBlockEnd))) // Peut etre mangé
			score += 0;
		else
			score += 0;
	}
	else
		score += pow(10, size);
	if (bBorder || bUnbound) {
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

void Heuristic::addMove(int y, int x, int score) {
	if (score <= HighestPriority) {
		if (score != CAPTURE && score < HighestPriority)
			score = HighestPriority;
		Instance->getPotentialMove().push_back(PotentialMove(y, x, score));
	}
}

void Heuristic::getMovePriority(int size, int potentialSize, bool bBorderStart, bool bBorderEnd, bool bBlockStart, bool bBlockEnd, int Unbound, int pos, int type, bool who) {
	int xVar = 0;
	int yVar = 0;
	int score = 0;
	int x = pos % BOARD_WIDTH;
	int y = pos / BOARD_WIDTH;

	if (type == HORIZONTAL)
		xVar = 1;
	else if (type == VERTICAL)
		yVar = 1;
	else if (type == DIAGORIGHT) {
		xVar = 1;
		yVar = 1;
	}
	else {
		xVar = -1;
		yVar = 1;
	}
	std::cout << "coo" << std::endl;

	if (size >= 4 && potentialSize > 4) {
		score = who ? OTW_PLAYER : OTW_OPPONENT;
		if (!bBlockStart && !bBorderStart && !Unbound)
			addMove(y - yVar, x - xVar, score);
		if (!bBlockEnd && !bBorderEnd && !Unbound)
			addMove(y + yVar * size, x + xVar * size, score);
		if (Unbound)
			addMove(y + yVar * Unbound, x + xVar * Unbound, score);
	}
	else if (size == 3 && potentialSize > 4) {
		if (!bBorderStart && !bBorderEnd && !bBlockStart && !bBlockEnd) {
			score = who ? TTW_PLAYER : TTW_OPPONENT;
			if (!Unbound) {
				addMove(y - yVar, x - xVar, score);
				addMove(y + yVar * size, x + xVar * size, score);
			}
			if (Unbound)
				addMove(y + yVar * Unbound, x + xVar * Unbound, score);
		}
		else {
			score = score = who ? STRONG_MOVE : BAD_MOVE;
			if (!bBlockStart && !bBorderStart && !Unbound)
			{
				addMove(y - yVar, x - xVar, score);
				if (x - xVar * 2 >= 0 && y - yVar * 2 >= 0 && Instance->getBoard()[pos - xVar * 2 - yVar * 2 * BOARD_WIDTH])
					addMove(y - yVar * 2, x - xVar * 2, score);
			}
			if (!bBlockEnd && !bBorderEnd && !Unbound)
			{
				addMove(y + yVar * size, x + xVar * size, score);
				if (x + xVar * (size + 1) < BOARD_WIDTH && y + yVar * (size + 1) < BOARD_HEIGHT && Instance->getBoard()[pos + xVar * (size + 1) + yVar * (size + 1) * BOARD_WIDTH] && !Unbound)
					addMove(y + yVar * (size + 1), x + xVar * (size + 1), score);
			}
			if (Unbound)
				addMove(y + yVar * Unbound, x + xVar * Unbound, score);
		}
	}
	else if (size == 2 && potentialSize > 5 && !bBorderStart && !bBorderEnd && !bBlockStart && !bBlockEnd) {
		score = who ? STRONG_MOVE : AVERAGE_MOVE;
		if (x - xVar * 2 >= 0 && y - yVar * 2 >= 0 && Instance->getBoard()[pos - xVar * 2 - yVar * 2 * BOARD_WIDTH] && !Unbound)
		{
			addMove(y - yVar, x - xVar, score);
			addMove(y - yVar * 2, x - xVar * 2, score);
		}
		else if (x + xVar * (size + 1) < BOARD_WIDTH && y + yVar * (size + 1) < BOARD_HEIGHT && Instance->getBoard()[pos + xVar * (size + 1) + yVar * (size + 1) * BOARD_WIDTH] && !Unbound)
		{
			addMove(y + yVar * size, x + xVar * size, score);
			addMove(y + yVar * (size + 1), x + xVar * (size + 1), score);
		}
		else if (Unbound) {
			addMove(y - yVar, x - xVar, score);
			addMove(y + yVar * size, x + xVar * size, score);
			addMove(y + yVar * Unbound, x + xVar * Unbound, score);
		}
	}
	else if (size == 2 && potentialSize > 2 && !Unbound && (bBorderStart || bBorderEnd)) {
		score = who ? STRONG_MOVE : CAPTURE;
		if (bBorderStart)
		{
			addMove(y + yVar * size, x + xVar * size, score);
		}
		else
		{
			addMove(y - yVar, x - xVar, score);
		}
	}
	else if (size == 1 && potentialSize > 5 && !bBorderStart && !bBorderEnd) {
		score = BAD_MOVE;
		if (!bBorderStart)
			addMove(y - yVar, x - xVar, score);
		if (!bBorderEnd)
			addMove(y + yVar, x + xVar, score);
	}
}

void Heuristic::searchMoves() {
	int pos = 0;
	std::vector<Coord> vPlayer;
	std::vector<Coord> vOpponent;
	if ((Player & STONE_BLACK ) != 0) {
		vPlayer = Instance->getBlackStones();
		vOpponent = Instance->getWhiteStones();
	}
	else {
		vOpponent = Instance->getBlackStones();
		vPlayer = Instance->getWhiteStones();
	}

	for (size_t i = 0; i < vPlayer.size(); i++) {
		std::cout << "PLA Y: "<< vPlayer[i].y << " X: " << vPlayer[i].x << std::endl;
		pos = (vPlayer[i].y) * BOARD_HEIGHT + vPlayer[i].x ;
		//Horizontale
		CountHorizontalAlignmentScore(pos, true, true);

		// Vertical
		CountVerticalAlignmentScore(pos, true, true);

		// Diagonnal Right
		CountDiagonnalRightAlignmentScore(pos, true, true);

		// Diagonnal Left
		CountDiagonnalLeftAlignmentScore(pos, true, true);
	}
	for (size_t i = 0; i < vOpponent.size(); i++) {
		std::cout << "OPP Y: "<< vOpponent[i].y << " X: " << vOpponent[i].x << std::endl;
		pos = (vOpponent[i].y) * BOARD_HEIGHT + vOpponent[i].x ;
		// Horizontal
		CountHorizontalAlignmentScore(pos, false, true);
		// Vertical
		CountVerticalAlignmentScore(pos, false, true);
		// Diagonnal Right
		CountDiagonnalRightAlignmentScore(pos, false, true);
		// Diagonnal Left
		CountDiagonnalLeftAlignmentScore(pos, false, true);
	}
	Instance->setHighestPriority(HighestPriority);
}
