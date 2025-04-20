#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "../../Header/State Game/GameState.h"

#include "../../Header/Data-Logic/LeaderBoardManager.h"
#include "../../Header/Data-Logic/GameStateSystem.h"
#include "../../Header/Data-Logic/HighScoreSystem.h"
#include "../../Header/Data-Logic/MYSTACK.h"


#include "../../Header/Graphic/Audio.h"
#include "../../Header/Graphic/Login.h"
#include "../../Header/Graphic/Menu.h"
#include "../../Header/Graphic/Newgame.h"
#include "../../Header/Graphic/Classic.h"
#include "../../Header/Graphic/UIGame.h"
#include "../../Header/Graphic/Setting.h"
#include "../../Header/Graphic/Rank.h"
#include "../../Header/Graphic/Howtoplay.h"

#include "../../Header/Logic/ColorGame.h"
#include "../../Header/Logic/StateManagement.h"

using namespace std;

class Game
{
private:
	// SFML and audio components
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::Event event;
	Audio* audio;

	// Data-logic managers
	LeaderBoardManager* leaderBoardManager;
	GameStateSystem* gameStateSystem;
	HighScoreSystem* highScoreSystem;

	// Window mode and user/game state
	string curWindow;
	string preWindow;
	string gameMode;
	string UserName;

	// Board and score data
	int** BoardGame;
	int sizeBoard;
	int sizeGame;
	int score;
	int HighScore;

	// Undo/Redo stacks
	MYSTACK undoStack;
	MYSTACK redoStack;

	// UI state pointers
	Login* login;
	Menu* menu;
	NewGame* newgame;
	Classic* classic;
	UIGame* uiGame;
	HowToPlay* howToPlay;
	Rank* rank;
	Setting* setting;

	// General game state and timing
	GAMESTATE gameState;
	sf::Clock clock;
	
	//Game object
	
	// Initializes the main SFML render window
	void initWindow();
	// Initializes current and previous window mode strings
	void initModeWindow();
	// Resets game state and boards to initial values
	void resetGame();
	// Polls and processes SFML window events
	void pollEvents();
	// Processes logic based on current window mode
	void processModeWindow();
	// Deletes resources tied to the previous window
	void deletePreWindow();
	// Sets previous and current window identifiers
	void setPreAndCur();
	// Loads game, user, and state data from files
	void loadFromFile();
	// Checks for win or lose conditions and updates state
	void checkWinLose();
	// Updates leaderboard and score file after game ends
	void setScoreBoard();

public:
	//Constructors and Destructor
	Game();
	~Game();
	
	//Functions
	// Returns true if window is open and game should keep running
	const bool running() const;
	
	// Updates game logic and subsystems each frame
	void update();
	// Renders current frame to the window
	void render();
	
	
	// Setters for window and game state parameters
	void setCurModeGame(const string& s) {
		this->curWindow = s;
	}
	void setPreModeGame(const string& s) {
		this->preWindow = s;
	}
	void setUndoStack(const MYSTACK& stackGame) {
		undoStack = stackGame;
	}
	void setRedoStack(const MYSTACK& stackGame) {
		redoStack = stackGame;
	}
	void setSizeBoard(const int& sizeGame) {
		this->sizeBoard = sizeGame;
	}
	void setBoardGame(int**& boardGame) {
		this->BoardGame = boardGame;
	}

	void setUserName(const string& userName) {
		this->UserName = userName;
	}

	void setScore(const int& Score) {
		this->score = Score;
	}

	void setHighScore(const int& highScore) {
		this->HighScore = highScore;
	}
};


