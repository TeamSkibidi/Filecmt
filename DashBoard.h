#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "../../Header/State Game/Game_Functions.h"
#include "../../Header/State Game/GameState.h"

#include "../../Header/Logic/StateManagement.h"
#include "../../Header/Logic/Init.h"


using namespace std;
// Dashboard manager for game UI, input handling, and rendering
class DashBoard {
private:
    sf::RenderWindow* window;     // Pointer to the SFML render window
    sf::Text newText[2];          // Array of text elements for UI
    sf::Font font;                // Font resource for text rendering
    int** BoardGame;              // Pointer to the game board matrix data
    Init init;                    // Initialization helper

    sf::Sprite newSprite[8];      // Sprites for UI buttons and icons
    sf::Texture textures[8];      // Textures associated with sprites
    FunctionGame buttonFunction;  // Enum/handler for current button function
    GAMESTATE gameState;          // Current game state
    string gameFunction;          // Identifier for selected game function
    string gameMode;              // Identifier for current game mode

    // Load font resource from file
    void initFont();

    // Setup text objects (position, string, style)
    void initAllText();

    // Load a single image into texture and sprite, set position and scale
    void initPng(int index, const string& path, float x, float y, float sizeX, float sizeY, sf::Color color);

    // Initialize all UI images (buttons/icons)
    void initAllimage();

public:
    // Constructor: configure window pointer and game mode
    DashBoard(sf::RenderWindow* window, const string& GameMode);

    // Handle input events to update selected function or state
    void pressdFuncion(sf::Event event);

    // Render dashboard UI elements onto the window
    void render();

    // Get the currently selected game function
    const string getGameFunction() const {
        return gameFunction;
    }
};
