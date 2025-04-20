#include <iostream>
#include "Header/Game.h"

int main()
{
	// Random 
	std::srand(static_cast<unsigned>(time(nullptr)));

	//Initilize game object
	Game game;

	//Game loop
	while (game.running()) {

		game.update();

		game.render();
	}
}
