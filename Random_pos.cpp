#include "../../Header/Logic/Random_pos.h"
using namespace std;

// Random position
void random_pos(int** boardgame,int sizeBoard) {
	// save the empty cells 
	vector<int> empty_cells;
	for (int i = 0; i < sizeBoard; i++) {
		for (int j = 0; j < sizeBoard; j++) {
			if (boardgame[i][j] == 0) {
				empty_cells.push_back(i);
				empty_cells.push_back(j);
			}
		}
	}
	// if has not empty cells, return 
	int empty_count = (empty_cells.size() / 2);
	if (empty_count == 0) return;
	// get number of cells want to random
	int num_cell = (empty_count > 1 && rand() % 2 == 0) ? 2 : 1;

	for (int i = 0; i < num_cell; i++) {
		int idx = rand() % empty_count;
		int x = empty_cells[idx * 2];
		int y = empty_cells[idx * 2 + 1];
		boardgame[x][y] = (rand() % 10 < 3) ? 512 : 2;
		// swap position x, y just been used for 2 last element 
		int lastIndex = empty_cells.size() - 2;
		empty_cells[idx * 2] = empty_cells[lastIndex];
		empty_cells[idx * 2 + 1] = empty_cells[lastIndex + 1];
		// remove 2 last element after swap
		empty_cells.pop_back();
		empty_cells.pop_back();
		empty_count--; // reduce the number of empty cells by 1
	}


}
