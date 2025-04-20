#include "../../Header/Graphic/GridGame.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "../../Header/Logic/ColorGame.h"

using namespace std;

// Sets drawing sizes (tile and text) based on the current board size
void GridGame::setSizeDrawing()
{
	if (SizeBoard == 3) {
		sizeTextDrawing = 60;
		sizeDrawing = 190;
	}
	else if (SizeBoard == 4) {
		sizeTextDrawing = 55;
		sizeDrawing = 140;
	}
	else if (SizeBoard == 5) {
		sizeTextDrawing = 50;
		sizeDrawing = 110;
	}
	else if (SizeBoard == 6) {
		sizeTextDrawing = 40;
		sizeDrawing = 90;
	}
	else if (SizeBoard == 7) {
		sizeTextDrawing = 35;
		sizeDrawing = 75.7;
	}
	else if (SizeBoard == 8) {
		sizeTextDrawing = 30;
		sizeDrawing = 65;
	}
	else if (SizeBoard == 9) {
		sizeTextDrawing = 25;
		sizeDrawing = 56.8;
	}
	else if (SizeBoard == 10) {
		sizeTextDrawing = 20;
		sizeDrawing = 50;
	}

// Loads the Roboto Bold font from file for grid text rendering
void GridGame::initFont()
{
	if (!font.loadFromFile("Text\\Roboto-Bold.ttf")) {
		cout << "Error loading font!" << endl;
	}
}


// Renders the game grid: draws each tile and its number if non-zero
void GridGame::RenderGridGame(int** BoardGame)
{
	for (int i = 0; i < SizeBoard; i++) {
		for (int j = 0; j < SizeBoard; j++) {
			shape.setSize(sf::Vector2f(static_cast<float>(sizeDrawing), static_cast<float>(sizeDrawing)));
			shape.setPosition(static_cast<float>(j * (sizeDrawing + 10) + 90), static_cast<float>(i * (sizeDrawing + 10) + 335));
			shape.setFillColor(getColor(BoardGame[i][j]));
			shape.setOutlineThickness(10);
			shape.setOutlineColor(sf::Color(187, 173, 160));

			window->draw(shape);

			if (BoardGame[i][j] != 0) {
				sf::FloatRect textRect;
				sf::Text text;
				text.setFont(font);
				text.setString(to_string(BoardGame[i][j]));
				text.setCharacterSize(sizeTextDrawing);
				text.setFillColor(sf::Color(187, 173, 160));

				sf::FloatRect textBounds = text.getGlobalBounds();
				text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
				text.setPosition(static_cast<float>(j * (sizeDrawing + 10) + 125), static_cast<float>(i * (sizeDrawing + 10) + 355));
				init.centerTextRec(text, shape);
				window->draw(text);
			}
		}
	}
}


// Constructor sets up window reference and board size, then initializes font and drawing sizes
GridGame::GridGame(sf::RenderWindow* window, const int sizeBoard)
	: window(window), SizeBoard(sizeBoard)
{
	initFont();
	setSizeDrawing();
}


