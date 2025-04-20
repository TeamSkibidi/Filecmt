#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "../../Header/Logic/Init.h"
#include "../../Header/State Game/GameState.h"

#include <string>

using namespace std;

// Classic game mode handler managing rendering and input in SFML
class Classic {
private:
    sf::RenderWindow* window;         // Pointer to the main render window
    sf::Text text[8];                 // Array of display texts
    sf::Texture texture[14];          // Textures for sprites
    sf::Sprite sprite[14];            // Sprites for visual elements
    sf::Font font;                    // Font for UI text

    string curWindow;                 // Current game mode identifier
    string preWindow;                 // Previous game mode identifier
    int SizeBoard;                    // Dimension of the game board

    bool isHovering[4];               // Hover state for UI buttons
    float hoverTimer[4];              // Timer for hover animation
    const float hoverScaleDuration = 0.15f; // Duration for scale animation on hover

    Init init;                        // Initialization helper
    GAMESTATE gameState;              // Current game state object

    // Load all sprites and textures
    void initAllImage();

    // Load font resource
    void initFont();

    // Initialize all sf::Text objects
    void initAllText();

    // Handle game-specific input events
    void pressdGame(sf::Event event);

public:
    // Constructor: set up window pointer and mode strings
    Classic(sf::RenderWindow* window, const string& cur, const string& pre);

    // Process SFML input event
    void updateEvent(sf::Event event);

    // Update hover animations based on mouse position and delta time
    void updateHover(sf::Vector2f mousePos, float deltaTime);

    // Render all game mode visuals to the window
    void render();

    // Getters for current and previous mode identifiers
    const string& getCurModeGame() const { return curWindow; }
    const string& getPreModeGame() const { return preWindow; }
    const int& getSizeBoard() const { return SizeBoard; }
};
