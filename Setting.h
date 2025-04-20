#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "../../Header/Logic/Init.h"
#include "../../Header/State Game/GameState.h"

#include "Audio.h"

#include <string>

using namespace std;
class Setting {
private:
	sf::RenderWindow* window;
	Audio* audio;
	Init init;
	GAMESTATE gameState;

	// Strings used to switch between different game windows/screens
	string curWindow;
	string preWindow;

	// Array of textures and sprites for the setting screen
	sf::Texture texture[10];
	sf::Sprite sprite[10];

	// Initializes all image textures and sprites
	void initAllImage();

	// Handles mouse click events on the setting screen
	void handleClick(sf::Event event);

public:
	// Constructor to set up the setting screen with references to the window and audio system
	Setting(sf::RenderWindow* window, Audio* audio, const string& cur, const string& pre);

	// Handles and updates input events such as clicks or key presses
	void updateEvent(sf::Event event);

	// Renders the setting screen to the window
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
