#pragma 

// Data structure to hold a game board snapshot and associated score
struct DataBoardGame {
    int** boardGame;   // 2D array representing the board state
    int score;         // Score at this board state
    int size;          // Dimension of the board

    // Deep-copy constructor: clones srcBoard into internal storage, sets size and score
    DataBoardGame(int** srcBoard, int size, int _score = 0) : score(_score), size(size) {
        boardGame = new int* [size];
        for (int i = 0; i < size; ++i) {
            boardGame[i] = new int[size];
            for (int j = 0; j < size; ++j) {
                boardGame[i][j] = (srcBoard && srcBoard[i]) ? srcBoard[i][j] : 0;
            }
        }
    }

    // Destructor: free allocated board memory
    ~DataBoardGame() {
        deleteBoard(size); 
    }

    // Helper: delete dynamic 2D array of given dimension
    void deleteBoard(int sz) {
        for (int i = 0; i < sz; ++i) {
            delete[] boardGame[i];
        }
        delete[] boardGame;
        boardGame = nullptr;
    }
};

// Node for linked list stack, holding a DataBoardGame and next pointer
class Node {
public:
    DataBoardGame data;  // Stored board snapshot and score
    Node* pNext;         // Pointer to next node in stack

    // Initialize node with board data and null next pointer
    Node(int** BoardGame, int Score, int SizeBoard)
        : data(BoardGame, SizeBoard, Score), pNext(nullptr) {
    }
};

// Stack implementation for game board states
class MYSTACK {
private:
    Node* topNode;   // Pointer to top of stack
    int count;       // Number of elements in stack
    int sizeBoard;   // Board dimension for all stored states

public:
    // Constructor: set up empty stack for boards of given size
    MYSTACK(int SizeBoard) : topNode(nullptr), count(0), sizeBoard(SizeBoard) {}

    // Destructor: pop all elements to free memory
    ~MYSTACK() {
        while (!isEmpty()) {
            pop();
        }
    }

    // Push a new board state and score onto the stack
    void push(int** BoardGame, int Score) {
        Node* newNode = new Node(BoardGame, Score, sizeBoard);
        newNode->pNext = topNode;
        topNode = newNode;
        count++;
    }

    // Pop the top element, freeing its memory
    void pop() {
        if (isEmpty()) return;

        Node* temp = topNode;
        topNode = topNode->pNext;
        delete temp;
        count--;
    }

    // Get pointer to top board matrix; nullptr if empty
    int** topBoard() {
        if (isEmpty()) return nullptr;
        return topNode->data.boardGame;
    }

    // Get score of top element; 0 if empty
    int topScore() {
        if (isEmpty()) return 0;
        return topNode->data.score;
    }

    // Check whether the stack is empty
    bool isEmpty() {
        return topNode == nullptr;
    }

    // Return number of elements in the stack
    int size() {
        return count;
    }
};

