#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "UIGame.h"
#include "DashBoard.h"

#include "../../Header/Logic/ColorGame.h"
#include "../../Header/State Game/GameState.h"
#include "../../Header/Logic/Init.h"

// Grid game renderer and handler for drawing the game board
class GridGame {
private:

    sf::RenderWindow* window;   //  Pointer to the SFML render window
    sf::RectangleShape shape;    // Shape used for each grid cell
    sf::Font font;               // Font for rendering text on cells

    int SizeBoard;               // Dimension of the game board
    float sizeDrawing;           // Pixel size for drawing each cell
    float sizeTextDrawing;       // Font size for cell text
    string gameMode;             // Identifier for current game mode
    Init init;                   // Initialization helper
    GAMESTATE gameState;         // Current game state

    // Calculate cell and text sizes based on board dimension
    void setSizeDrawing();

    // Load font resource from file
    void initFont();


public:

    // Constructor: set up window pointer and board size
    GridGame(sf::RenderWindow* window, const int sizeBoard);

    // Draw the game grid and cell values from BoardGame
    void RenderGridGame(int** BoardGame);

};
