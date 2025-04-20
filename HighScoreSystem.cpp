#include "../../Header/Data-Logic/HighScoreSystem.h"

// Calculates hash value for a username using polynomial rolling hash
int HighScoreSystem::hash_username(const string& username) {
	ull hash = 0;
	for (char c : username) {
		hash = (hash * 31 + c) % MAX_LONGLONG;
	}

	return hash;
}

// Maps username to initial hash table index
int HighScoreSystem::hash_to_index(const string& username) {
	return hash_username(username) % SIZE_HASH_TABLE;
}

// Determines probe step size for double hashing, ensuring it is odd
int HighScoreSystem::hash_to_step(const string& username) {
	int step = hash_username(username) % (SIZE_HASH_TABLE - 1);
	if (step % 2 == 0) {
		step += 1;
	}

	return step;
}

// Writes a string to a binary file with length prefix
void HighScoreSystem::save_string(ofstream& file, const string& str) {
	size_t length = str.size();
	file.write((char*)&length, sizeof(length));    
	file.write(str.data(), length);
}

// Reads a length-prefixed string from a binary file with error check
string HighScoreSystem::load_string(ifstream& file) {
	size_t length;
	file.read((char*)&length, sizeof(length));


	if (length > 1000) {
		cerr << "Length quá lớn: " << length << endl;
		throw runtime_error("Lỗi file: độ dài chuỗi không hợp lệ");
	}
	string str(length, ' ');
	file.read(&str[0], length);

	return str;
}

// Saves vector of ints sequentially to binary file
void HighScoreSystem::save_Vector(ofstream& file, const vector<int>& vec)
{
	for (int i = 0; i < vec.size(); ++i) {
		file.write((char*)(&vec[i]), sizeof(int));
	}
}

// Loads vector of a given size from binary file
void HighScoreSystem::load_Vector(ifstream& file, vector<int>& vec, int size)
{
	vec.resize(size);
	for (int i = 0; i < size; ++i) {
		file.read((char*)(&vec[i]), sizeof(int));
	}
}

// Constructor: initializes hash table and loads data from file
HighScoreSystem::HighScoreSystem() : hashTable(SIZE_HASH_TABLE, { "", vector<int>(10 ,0), false }) {
	load_from_file("Source\\Data\\LeaderBoard\\HighScore.dat");
};

// Updates or inserts high score for user and game mode
void HighScoreSystem::update_high_score(const string& username, int gameMode, int score) {
	int index = hash_to_index(username);
	int step = hash_to_step(username);
	int i = 0;

	while (hashTable[(index + i * step) % SIZE_HASH_TABLE].isActive == true) {
		int checkIndex = (index + i * step) % SIZE_HASH_TABLE;
		Player_highScore& player = hashTable[checkIndex];
		if (player.username == username) {
			if (score > player.highScore[gameMode]) {
				player.highScore[gameMode] = score;
				cout << "Cap nhat diem thanh cong" << endl;
			}
			return;
		}

		++i;
	}

	//Nếu không tìm ra tức ở bên hash table này điểm người đó chưa được cập nhật
	int newIndex = (index + i * step) % SIZE_HASH_TABLE;
	hashTable[newIndex] = { username, vector<int>(10, 0), true };
	hashTable[newIndex].highScore[gameMode] = score;
	cout << "Tao moi va cap nhat diem thanh cong" << endl;
}

// Retrieves the high score for a user and game mode, or -1 if not found
int HighScoreSystem::getHighScore(const string& username, int gameMode) {
	int index = hash_to_index(username);
	int step = hash_to_step(username);

	int i = 0;
	while (hashTable[(index + i * step) % SIZE_HASH_TABLE].isActive) {
		int checkIdex = (index + i * step) % SIZE_HASH_TABLE;
		Player_highScore& player = hashTable[checkIdex];

		if (player.username == username) {
			return player.highScore[gameMode];
		}
		++i;

	}

	return -1;
}

// Loads high score table from file or initializes new file if missing
void HighScoreSystem::load_from_file(const string& fileName) {
	ifstream file(fileName, ios::binary);
	if (!file.is_open()) {
		ofstream file_out(fileName, ios::binary);
		for (int i = 0; i < SIZE_HASH_TABLE; i++) {
			Player_highScore  emptyUser = {};
			save_string(file_out, "");
			save_Vector(file_out, emptyUser.highScore);
			file_out.write((char*)emptyUser.highScore.data(), emptyUser.highScore.size() * sizeof(int));
			file_out.write((char*)&emptyUser.isActive, sizeof(bool));
		}
		file_out.close();
		return;
	}

	int index = 0;
	while (index < SIZE_HASH_TABLE) {
		Player_highScore user;
		user.username = load_string(file);
		cout << index << " " << user.username << endl;
		load_Vector(file, user.highScore, 10);
		file.read((char*)&user.isActive, sizeof(user.isActive));
		hashTable[index++] = user;
	}
	file.close();
	cout << "Tai du lieu thanh cong" << endl;
}

// Saves high score table to binary file
void HighScoreSystem::save_to_file(const string& fileName) {
	ofstream file(fileName, ios::binary);
	if (!file.is_open()) {
		cout << "Không thể mở file để ghi" << endl;
		return;
	}

	for (const Player_highScore& player : hashTable) {
		save_string(file, player.username);
		save_Vector(file, player.highScore);
		file.write((char*)(&player.isActive), sizeof(bool));
	}

	file.close();
	cout << "Lưu file thành công" << endl;
}
