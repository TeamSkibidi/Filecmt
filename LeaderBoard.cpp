#include "../../Header/Data-Logic/LeaderBoard.h"


// Counts number of nodes in the player BST
int LeaderBoard::countPlayer(PlayerNode* root) {
    if (root == NULL) {
        return 0;
    }

    return 1 + countPlayer(root->left) + countPlayer(root->right);
}

// Finds the node with minimum score in BST (leftmost)
PlayerNode* LeaderBoard::findMin(PlayerNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Inserts player into BST; maintains max size by deleting lowest score
PlayerNode* LeaderBoard::insertPlayer(PlayerNode* root, string name, int score) {
    if (root == NULL) {
        return new PlayerNode(name, score);
    }

    if (score < root->score) {
        root->left = insertPlayer(root->left, name, score);
    }
    else if (score > root->score) {
        root->right = insertPlayer(root->right, name, score);
    }

    int countPlayers = countPlayer(root);

    if (countPlayers > MAX_PLAYER) {
        root = deletePlayer(root, findMin(root)->score);
    }

    return root;
}

// Deletes a node by score from BST
PlayerNode* LeaderBoard::deletePlayer(PlayerNode* root, int score) {
    if (root == NULL) {
        return NULL;
    }

    if (score < root->score) {
        root->left = deletePlayer(root->left, score);
    }
    else if (score > root->score) {
        root->right = deletePlayer(root->right, score);
    }
    else {
        

        //TH2: Have one child
        if (root->left == NULL) {
            PlayerNode* temp = root->right;
            delete root;
            return temp;
        }
        if (root->right == NULL) {
            PlayerNode* temp = root->left;
            delete root;
            return temp;
        }
        //TH3: Have 2 leaves
        
        PlayerNode* temp = findMin(root->right);
        root->name = temp->name;
        root->score = temp->score;
        root->right = deletePlayer(root->right, temp->score); //Xóa node lớn nhất bên trái
        
    }

    return root;
}

// Performs reverse in-order traversal to collect top scores
void LeaderBoard::getTopPlayer(PlayerNode* node, vector<PlayerNode*> &list, int limit) {
    if (node == NULL || list.size() >= limit) {
        return;
    }

    getTopPlayer(node->right, list, limit);

    if (list.size() < limit) {
        list.push_back(node);
    }

    getTopPlayer(node->left, list, limit);
}

// Searches BST for a player node by name
//Hàm tìm kiếm người chơi theo tên (nhằm mục đích nếu tên có trong danh sách thì sẽ xóa tên rồi mới chèn tên mới vào)
PlayerNode* LeaderBoard::searchPlayer(PlayerNode* root, string name) {
    if (root == NULL || root->name == name) {
        return root;
    }

    PlayerNode* searchLeft = searchPlayer(root->left, name);
    if (searchLeft != NULL) {
        return searchLeft;
    }
    return searchPlayer(root->right, name);
}

// Saves leaderboard to binary file (preorder serialization)
void LeaderBoard::saveToFile(ofstream& file, PlayerNode* root) {
    if (root == NULL) {
        return;
    }

    //Ghi dộ dài của tên vao
    size_t sizeName = root->name.size();
    file.write((char*)&sizeName, sizeof(sizeName));
    //Ghi tên vào
    file.write(root->name.c_str(), sizeName);   //Số byte ghi được bằng chính độ dài chuỗi

    //Ghi score vào 
    file.write((char*)&root->score, sizeof(root->score));


    saveToFile(file, root->left);
    saveToFile(file, root->right);
}

// Loads leaderboard from binary file into BST
PlayerNode* LeaderBoard::loadFromFile(ifstream& file) {
    if (!file.good()) return NULL;

    size_t sizeName;
    if (!file.read((char*)&sizeName, sizeof(sizeName))) return NULL;

    string name(sizeName, ' ');
    if (!file.read(&name[0], sizeName)) return NULL;

    int score;
    if (!file.read((char*)&score, sizeof(score))) return NULL;

    PlayerNode* node = new PlayerNode(name, score);
    node->left = loadFromFile(file);
    node->right = loadFromFile(file);
    return node;
}

// Constructor: initializes empty leaderboard
LeaderBoard::LeaderBoard() : root(NULL) {};

// Updates existing player's score or inserts new player
void LeaderBoard::updateScoreOrAdd(string name, int newScore) {
    PlayerNode* player = searchPlayer(root, name);
    if (player != NULL) {
        if (newScore > player->score) {
            root = deletePlayer(root, player->score);
            root = insertPlayer(root, name, newScore);
        }
    }
    else {
        root = insertPlayer(root, name, newScore);
    }
}

// Saves entire leaderboard to file
void LeaderBoard::saveToFile(const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cout << "Failed to open file for saving!" << endl;
        return;
    }
    saveToFile(file, root);
    file.close();
}
// Loads leaderboard from file
void LeaderBoard::loadFromFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
       cout << "Failed to open file for loading!" << endl;
       return;
    }
    root = loadFromFile(file);
    file.close();
}

// Retrieves top 'limit' players into list
void LeaderBoard::getTopplayer(vector<PlayerNode*>& list, int limit)
{
    list.clear();
    getTopPlayer(root, list, limit);
}


