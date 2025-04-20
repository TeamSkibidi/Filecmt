#pragma once

#include <SFML/Graphics.hpp>
#include "../../Header/Data-Logic//LeaderBoardManager.h"
#include "../../Header/Logic/Init.h"
#include "../../Header/State Game/GameState.h"

#include <string>
class Rank {
private:
    sf::RenderWindow* window;
    LeaderBoardManager* leaderBoardManager;
    sf::Font font;
    sf::Text text;
    

    Init init;
    string curWindow;
    string preWindow;
    GAMESTATE gameStae;

    sf::Texture back;
    sf::Sprite Back;
    sf::Sprite boardSprite, leftSprite, rightSprite, sizeSprite, backSprite;
    sf::Texture boardTexture, leftTexture, rightTexture, sizeTexture, backTexture;

    sf::Text rankText, playerText, scoreText, modeText;
    std::vector<std::string> boardModes;
    vector<sf::Text> rankListText;

    int curBoardIndex;

    // Loads the font used in the Rank screen
    void initFont();

    // Initializes all sprite objects and their textures
    void initAllSprite();

    // Initializes all text elements on the leaderboard screen
    void initAllText();

    // Creates a centered sf::Text object at a given x and y position
    sf::Text createNewTextIsCenterOfText(const string& str, float centerx, float y);

    // Returns the pixel width of the given text string
    float getTextWidth(const std::string& str);

    // Initializes the list of player rankings displayed
    void initRankList();

    // Handles user input and events such as clicks and key presses
    void handleEvent(const sf::Event& event);

public:
    // Constructor that sets up the leaderboard screen with access to the window and leaderboard manager
    Rank(sf::RenderWindow* window, LeaderBoardManager*& lbm, const string& cur, const string& pre);

    // Processes events like mouse movement, button clicks, etc.
    void updateEvent(const sf::Event& event);

    // Renders all visual elements of the Rank screen
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



