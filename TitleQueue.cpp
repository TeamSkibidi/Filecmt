#include "../../Header/Logic/TitleQueue.h"

// Initializes an empty queue by setting the front index to 0
TitleQueue::TitleQueue() : front(0) {}

// Returns true if the queue is empty (front has reached or passed end of data)
bool TitleQueue::checkempty() {
	return front >= data.size(); //	return true when queue empty or  opposite
}

// Adds a new integer value to the end of the queueoid TitleQueue::push(int value) {
void TitleQueue::push(int value) {
	data.push_back(value);
}

// Removes and returns the first element; returns -1 if queue is empty
int TitleQueue::pop() {
	if (checkempty()) return -1;
	return data[front++];
}

// Returns the first element without removing it; returns -1 if queue is empty
int TitleQueue::peek() {
	if (checkempty()) return -1;
	return data[front];
}
