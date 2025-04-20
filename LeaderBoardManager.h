#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "LeaderBoard.h"

using namespace std;

// Manager for handling multiple leaderboards and their persistence files
class LeaderBoardManager
{
private:
	vector<LeaderBoard> leaderBoards; // Collection of leaderboard instances
	vector<string> fileNames;         // Corresponding filenames for each leaderboard
public:
	// Construct manager with a given number of leaderboards (default 10)
	LeaderBoardManager(int count = 10);

	// Save all leaderboards to their respective files
	void saveAllLeaderBoards();

	// Get reference to the leaderboard at specified index
	LeaderBoard& getLeaderBoard(int index);

};

