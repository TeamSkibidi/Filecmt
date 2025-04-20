#include "../../Header/Graphic/Classic.h"
#include <iostream>

// Loads the Roboto Bold font from file for text rendering
void Classic::initFont()
{
	font.loadFromFile("Text\\Roboto-Bold.ttf");
}


// Initializes all size option texts (3x3 to 10x10) with proper font, size, position, and color
void Classic::initAllText()
{
	init.initText(text[0], font, "3 x 3", 70, 310.0, 825.f, sf::Color::Black);
	init.initText(text[1], font, "4 x 4", 70, 310.0, 825.f, sf::Color::Black);
	init.initText(text[2], font, "5 x 5", 70, 310.0, 825.f, sf::Color::Black);
	init.initText(text[3], font, "6 x 6", 70, 310.0, 825.f, sf::Color::Black);
	init.initText(text[4], font, "7 x 7", 70, 310.0, 825.f, sf::Color::Black);
	init.initText(text[5], font, "8 x 8", 70, 310.0, 825.f, sf::Color::Black);
	init.initText(text[6], font, "9 x 9", 70, 310.0, 825.f, sf::Color::Black);
	init.initText(text[7], font, "10 x 10", 70, 272.0, 825.f, sf::Color::Black);
}

// Loads and positions all sprites for board sizes, buttons, and UI elements
void Classic::initAllImage()
{
	init.initPng(texture[0], sprite[0], "Image\\Classic_image\\3x3.png", 380.f, 500.f, 1.f, 0.4f, sf::Color(255, 255, 255));
	init.initPng(texture[1], sprite[1], "Image\\Classic_image\\4x4.png", 380.f, 500.f, 0.6f, 0.6f, sf::Color(255, 255, 255));
	init.initPng(texture[2], sprite[2], "Image\\Classic_image\\5x5.png", 380.f, 500.f, 0.6f, 0.6f, sf::Color(255, 255, 255));
	init.initPng(texture[3], sprite[3], "Image\\Classic_image\\6x6.png", 380.f, 500.f, 0.6f, 0.6f, sf::Color(255, 255, 255));
	init.initPng(texture[4], sprite[4], "Image\\Classic_image\\7x7.png", 380.f, 500.f, 0.6f, 0.6f, sf::Color(255, 255, 255));
	init.initPng(texture[5], sprite[5], "Image\\Classic_image\\8x8.png", 380.f, 500.f, 0.6f, 0.6f, sf::Color(255, 255, 255));
	init.initPng(texture[6], sprite[6], "Image\\Classic_image\\9x9.png", 380.f, 500.f, 0.6f, 0.6f, sf::Color(255, 255, 255));
	init.initPng(texture[7], sprite[7], "Image\\Classic_image\\10x10.png", 380.f, 500.f, 0.6f, 0.6f, sf::Color(255, 255, 255));
	init.initPng(texture[8], sprite[8], "Image\\Classic_image\\Button.png", 385.0, 875.f, 1.f, 1.f, sf::Color::White);
	init.initPng(texture[9], sprite[9], "Image\\Classic_image\\Right.png", 720.f, 470.f, 1.f, 1.f, sf::Color(255, 255, 255));
	init.initPng(texture[10], sprite[10], "Image\\Classic_image\\Left.png", 40.f, 470.f, 1.f, 1.f, sf::Color(255, 255, 255));
	init.initPng(texture[11], sprite[11], "Image\\Classic_image\\Back.png", 50.0, 50.f, 1.3f, 1.2f, sf::Color::White);
	init.initPng(texture[12], sprite[12], "Image\\Classic_image\\Logo-Size.png", 220.0, 1.f, 1.f, 1.f, sf::Color::White);
	init.initPng(texture[13], sprite[13], "Image\\BackGround\\background.png", 1.f, 1.f, 0.8f, 0.8f, sf::Color(255, 255, 255));
	for (int i = 0; i < 12; i++) {
		sprite[i].setOrigin(sprite[i].getLocalBounds().width / 2, sprite[i].getLocalBounds().height / 2);
	}

}

// Processes mouse click events to adjust board size or navigate to new game/UI screens
void Classic::pressdGame(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2f mouPos = this->window->mapPixelToCoords(sf::Mouse::getPosition (*this->window));
		for (int i = 7; i < 12; i++) {
			sf::FloatRect bounds = sprite[i].getGlobalBounds();
			if (bounds.contains(mouPos)) {
				switch (i) {
				case 9:
					if (SizeBoard < 10) SizeBoard++;
					break;
				case 10:
					if (SizeBoard > 3) SizeBoard--;
					break;	
				case 11:
					preWindow = curWindow;
					curWindow = gameState.NEWGAME;
					break;
				case 7:
					preWindow = curWindow;
					curWindow = gameState.UIGAME;
					break;
				}
				
			}
		}
	}
}



// Updates hover scaling effect on buttons and tiles based on mouse position and delta time
void Classic::updateHover(sf::Vector2f mousePos, float deltaTime)
{
	float maxScale = 0.9f;
	float minScale = 0.8f;
	float scaleSpeed = 5.0f;

	for (int i = 0; i < 8; i++) {
		isHovering[i] = sprite[i].getGlobalBounds().contains(mousePos);
		float currentScale = sprite[i].getScale().x;
		float targetScale = isHovering[i] ? maxScale : minScale;
		float newScale = currentScale + (targetScale - currentScale) * deltaTime * scaleSpeed;
		if (targetScale == maxScale && newScale > maxScale) newScale = maxScale;
		if (targetScale == minScale && newScale < minScale) newScale = minScale;
		sprite[i].setScale(newScale, newScale);
	}

	maxScale = 1.2f;
	minScale = 1.f;
	scaleSpeed = 5.0f;

	for (int i = 9; i < 12; i++) {
		this->isHovering[i] = sprite[i].getGlobalBounds().contains(mousePos);
		float currentScale = sprite[i].getScale().x;
		float targetScale = this->isHovering[i] ? maxScale : minScale;
		float newScale = currentScale + (targetScale - currentScale) * deltaTime * scaleSpeed;
		if (targetScale == maxScale && newScale > maxScale) newScale = maxScale;
		if (targetScale == minScale && newScale < minScale) newScale = minScale;
		sprite[i].setScale(newScale, newScale);
	}


}

// Constructor sets initial board size based on game mode, resets hover states, and initializes assets
Classic::Classic(sf::RenderWindow* window, const string& cur, const string& pre)
	: curWindow(cur), preWindow(pre)
{

	for (int i = 0; i < 4; i++) {
		isHovering[i] = false;
		hoverTimer[i] = 0.0f;
	}
	SizeBoard = 3;
	if (curWindow == gameState.TIMETRIAL) SizeBoard = 4;
	if (curWindow == gameState.STANDAR) SizeBoard = 4;
	this->window = window;
	initFont();
	initAllImage();
	initAllText();
}

// Handles SFML events by delegating to pressdGame
void Classic::updateEvent(sf::Event event)
{
	pressdGame(event);
}

// Renders background, logo, and either the selected board size sprite/text or default UI elements
void Classic::render()
{
	this->window->draw(sprite[13]);
	this->window->draw(sprite[12]);
	if (curWindow == gameState.CLASSIC) {
		this->window->draw(sprite[SizeBoard - 3]);
		for (int i = 8; i < 13; i++) {
			this->window->draw(sprite[i]);
		}
		this->window->draw(text[SizeBoard - 3]);
	}
	else {
		this->window->draw(sprite[1]);
		this->window->draw(sprite[11]);
		this->window->draw(sprite[8]);
		this->window->draw(text[1]);
	}
}
