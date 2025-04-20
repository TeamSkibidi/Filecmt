#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <string>

#include <iostream>
#include "../../Header/State Game/GameState.h"
#include "../../Header/Logic/Init.h"


class Menu
{
private:
    sf::RenderWindow* window;        // Pointer to the main render window
    sf::Font font;                   // Font used for button labels
    sf::Sprite spirite[8];           // Array of sprites for menu graphics
    sf::Texture texture[8];          // Textures corresponding to each sprite

    sf::Text buttonTexts[4];         // Text labels for menu buttons

    Init init;                       // Initialization helper
    GAMESTATE gameState;             // Current game state
    std::string curWindow;           // Identifier for current screen
    std::string preWindow;           // Identifier for previous screen

    bool isHovering[4];              // Flags for hover state per button
    float hoverTimer[4];             // Timers for hover animation durations
    const float hoverScaleDuration = 0.15f;  // Duration for scale animation

    // Load font resources for text rendering
    void initFont();

    // Initialize all SFML Text objects for buttons
    void initAllText();

    // Initialize all sprites and textures for menu visuals
    void initAllImage();

    // Smoothstep function for interpolation (ease-in/out)
    float smoothstep(float t) {
        return t * t * (3.0f - 2.0f * t);
    }

public:
    // Constructor: set up window pointer and screen identifiers
    Menu(sf::RenderWindow* window, const std::string& cur, const std::string& pre);

    // Update hover animations based on mouse position and elapsed time
    void updateHover(sf::Vector2f mousePos, float deltaTime);

    // Handle input events (keyboard, mouse clicks)
    void updateEvent(sf::Event event);

    // Render all menu elements onto the window
    void render();

    // Get current window identifier
    const std::string& getCurModeGame() const { return curWindow; }

    // Get previous window identifier
    const std::string& getPreModeGame() const { return preWindow; }
};
 
