#pragma once


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Menu.h"
#include "../../Header/State Game/Game_Functions.h"
#include "../../Header/State Game/GameState.h"

#include "../../Header/Logic/Movement.h"
#include "../../Header/Logic/Random_pos.h"
#include "../../Header/Logic/Ultilities.h"
#include "../../Header/Logic/StateManagement.h"
#include "../../Header/Logic/Init.h"

#include "../../Header/Data-Logic/MYSTACK.h"

class DashBoard;
class GridGame;


class UIGame {
private:
	sf::RenderWindow* window;
	DashBoard* dashboard;
	GridGame* grid;

	
	GAMESTATE gameState;
	FunctionGame buttonFunction;
	string gameFunction;
	Init init;

	sf::Font font;	
	sf::Clock clock;
	sf::Clock timeGame;
	sf::Text timeText;
	sf::Text timeText2;


	sf::Texture texture[6];
	sf::Sprite sprite[6];
	sf::Text text[3];
	int pos;

	float timeLimitSeconds;
	float timeLimitMinutes;
	double starting = 0.0001;

	int** BoardGame;
	int sizeBoard;

	string curWindow;
	string preWindow;
	string gameMode;
	string WinLose;

	int Score;
	int HighScore;
	sf::Text textScore;
	sf::Text textHighScore;

	MYSTACK Undo;
	MYSTACK Redo;

	// Loads the font used in the game UI
	void initFont();

	// Initializes all game-related text elements
	void initAllText();

	// Loads all images (textures and sprites)
	void initAllPng();

	// Initializes the dashboard (e.g. buttons, labels)
	void initDashBoard();

	// Initializes the game grid (the game board)
	void initGrid();

	// Saves the current game state
	void SaveGame();

	// Undoes the last move
	void undoGame();

	// Redoes the previously undone move
	void redoGame();

	// Checks the game state (win/lose)
	void checkGame();

	// Displays or logs the current FPS
	void checkFPS();

	// Handles player input inside the game
	void pressdGame(sf::Event event);

	// Handles actions from dashboard buttons
	void dashboardButton();

	// Manages game time updates and display
	void TimeGame();

	// Polls and processes window events
	void pollEvents(sf::Event event);

	// Sets the position of score-related UI
	void setPostitionScore();

	// Displays the score and high score
	void printScore();

public:
	// Constructor that initializes the game UI and logic
	UIGame(sf::RenderWindow* window, const string& cur, const string& pre, const int sizeGame, int**& boardGame, const string modeGame, const int& score, const int& highScore);

	// Destructor to clean up dynamic memory/resources
	~UIGame();

	// Handles all game-related input events
	void updateEvent(sf::Event event);

	// Renders the entire game UI and game board
	void render();

	// Manages game logic based on the current mode
	void gameManager(string gameMode);

	// Returns the current window/screen name
	const string& getCurModeGame() const {
		return curWindow;
	}

	// Returns the previous window/screen name
	const string& getPreModeGame() const {
		return preWindow;
	}

	// Returns the Undo stack
	const MYSTACK& getUndoStack() const {
		return Undo;
	}

	// Returns the Redo stack
	const MYSTACK& getRedoStack() const {
		return Redo;
	}

	// Returns the current game result (Win/Lose)
	const string& getGameMode() const {
		return WinLose;
	}

	// Returns the current game board
	int**& getBoardGame() {
		return BoardGame;
	}

	// Returns the current score
	const int& getScore() {
		return Score;
	}

	// Sets the game function (used for internal logic/routing)
	void setGameFunction(string gameFunction) {
		this->gameFunction = gameFunction;
	}
};
