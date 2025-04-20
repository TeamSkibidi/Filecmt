#pragma once

// Swaps the contents of two game boards
void Swap(int**& boardGame, int**& newBoard, int sizeBoard);

// Creates and initializes a new empty game board
void createGame(int**& boardGame, int sizeBoard);

// Deletes the game board and frees memory
void DeleteGame(int**& boardGame, int sizeBoard);

// Returns a deep copy of the given game board
int** copyBoard(int** boardGame, int sizeBoard);

// Sets up the board with initial values
void setBoard(int**& boardGame, int sizeBoard);
