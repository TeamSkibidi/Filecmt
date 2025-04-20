#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "../../Header/Logic/Init.h"
#include "../../Header/State Game/GameState.h"

#include <string>

using namespace std;
class NewGame {
private:
	sf::RenderWindow* window;
	Init init;
	GAMESTATE gameState;
	string curWindow;
	string preWindow;

	sf::Texture texture[6];
	sf::Sprite sprite[6];
	sf::Text text[3];
	sf::Font font;


	bool isHovering[4];
	float hoverTimer[4];
	const float hoverScaleDuration = 0.15f;

	// Loads the font used in the NewGame screen
	void initFont();

	// Initializes all image textures and sprites
	void initAllImage();

	// Initializes all displayed text elements
	void initAllText();

	// Handles key presses or mouse clicks on the NewGame screen
	void pressdGame(sf::Event event);

public:

	// Constructor that sets up the NewGame screen with references to window and game mode
	NewGame(sf::RenderWindow* window, const string& cur, const string& pre);

	// Updates hover animations and effects based on mouse position and time
	void updateHover(sf::Vector2f mousePos, float deltaTime);

	// Processes events like mouse movement and button clicks
	void updateEvent(sf::Event event);

	// Draws the NewGame screen elements to the window
	void render();

	// Returns the current game mode/window name
	const string& getCurModeGame() const {
		return curWindow;
	}

	// Returns the previous game mode/window name
	const string& getPreModeGame() const {
		return preWindow;
	}

};
