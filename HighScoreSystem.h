#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

struct Player_highScore {
	string username;           // Player's username
	vector<int> highScore;     // List of high scores per game mode
	bool isActive;             // Indicates if entry is active
};

#define ull unsigned long long


const int SIZE_HASH_TABLE = 100;
const int MAX_LONGLONG = 1000000007;

class HighScoreSystem {
private:
	// Storage for player high scores
	vector<Player_highScore> hashTable;

	// Compute a hash value from username string
	int hash_username(const string& username);
	// Calculate initial table index from hashed username
	int hash_to_index(const string& username);
	// Determine step size for probing on collision
	int hash_to_step(const string& username);
	// Write a string to output file stream
	void save_string(ofstream& file, const string& str);
	// Read a string from input file stream
	string load_string(ifstream& file);
	// Serialize integer vector to file
	void save_Vector(ofstream& file, const vector<int>& vec);	
	// Deserialize integer vector of given size from file
	void load_Vector(ifstream& file, vector<int>& vec, int size);

public:
	// Initialize high score system
	HighScoreSystem();
	// Update user's high score for specific game mode
	void update_high_score(const string& username, int gameMode, int score);
	// Retrieve user's high score for specific game mode
	int getHighScore(const string& username, int gameMode);
	// Save all high scores to a file
	void save_to_file(const string& fileName);
	// Load all high scores from a file
	void load_from_file(const string& fileName);
};

