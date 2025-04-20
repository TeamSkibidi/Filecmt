#include "../../Header/Logic/StateManagement.h"


// Swaps all elements between two square boards of size sizeBoard
void Swap(int**& boardGame, int**& newBoard, int sizeBoard)
{	
	int temp;
	for (int i = 0; i < sizeBoard; i++) {
		for (int j = 0; j < sizeBoard; j++) {
			temp = boardGame[i][j];
			boardGame[i][j] = newBoard[i][j];
			newBoard[i][j] = temp;
		}
	}
}

// Allocates a new sizeBoard x sizeBoard game board and initializes all cells to zero
void createGame(int**& boardGame, int sizeBoard) {
	int n = sizeBoard;
	boardGame = new int* [n];
	for (int i = 0; i < n; i++) {
		boardGame[i] = new int[n];
		for (int j = 0; j < n; j++) {
			boardGame[i][j] = 0;
		}
	}
}

// Deletes the dynamically allocated game board and sets pointer to nullptr
void DeleteGame(int**& boardGame, int sizeBoard) {
	int n = sizeBoard;
	for (int i = 0; i < n; i++) {
		delete[] boardGame[i];
	}
	delete[] boardGame;
	boardGame = nullptr;
}

// Creates and returns a deep copy of a given sizeBoard x sizeBoard board
int** copyBoard(int** boardGame, int sizeBoard) {
	if (boardGame == nullptr) return nullptr;
	int** newBoard = new int* [sizeBoard];
	for (int i = 0; i < sizeBoard; i++) {
		newBoard[i] = new int[sizeBoard];
		for (int j = 0; j < sizeBoard; j++) {
			newBoard[i][j] = boardGame[i][j];
		}
	}
	return newBoard;
}

// Resets all cells of the board to zero (useful for clearing state)
void setBoard(int** &boardGame, int sizeBoard) {
	for (int i = 0; i < sizeBoard; i++) {
		for (int j = 0; j < sizeBoard; j++) {
			boardGame[i][j] = 0;
		}
	}
}
