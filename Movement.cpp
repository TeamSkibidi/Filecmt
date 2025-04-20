#include "../../Header/Logic/Movement.h"

// Init queue empty
Queue::Queue() : front(0) {}

// Check empty
bool Queue::checkempty() {
	return front >= data.size(); //	return true when queue empty or  opposite
}

// Add value
void Queue::push(int value) {
	data.push_back(value);
}

// Take first element and it remove
int Queue::pop() {
	if (checkempty()) return -1;
	return data[front++];
}

// Only watch and not remove
int Queue::peek() {
	if (checkempty()) return -1;
	return data[front];
}

// Go up
void goup(int** BoardGame, int sizeBoard, int& score) {
	// browse each colums
	for (int j = 0; j < sizeBoard; j++) {
		Queue queue;
		// take elements in colums j has value different 0 into queue (from top to bottom)
		for (int i = 0; i < sizeBoard; i++) {
			if (BoardGame[i][j] != 0) {
				queue.push(BoardGame[i][j]);
			}
		}

		int idx = 0;
		// take each element in order of priority and merge if consecutive elements the same
		while (!queue.checkempty()) { // if queue not empty then run
			int value = queue.pop();
			// peek continue value and merge if it the same
			if (!queue.checkempty() && queue.peek() == value) {
				value *= 2;
				score += value;
				queue.pop(); // remove element just peek
			}
			BoardGame[idx++][j] = value;
		}
		// fill 0 into rest celss of colums
		while (idx < sizeBoard) BoardGame[idx++][j] = 0;
	}
}

// Go down
void godown(int** BoardGame, int sizeBoard, int &score) {
	// browse each colums
	for (int j = 0; j < sizeBoard; j++) {
		Queue queue;
		// take elements in colums j has value different 0 into queue (from bottom to top)
		for (int i = sizeBoard - 1; i >= 0; i--) {
			if (BoardGame[i][j] != 0) {
				queue.push(BoardGame[i][j]);
			}
		}

		int idx = sizeBoard - 1;
		// take each element in order of priority and merge if consecutive elements the same
		while (!queue.checkempty()) { // if queue not empty then run
			int value = queue.pop();
			if (!queue.checkempty() && queue.peek() == value) {
				value *= 2;
				score += value;
				queue.pop();
			}
			BoardGame[idx--][j] = value;
		}
		// fill 0 into rest cells of colums
		while (idx >= 0) BoardGame[idx--][j] = 0;

	}
}

// Turn left
void turnleft(int** BoardGame, int sizeBoard, int& score) {
	// browse each row
	for (int i = 0; i < sizeBoard; i++) {
		Queue queue;
		// take element in row i has value different 0 into queue (from left to right)
		for (int j = 0; j < sizeBoard; j++) {
			if (BoardGame[i][j] != 0) {
				queue.push(BoardGame[i][j]);
			}
		}
		int idx = 0;
		// take each element in order of priority and merge if consecutive elements the same
		while (!queue.checkempty()) { // if queue not empty then run
			int value = queue.pop();
			if (!queue.checkempty() && queue.peek() == value) {
				value *= 2;
				score += value;
				queue.pop(); // remove element just peek
			}
			BoardGame[i][idx++] = value;
		}
		// fill value 0 into rest cells
		while (idx < sizeBoard) BoardGame[i][idx++] = 0;

	}
}

// Turn right
void turnright(int** BoardGame, int sizeBoard, int& score) {
	// browse each row
	for (int i = 0; i < sizeBoard; i++) {
		Queue queue;
		// take element in row i has value different 0 into queue (from right to left)
		for (int j = sizeBoard - 1; j >= 0; j--) {
			if (BoardGame[i][j] != 0) {
				queue.push(BoardGame[i][j]);
			}
		}

		int idx = sizeBoard - 1;
		// take each element in order of priority and merge if consecutive elements the same
		while (!queue.checkempty()) { // if queue empty then run
			int value = queue.pop();
			if (!queue.checkempty() && queue.peek() == value) {
				value *= 2;
				score += value;
				queue.pop(); // remove element just peek
			}
			BoardGame[i][idx--] = value;
		}
		// fill value 0 into rest cells 
		while (idx >= 0) BoardGame[i][idx--] = 0;
	}
}

// Check Change
bool check_change(int** BoardGame, int sizeGame, int** oldBoard) {
	for (int i = 0; i < sizeGame; i++) {
		for (int j = 0; j < sizeGame; j++) {
			if (BoardGame[i][j] != oldBoard[i][j]) {
				return true;
			}
		}
	}
	return false;
}
