
#include "../../Header/Logic/Ultilities.h"

using namespace std;


// Check win
bool checkwin(int** BoardGame, int sizeBoard) {
	for (int i = 0; i < sizeBoard; i++) {
		for (int j = 0; j < sizeBoard; j++) {
			if (BoardGame[i][j] >= 2048) return true; // Win
		}
	}
	return false; // Lose
}

// Check lost
bool checklose(int** BoardGame, int sizeBoard) {
	// TH1 kiểm tra xem còn ô trống nào không
	for (int i = 0; i < sizeBoard; i++) {
		for (int j = 0; j < sizeBoard; j++) {
			if (BoardGame[i][j] == 0) return false; // Not Lose
		}
	}
	
	// TH2 nếu không còn ô trống thì kiểm tra các phần tử kề nhau có gộp lại được nữa không
	for (int i = 0; i < sizeBoard; i++) {
		for (int j = 0; j < sizeBoard; j++) {
			// Kiểm tra phần tử bên phải và dưới của ô ij
			if (j + 1 < sizeBoard && BoardGame[i][j] == BoardGame[i][j + 1])
				return false; // Not Lose
			if (i + 1 < sizeBoard && BoardGame[i][j] == BoardGame[i + 1][j])
				return false; // Not Lose
		}
	}
	// TH3 
	return true; // Lose


}


