#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct PlayerNode {
    string name; // Player's name
    int score;  // Player's score
    PlayerNode* left;
    PlayerNode* right;

    PlayerNode(string n, int s) : name(n), score(s), left(NULL), right(NULL) {};

};

class LeaderBoard
{
private:
    PlayerNode* root;          // Root of BST storing players
    const int MAX_PLAYER = 10; // Maximum top players to retrieve

    // Count number of nodes in subtree
    int countPlayer(PlayerNode* root);

    // Find node with minimum score in subtree
    PlayerNode* findMin(PlayerNode* root);

    // Insert or update player in BST
    PlayerNode* insertPlayer(PlayerNode* root, string name, int score);

    // Remove player by score from BST
    PlayerNode* deletePlayer(PlayerNode* root, int score);

    // Search for player by name in BST
    PlayerNode* searchPlayer(PlayerNode* root, string name);

    // Save BST nodes to file (in-order)
    void saveToFile(ofstream& file, PlayerNode* root);

    // Load BST from file data
    PlayerNode* loadFromFile(ifstream& file);

    // Collect top players up to limit into list
    void getTopPlayer(PlayerNode* node, vector<PlayerNode*>& list, int limit = 10);
 
public:

    // Initialize empty leaderboard
    LeaderBoard();

    // Add new score or update existing player's score
    void updateScoreOrAdd(string name, int newScore);

    // Save leaderboard to external file
    void saveToFile(const string& filename);

    // Load leaderboard from external file
    void loadFromFile(const string& filename);

    // Retrieve list of top players up to limit
    void getTopplayer(vector<PlayerNode*>& list, int limit);

};

