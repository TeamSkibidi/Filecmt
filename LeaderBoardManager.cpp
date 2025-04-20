#include "../../Header/Data-Logic/LeaderBoardManager.h"

// Constructor: initializes and loads each leaderboard file
LeaderBoardManager::LeaderBoardManager(int count)
{
    for (int i = 0; i < 10; ++i) {
        LeaderBoard lb;  // Tạo một đối tượng LeaderBoard mới
        leaderBoards.push_back(lb);  // Thêm vào vector

        std::ostringstream oss;
        oss << "Source\\Data\\LeaderBoard\\leaderboard_" << i << ".dat";
        std::string filename = oss.str();

        std::ifstream testFile(filename, std::ios::binary);
        if (testFile.good()) {
            leaderBoards[i].loadFromFile(filename);  // Nếu file tồn tại, load từ file
            std::cout << "Loaded: " << filename << "\n";
        }
        else {
            leaderBoards[i].saveToFile(filename);  // Nếu file chưa có, tạo file mới
            std::cout << "Created new: " << filename << "\n";
        }
        testFile.close();
    }
}

// Saves all leaderboards back to their files
void LeaderBoardManager::saveAllLeaderBoards()
{   
    for (int i = 0; i < 10; ++i) {
        std::ostringstream oss;
        oss << "Source\\Data\\LeaderBoard\\leaderboard_" << i << ".dat";
        std::string filename = oss.str();
        leaderBoards[i].saveToFile(filename);
    }
}

// Returns reference to leaderboard by index
LeaderBoard& LeaderBoardManager::getLeaderBoard(int index)
{
    return leaderBoards[index];
}
