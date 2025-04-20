#include "../../Header/Graphic/Newgame.h"



// Loads the font from file
void NewGame::initFont()
{
	font.loadFromFile("Text\\Roboto-Bold.ttf");
}

// Initializes all sprite textures and positions
void NewGame::initAllImage()
{
	init.initPng(texture[0], sprite[1], "Image\\NewGame_Image\\Classic_image.png", 400.f, 380.f, 1.f, 1.f, sf::Color::White);
	init.initPng(texture[1], sprite[2], "Image\\NewGame_Image\\Standal_image.png", 400.f, 580.f, 1.f, 1.f, sf::Color::White);
	init.initPng(texture[2], sprite[3], "Image\\NewGame_Image\\TimeTrial_image.png", 400.f, 780.f, 1.f, 1.f, sf::Color::White);
	init.initPng(texture[3], sprite[4], "Image\\BackGround\\BackGround.png", 1.0, 1.0, 1.0, 1.0, sf::Color::White);
	init.initPng(texture[4], sprite[0], "Image\\NewGame_Image\\Back.png", 40.0, 40.0, 1.0, 1.0, sf::Color::White);
	init.initPng(texture[5], sprite[5], "Image\\NewGame_Image\\Logo-GameMode.png", 200.0, 5.f, 1.f, 1.f, sf::Color::White);
	for (int i = 0; i < 4; i++) {
		sprite[i].setOrigin(sprite[i].getLocalBounds().width / 2, sprite[i].getLocalBounds().height / 2);
	}


}

// Creates and positions text elements
void NewGame::initAllText()
{
	init.initText(text[0], font, "Classic", 60, 100.0, 200.0, sf::Color(110, 62, 30));
	init.initText(text[1], font, "Standar", 60, 100.0, 240.0, sf::Color(110, 62, 30));
	init.initText(text[2], font, "Time Trial", 60, 100.0, 280.0, sf::Color(110, 62, 30));
	init.centerTextInSprite(text[0], sprite[1]);
	init.centerTextInSprite(text[1], sprite[2]);
	init.centerTextInSprite(text[2], sprite[3]);
}

// Handles mouse press events to change game state
void NewGame::pressdGame(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2f mouPos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
		for (int i = 0; i < 4; i++) {
			sf::FloatRect bounds = sprite[i].getGlobalBounds();
			if (bounds.contains(mouPos)) {
				switch (i) {
				case 0:
					preWindow = curWindow;
					curWindow = gameState.MENU;
					break;
				case 1:
					preWindow = curWindow;
					curWindow = gameState.CLASSIC;
					break;
				case 2:
					preWindow = curWindow;
					curWindow = gameState.STANDAR;
					break;
				case 3:
					preWindow = curWindow;
					curWindow = gameState.TIMETRIAL;
					break;
				}
			}
		}
	}
}

// Updates sprite scaling on hover
void NewGame::updateHover(sf::Vector2f mousePos, float deltaTime)
{
	const float maxScale = 1.1f;
	const float minScale = 1.f;
	const float scaleSpeed = 5.0f;

	for (int i = 0; i < 4; i++) {
		isHovering[i] = sprite[i].getGlobalBounds().contains(mousePos);
		float currentScale = sprite[i].getScale().x;
		float targetScale = isHovering[i] ? maxScale : minScale;
		float newScale = currentScale + (targetScale - currentScale) * deltaTime * scaleSpeed;
		if (targetScale == maxScale && newScale > maxScale) newScale = maxScale;
		if (targetScale == minScale && newScale < minScale) newScale = minScale;
		sprite[i].setScale(newScale, newScale);
	}
}

// Constructor: initializes member variables and components
NewGame::NewGame(sf::RenderWindow* window, const string& cur, const string& pre)
	: window(window), curWindow(cur), preWindow(pre)
{

	for (int i = 0; i < 4; i++) {
		isHovering[i] = false;
		hoverTimer[i] = 0.0f;
	}
	initFont();
	initAllImage();
	initAllText();
}

// Processes SFML events
void NewGame::updateEvent(sf::Event event)
{
	pressdGame(event);
}

// Renders background, sprites, and text to the window
void NewGame::render()
{
	window->draw(sprite[4]);
	window->draw(sprite[5]);
	for (int i = 0; i < 4; i++) {
		window->draw(sprite[i]);
	}
	for (int i = 0; i < 3; i++) {
		window->draw(text[i]);
	}
}
