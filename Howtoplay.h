#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "../../Header/Logic/Init.h"
#include "../../Header/State Game/GameState.h"


// Screen to display "how to play" instructions and handle its interactions
class HowToPlay {
private:
    sf::RenderWindow* window;    // Pointer to the main SFML window
    sf::Font font;               // Font resource for rendering instruction text
    sf::Text text;               // Text object displaying instructions
    sf::RectangleShape background; // Background shape for the instruction screen
    Init init;                   // Initialization helper for loading resources
    sf::Texture texture[5];      // Array of textures for instruction images
    sf::Sprite sprite[5];        // Array of sprites for instruction visuals

    GAMESTATE gameState;         // Current game state

    // Con trỏ chuyển giữa các file
    string curWindow;            // Identifier for current screen
    string preWindow;            // Identifier for previous screen

    bool isShowing; // check display

    // font, size, position
    void setupText();

    // Load all textures and assign to sprites
    void initAllImage();

    // Handle input events specific to HowToPlay screen
    void handleEvent(sf::Event event);

public:
    // Constructor: set window pointer and initialize screen identifiers
    HowToPlay(sf::RenderWindow* window, const string& cur, const string& pre);

    // Process a single SFML event (e.g., key press, mouse click)
    void updateEvent(sf::Event event);

    // Draw the instruction screen elements
    void render();

    // Getters for current and previous screen names
    const string& getCurModeGame() const {
        return curWindow;
    }
    const string& getPreModeGame() const {
        return preWindow;
    }
};
