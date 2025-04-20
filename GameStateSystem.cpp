#include "../../Header/Data-Logic/GameStateSystem.h"

// Calculates hash value for a username using polynomial rolling hash
int GameStateSystem::hash_username(const string& username) {
	ull hash = 0;
	for (char c : username) {
		hash = (hash * 31 + c) % MAX_LONGLONG;
	}

	return hash;
}

// Maps username to initial hash table index
int GameStateSystem::hash_to_index(const string& username) {
	return hash_username(username) % SIZE_HASH_TABLE;
}

// Determines probe step size for double hashing, ensuring it is odd
int GameStateSystem::hash_to_step(const string& username) {
	int step = hash_username(username) % (SIZE_HASH_TABLE - 1);
	if (step % 2 == 0) {
		step += 1;
	}

	return step;
}

// Writes a string to a binary file with length prefix
void GameStateSystem::save_string(ofstream& file, const string& str) {
	size_t length = str.size();
	file.write((char*)&length, sizeof(length));     //Ghi độ dài trước
	file.write(str.data(), length);
}

// Reads a length-prefixed string from a binary file
string GameStateSystem::load_string(ifstream& file) {
	size_t length;
	file.read((char*)&length, sizeof(length));

	string str(length, ' ');
	file.read(&str[0], length);

	return str;
}

// Saves a size x size matrix of ints to a binary file
void GameStateSystem::save_matrix(ofstream& file, int** matrixGame, int size) {
	file.write((char*)&size, sizeof(size));

	for (int i = 0; i < size; i++) {
		file.write((char*)matrixGame[i], size * sizeof(int));
	}
}

// Loads a size x size matrix from a binary file, allocating memory
void GameStateSystem::load_matrix(ifstream& file, int**& matrixGame, int& size) {
	file.read((char*)&size, sizeof(size));
	matrixGame = new int* [size];
	for (int i = 0; i < size; i++) {
		matrixGame[i] = new int[size];
		file.read((char*)matrixGame[i], size * sizeof(int));
	}
}

// Constructor: initializes hash table and loads data from file
GameStateSystem::GameStateSystem() : hashTable(SIZE_HASH_TABLE, { "", 0, 0, NULL, false, false })
{
	load_from_file("Source\\Data\\Continue\\Continue.dat");
};

// Inserts or updates the game state for a given username
void GameStateSystem::updateGameState(const string& username, int score, int** matrixGame, int size) {
	int index = hash_to_index(username);
	int step = hash_to_step(username);
	int i = 0;
	while (hashTable[(index + i * step) % SIZE_HASH_TABLE].isActive == true) {
		int checkIndex = (index + i * step) % SIZE_HASH_TABLE;
		PlayerState& player = hashTable[checkIndex];
		if (player.username == username) {
			player.now_score = score;
			//Xóa dữ liệu ma trận cũ
			for (int j = 0; j < player.size; j++) {
				delete[]player.matrixGame[j];
			}

			delete[]player.matrixGame;
			//Cập nhật size mới
			player.size = size;
			//Cập nhật dữ liệu ma trận mới
			player.matrixGame = new int* [size];
			for (int j = 0; j < size; j++) {
				player.matrixGame[j] = new int[size];
				for (int k = 0; k < size; k++) {
					player.matrixGame[j][k] = matrixGame[j][k];
				}
			}
			cout << "cap nhat thanh cong" << endl;
			return;
		}
		++i;
	}
	int indexOfEmpty = (index + i * step) % SIZE_HASH_TABLE;
	hashTable[indexOfEmpty].username = username;
	hashTable[indexOfEmpty].now_score = score;
	hashTable[indexOfEmpty].size = size;
	hashTable[indexOfEmpty].isActive = true;
	hashTable[indexOfEmpty].isContinue = true; // hoặc false tùy trạng thái game

	// Khởi tạo và copy ma trận
	hashTable[indexOfEmpty].matrixGame = new int* [size];
	for (int j = 0; j < size; j++) {
		hashTable[indexOfEmpty].matrixGame[j] = new int[size];
		for (int k = 0; k < size; k++) {
			hashTable[indexOfEmpty].matrixGame[j][k] = matrixGame[j][k];
		}
	}
}

// Serializes the entire hash table to a binary file
void GameStateSystem::save_to_file(const string& fileName) {
	ofstream file(fileName, ios::binary);
	if (!file.is_open()) {
		cout << "Khong the mo file ghi" << endl;
		return;
	}



	for (const PlayerState& player : hashTable) {
		save_string(file, player.username);
		file.write((char*)&player.now_score, sizeof(player.now_score));
		save_matrix(file, player.matrixGame, player.size);
		file.write((char*)&player.isContinue, sizeof(player.isContinue));
		file.write((char*)&player.isActive, sizeof(player.isActive));
	}


	file.close();
	cout << "Luu file thanh cong" << endl;
}

// Loads hash table data from file, or initializes empty file if not present
void GameStateSystem::load_from_file(const string& fileName) {
	ifstream file(fileName, ios::binary);
	if (!file.is_open()) {
		ofstream file_out(fileName, ios::binary);
		for (int i = 0; i < SIZE_HASH_TABLE; i++) {
			PlayerState  emptyUser = {};
			save_string(file_out, "");
			file_out.write((char*)&emptyUser.now_score, sizeof(emptyUser.now_score));
			save_matrix(file_out, emptyUser.matrixGame, emptyUser.size);
			file_out.write((char*)&emptyUser.isContinue, sizeof(emptyUser.isContinue));
			file_out.write((char*)&emptyUser.isActive, sizeof(bool));
		}
		file_out.close();
		return;
	}

	for (PlayerState& player : hashTable) {
		player.username = load_string(file);
		file.read((char*)&player.now_score, sizeof(player.now_score));
		load_matrix(file, player.matrixGame, player.size);
		file.read((char*)&player.isContinue, sizeof(player.isContinue));
		file.read((char*)&player.isActive, sizeof(player.isActive));
	}

	file.close();
	cout << "Tai du lieu thanh cong" << endl;
}
