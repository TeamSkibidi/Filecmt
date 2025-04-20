#pragma once
#include <vector>

using namespace std;

class TitleQueue {
private:
	vector<int> data;
	int front;
public:
	// Init Queue and set up queue is empty
	TitleQueue();

	// Check queue has empty or not 
	bool checkempty();

	// Add value into queue
	void push(int value);

	// Take first element out of the queue
	int pop();

	// Only watch not remove first element
	int peek();

};
