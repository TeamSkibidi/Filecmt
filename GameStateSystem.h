#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>

#define ull unsigned long long

using namespace std;

class GameStateSystem {
private:
    struct PlayerState {

        string username;
        int now_score;
        int size;
        int** matrixGame;
        bool isContinue;
        bool isActive;
    };

    const int SIZE_HASH_TABLE = 100;
    const int MAX_LONGLONG = 1000000007;

    vector<PlayerState> hashTable;
    // Compute a hash value from the given username
    int hash_username(const string& username);
    // Derive the initial index in the hash table for the username
    int hash_to_index(const string& username);
    // Determine probing step size for collision resolution
    int hash_to_step(const string& username);
    // Write a string to an output file stream
    void save_string(ofstream& file, const string& str);
    // Read and return a string from an input file stream
    string load_string(ifstream& file);
    // Serialize a 2D int matrix of given size to file
    void save_matrix(ofstream& file, int** matrixGame, int size);
    // Deserialize a 2D int matrix of given size from file
    void load_matrix(ifstream& file, int**& matrixGame, int &size);

public:
    // Initialize the game state system and hash table
    GameStateSystem();
    // Insert or update the game state for a specific user
    void updateGameState(const string& username, int score, int** matrixGame, int size);
    // Save all player states to a file
    void save_to_file(const string& fileName);
    // Load all player states from a file
    void load_from_file(const string& fileName);

    int getSizeBoard(const string& userName) {
        int index = hash_to_index(userName);
        int step = hash_to_step(userName);
        int i = 0;

        while (hashTable[(index + i * step) % SIZE_HASH_TABLE].isActive == true) {
            int checkIndex = (index + i * step) % SIZE_HASH_TABLE;
            PlayerState& player = hashTable[checkIndex];
            if (player.username == userName) {
                return player.size;
                
            }
            ++i;
        }
        return 3;
    }
    int** getBoardGame(const string& userName) {
        int index = hash_to_index(userName);
        int step = hash_to_step(userName);
        int i = 0;

        while (hashTable[(index + i * step) % SIZE_HASH_TABLE].isActive == true) {
            int checkIndex = (index + i * step) % SIZE_HASH_TABLE;
            PlayerState& player = hashTable[checkIndex];
            if (player.username == userName) {
                return player.matrixGame;

            }
            ++i;
        }
        return nullptr;
    }
    int getScore(const string& userName) {
        int index = hash_to_index(userName);
        int step = hash_to_step(userName);
        int i = 0;

        while (hashTable[(index + i * step) % SIZE_HASH_TABLE].isActive == true) {
            int checkIndex = (index + i * step) % SIZE_HASH_TABLE;
            PlayerState& player = hashTable[checkIndex];
            if (player.username == userName) {
                return player.now_score;

            }
            ++i;
        }
        return 0;
    }
};
