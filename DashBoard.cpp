#include "../../Header/Graphic/DashBoard.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;


// Loads the LilitaOne font from file for dashboard text rendering
void DashBoard::initFont() {
	font.loadFromFile("Text\\LilitaOne-Regular.ttf");
}


// Include image
void DashBoard::initPng(int index, const string& path, float x, float y, float sizeX, float sizeY, sf::Color color)
{

	if (!this->textures[index].loadFromFile(path)) {
		cout << "Error loading file png " << path << endl;
		return;
	}
	this->newSprite[index].setTexture(this->textures[index]);
	this->newSprite[index].setScale(sizeX, sizeY);
	this->newSprite[index].setPosition(x, y);
	this->newSprite[index].setColor(color);
}

// Initialize all rectangle displayed


// Initialize all image displayed
void DashBoard::initAllimage()
{
	this->initPng(0, "Image\\UIGame-image\\Undo.png", 510, 230, 1.f, 1.f, sf::Color::White);
	this->initPng(1, "Image\\UIGame-image\\Redo.png", 610, 230, 1.f, 1.f, sf::Color::White);
	this->initPng(2, "Image\\UIGame-image\\Refresh.png", 180, 230, 1.f, 1.f, sf::Color::White);
	this->initPng(3, "Image\\UIGame-image\\Home.png", 80, 230, 1.f, 1.f, sf::Color::White);
	this->initPng(5, "Image\\UIGame-image\\High_Score.png", 490, 30, 1.f, 1.f, sf::Color(187, 173, 160));
	this->initPng(4, "Image\\UIGame-image\\Back.png", 10, 10, 1.f, 1.f, sf::Color::White);
	this->initPng(6, "Image\\UIGame-image\\Now_Score.png", 290, 30, 0.8f, 0.8f, sf::Color(187, 173, 160));
	this->initPng(7, "Image\\UIGame-image\\Logo.png", 75, 35, 1.f, 1.f, sf::Color::White);


}

// Initialize all text displayed
void DashBoard::initAllText()
{
	init.initText(newText[0], font, "SCORE", 35, 320, 45, sf::Color::White);
	init.initText(newText[1], font, "BEST SCORE", 35, 500, 50, sf::Color::White);
}

// Include text, rectangle and image 
DashBoard::DashBoard(sf::RenderWindow* window, const string& GameMode)
	: window(window), gameMode(GameMode)
{
	this->initFont();
	this->initAllimage();
	this->initAllText();
}

// Procces mouse button press
void DashBoard::pressdFuncion(sf::Event event){
	gameFunction = "";
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2f mouPos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
		std::cout << "b";
		for (int i = 0; i < 5; i++) {
			sf::FloatRect bounds = newSprite[i].getGlobalBounds();
			if (bounds.contains(mouPos)) {
				switch (i) {
				case 0:
					gameFunction = buttonFunction.UNDO;	
					break;
				case 1:
					gameFunction = buttonFunction.REDO;
					break;
				case 2:
					gameFunction = buttonFunction.REFRESH;
					break;
				case 3:
					gameFunction = buttonFunction.HOME;
					break;
				case 4:
					gameFunction = buttonFunction.BACK;
					break;
				}
			}
		}
	}
}

// Render images and rectangle and text for dash board
void DashBoard::render()
{
	if (!this->window) {
		std::cerr << "Error: `window` is null in DashBoard::render()!" << std::endl;
		return;
	}

	
	for (int i = 7; i >= 2; i--) {
		this->window->draw(this->newSprite[i]);
	}
	if (gameMode != gameState.STANDAR) {
		this->window->draw(this->newSprite[0]);
		this->window->draw(this->newSprite[1]);
	}
	window->draw(newText[0]);
	window->draw(newText[1]);

}
