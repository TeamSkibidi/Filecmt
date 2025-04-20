#pragma once

#include <vector>

using namespace std;



class Queue {
private:
	vector<int> data;
	int front;
public:
	// Init Queue and set up queue is empty
	Queue();

	// Check queue has empty or not 
	bool checkempty();

	// Add value into queue
	void push(int value);

	// Take first element out of the queue
	int pop();

	// Only watch not remove first element
	int peek();

};

// Moves the board upwards and merges tiles; updates the score
void goup(int** BoardGame, int sizeBoard, int& score);

// Moves the board downwards and merges tiles; updates the score
void godown(int** BoardGame, int sizeBoard, int& score);

// Moves the board to the left and merges tiles; updates the score
void turnleft(int** BoardGame, int sizeBoard, int& score);

// Moves the board to the right and merges tiles; updates the score
void turnright(int** BoardGame, int sizeBoard, int& score);

// Checks if the board has changed compared to a previous state
bool check_change(int** BoardGame, int sizeGame, int** oldBoard);
