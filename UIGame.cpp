#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include "../../Header/Graphic/UIGame.h"
#include "../../Header/Graphic/DashBoard.h"
#include "../../Header/Graphic/GridGame.h"
#include "../../Header/Data-Logic/MYSTACK.h"

//  Function to initialize dashboard
void UIGame::initDashBoard()
{
	dashboard = new DashBoard(window ,gameMode);
}

// Function to initialize Grid Game
void UIGame::initGrid() 
{
	grid = new GridGame(window, sizeBoard);
}

// Function to initialize font
void UIGame::initFont()
{
	if (!font.loadFromFile("Text\\LilitaOne-Regular.ttf")) {
		cout << "Error loading font!" << endl;
	}
}

// Sets up all in-game text elements (time, score, labels)
void UIGame::initAllText()
{
	// Set up time game
	timeText.setFont(font);
	timeText.setCharacterSize(40);
	timeText.setFillColor(sf::Color::Black);
	timeText.setPosition(275, 250);

	timeText2.setFont(font);
	timeText2.setCharacterSize(40);
	timeText2.setFillColor(sf::Color::Black);
	timeText2.setPosition(275, 250);

	// Set Score game
	textScore.setFont(font);
	textScore.setCharacterSize(50);
	textScore.setFillColor(sf::Color(255, 156, 44));
	textScore.setPosition(355, 80);


	// Set High Score game
	textHighScore.setFont(font);
	textHighScore.setCharacterSize(50);
	textHighScore.setFillColor(sf::Color(255, 156, 44));
	textHighScore.setPosition(575, 95);

	init.initText(text[0], font, "YOUR SCORE", 70, 195.f, 550.f, sf::Color::Black);
	init.initText(text[1], font, "PLAY AGAIN ", 40, 347.f, 765.f, sf::Color::Black);
	init.initText(text[2], font, "PLAY AGAIN ", 50, 260.f, 805.f, sf::Color::Black);
}

// Loads win/lose images and play/home buttons
void UIGame::initAllPng()
{
	init.initPng(texture[0], sprite[0], "Image\\WinLose_image\\Win.png", 90.f, 100.f, 1.2f, 1.2f, sf::Color::White);
	init.initPng(texture[1], sprite[1], "Image\\WinLose_image\\Lose.png", 90.f, 100.f, 1.2f, 1.2f, sf::Color::White);
	init.initPng(texture[2], sprite[2], "Image\\WinLose_image\\play_again_win.png", 320.f, 730.f, 1.2f, 1.2f, sf::Color::White);
	init.initPng(texture[3], sprite[3], "Image\\WinLose_image\\home_win.png", 180.f, 730.f, 1.2f, 1.2f, sf::Color::White);
	init.initPng(texture[4], sprite[4], "Image\\WinLose_image\\play_again_lose.png", 217.f, 780.f, 1.2f, 1.2f, sf::Color::White);
	init.initPng(texture[5], sprite[5], "Image\\WinLose_image\\home_win.png", 217.f, 650.f, 1.2f, 1.2f, sf::Color::White);
	init.centerSpriteHorizontally(sprite[0], window);
	init.centerSpriteHorizontally(sprite[1], window);

}

// Constructor and destructor Game UI
UIGame::UIGame(sf::RenderWindow* window, const string& cur, const string& pre, const int sizeGame, int**& boardGame, const string modeGame, const int& score, const int& highScore)
	: window(window), curWindow(cur), preWindow(pre), sizeBoard(sizeGame), gameMode(modeGame), Undo(sizeGame), Redo(sizeGame) , HighScore(highScore) {
	
	// Initialize the font, png and text
	initFont();
	initAllPng();
	initAllText();

	// If game mode is not Resume, create a new game and randomize the board
	if (curWindow != gameState.RESUME) {
		createGame(BoardGame, sizeBoard);
		random_pos(BoardGame, sizeBoard);
		Score = 0;
	}

	/* If game mode is Resume get Board Game from file, update score and high score*/
	else {
		BoardGame = copyBoard(boardGame, sizeBoard);
		Score = score;
	}

	// Initialize the game UI Game
	initDashBoard();
	initGrid();

	// Save game state event (Ex: Win, Lose, Undo, Redo, Home, Refresh, and pause);
	gameFunction = "";
	WinLose = "";
	pos = 0;
	
	// Initialize the game clock for game State Time Trial
	if (gameMode == gameState.TIMETRIAL) {

		// Set time Play game mode time trial
		timeLimitSeconds = 0.0f;
		timeLimitMinutes = 2.0f;
		
	}
}	
 
// Destructor: cleans up dynamically allocated resources
UIGame::~UIGame()
{
	DeleteGame(BoardGame, sizeBoard);

	if (dashboard) {
		delete dashboard;
		dashboard = nullptr;
	}
	if (grid) {
		delete grid;
		grid = nullptr;
	}

}

// Processes win/lose button clicks
void UIGame::pressdGame(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2f mouPos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
		for (int i = 2; i < 6; i++) {
			sf::FloatRect bounds = sprite[i].getGlobalBounds();
			if (bounds.contains(mouPos)) {
				if (WinLose == gameState.WIN) {
					switch (i) {
					case 2:
						gameFunction = buttonFunction.REFRESH;
						break;
					case 3:
						preWindow = curWindow;
						curWindow = gameState.MENU;
						break;
					}
				}
				else if (WinLose == gameState.LOSE) {

					switch (i) {
					case 4:
						gameFunction = buttonFunction.REFRESH;
						break;
					case 5:
						preWindow = curWindow;
						curWindow = gameState.MENU;
						break;
					}
				}
			}
		}
	}
}

// Handles keyboard input for moves and updates board state
void UIGame::pollEvents(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (BoardGame != nullptr)
		{
			bool moved = false;
			switch (event.key.code) {

			case sf::Keyboard::Up:
				SaveGame();
				goup(BoardGame, sizeBoard, Score);
				moved = check_change(BoardGame, sizeBoard, Undo.topBoard());
				moved = check_change(BoardGame, sizeBoard, Undo.topBoard());
				break;

			case sf::Keyboard::Down:
				SaveGame();
				godown(BoardGame, sizeBoard, Score);
				moved = check_change(BoardGame, sizeBoard, Undo.topBoard());
				break;

			case sf::Keyboard::Left:
				SaveGame();
				turnleft(BoardGame, sizeBoard, Score);
				moved = check_change(BoardGame, sizeBoard, Undo.topBoard());
				break;

			case sf::Keyboard::Right:
				SaveGame();
				turnright(BoardGame, sizeBoard, Score);
				moved = check_change(BoardGame, sizeBoard, Undo.topBoard());
				break;

			}
			if (moved) {
				cout << endl;
				for (int i = 0; i < sizeBoard; i++) {
					for (int j = 0; j < sizeBoard; j++) {
						cout << Undo.topBoard()[i][j] << " ";
					}
					cout << endl;
				}
				if (Score > HighScore) {
					HighScore = Score;
				}
				Redo.pop();
				random_pos(BoardGame, sizeBoard);
			}
		}
	}
}

// Handles dashboard button actions (undo, redo, home, refresh)
void UIGame::dashboardButton()
{

	if (gameFunction == buttonFunction.HOME) {

		preWindow = curWindow;
		curWindow = gameState.MENU;
	}
	else if (gameFunction == buttonFunction.UNDO && gameMode != gameState.STANDAR) {
		if (!Undo.isEmpty()) {
			Redo.push(copyBoard(BoardGame, sizeBoard), Score);
			undoGame();
		}
	}
	else if (gameFunction == buttonFunction.REDO && gameMode != gameState.STANDAR) {
		if (!Redo.isEmpty()) {
			Undo.push(copyBoard(BoardGame, sizeBoard), Score);
			redoGame();
		}
	}
	else if (gameFunction == buttonFunction.REFRESH) {
		Redo.pop();
		Undo.pop();
		WinLose = "";
		DeleteGame(BoardGame, sizeBoard);
		createGame(BoardGame, sizeBoard);
		random_pos(BoardGame, sizeBoard);
		Score = 0;

		timeLimitSeconds = 0.0f;
		timeLimitMinutes = 2.0f;

		textScore.setCharacterSize(50);
		textScore.setPosition(355, 80);
	}
	else if (gameFunction == buttonFunction.BACK) {
		preWindow = curWindow;
		curWindow = gameMode;
	}
	gameFunction = "";
}

// Measure game FPS
void UIGame::checkFPS()
{
	// 
	window->setFramerateLimit(60);
	double ending = clock.getElapsedTime().asSeconds();
	double timeFPS = ending - starting;
	string FPS;

	if (timeFPS > 0.0001) {
		FPS = to_string(int(1.0 / timeFPS));
	}

	// Print FPS Current
	window->setTitle("2048 FPS: " + FPS);
	starting = ending;
}
 
// Saves current board state on undo stack, limiting depth
void UIGame::SaveGame()
{
	if (checklose(BoardGame, sizeBoard) || checkwin(BoardGame, sizeBoard)) {
		return;
	}

	if (Undo.size() >= 3) {
		MYSTACK temp(sizeBoard);

		for (int i = 0; i < 2 && !Undo.isEmpty(); i++) {
			temp.push(copyBoard(Undo.topBoard(), sizeBoard), Undo.topScore());
			Undo.pop();
		}

		if (!Undo.isEmpty()) Undo.pop();

		for (int i = 0; i < 2 && !temp.isEmpty(); i++) {
			Undo.push(copyBoard(temp.topBoard(), sizeBoard), temp.topScore());
			temp.pop();
		}
	}

	Undo.push(copyBoard(BoardGame, sizeBoard), Score);
}

// Updates timer text for time trial mode
void UIGame::TimeGame()
{
	if (WinLose != gameState.WIN) {
		float escape = timeGame.getElapsedTime().asSeconds();
		float timePrint = timeLimitSeconds - escape;
		if (timePrint <= 0 && timeLimitMinutes == 0) {
			WinLose = gameState.LOSE;
			return;
		}
		if (timePrint <= 0 && timeLimitMinutes > 0) {
			timeLimitMinutes--;
			timeLimitSeconds = 60.0f;
			timeGame.restart();
		}

		else {
			if (timeLimitMinutes < 10) {
				if (timePrint < 10) {
					ostringstream temp;
					temp << "Time: 0" << static_cast<int>(timeLimitMinutes) << ":0" << static_cast<int>(timePrint) << "s";
					timeText.setString(temp.str());
				}
				else {
					ostringstream temp;
					temp << "Time: 0" << static_cast<int>(timeLimitMinutes) << ":" << static_cast<int>(timePrint) << "s";
					timeText.setString(temp.str());
				}
			}
			else {
				if (timePrint < 10) {
					ostringstream temp;
					temp << "Time: 0" << static_cast<int>(timeLimitMinutes) << ":0" << static_cast<int>(timePrint) << "s";
					timeText.setString(temp.str());
				}
				else {
					ostringstream temp;
					temp << "Time: 0" << static_cast<int>(timeLimitMinutes) << ":" << static_cast<int>(timePrint) << "s";
					timeText.setString(temp.str());
				}
			}
		}
	}
}

// Calls time update if in Time Trial mode
void UIGame::gameManager(string gameMode)
{
	if (gameMode == gameState.TIMETRIAL) {
		TimeGame();
	}
	
}

// Checks win/lose conditions
void UIGame::checkGame()
{
	if (checkwin(BoardGame, sizeBoard)) {
		WinLose = gameState.WIN;
	}
	else if (checklose(BoardGame, sizeBoard)) {
		WinLose = gameState.LOSE;

	}

}

// Restores previous board state from undo stack
void UIGame::undoGame() {
	if (Undo.isEmpty()) return;

	int** top = Undo.topBoard();
	if (top == nullptr) return;

	for (int i = 0; i < sizeBoard; i++) {
		for (int j = 0; j < sizeBoard; j++) {
			BoardGame[i][j] = top[i][j];
		}
	}

	Score = Undo.topScore();
	Undo.pop();
}

// Reapplies board state from redo stack
void UIGame::redoGame()
{
	for (int i = 0; i < sizeBoard; i++) {
		for (int j = 0; j < sizeBoard; j++) {
			BoardGame[i][j] = Redo.topBoard()[i][j];
		}
	}
	Score = Redo.topScore();
	Redo.pop();

}

// Adjusts score text position based on digit count
void UIGame::setPostitionScore()
{
	if (Score / 10 >= 1000) {
		textScore.setCharacterSize(40);
		textScore.setPosition(312, 80);
		pos = 40;
	}
	else if (Score / 10 >= 100) {
		textScore.setPosition(315, 80);
		pos = 55;
	}
	else if (Score / 10 >= 10) {
		textScore.setPosition(325, 80);
		pos = 35;
	}
	else if (Score / 10 >= 1) {
		textScore.setPosition(340, 80);
		pos = 25;
	}

	if (HighScore / 10 >= 1000) {
		textHighScore.setCharacterSize(40);
		textHighScore.setPosition(535, 95);
	}
	else if (HighScore / 10 >= 100) {
		textHighScore.setPosition(535, 95);
	}
	else if (HighScore / 10 >= 10) {
		textHighScore.setPosition(545, 95);
	}
	else if (HighScore / 10 >= 1) {
		textHighScore.setPosition(560, 95);
	}
}

// Updates score and high score display strings
void UIGame::printScore()
{
	
	ostringstream tempScore;
	tempScore << Score;
	textScore.setString(tempScore.str());
	
	ostringstream tempHighScore;
	tempHighScore << HighScore;
	textHighScore.setString(tempHighScore.str());

	setPostitionScore();
}

// Main event handler delegating to components and functions
void UIGame::updateEvent(sf::Event event)
{

	if (WinLose == gameState.WIN || WinLose == gameState.LOSE) {
		pressdGame(event);
	}
	else {
		dashboard->pressdFuncion(event);
		setGameFunction(dashboard->getGameFunction());
		pollEvents(event);
	}


	dashboardButton();
	checkGame();
}

// Render game UI including dashboard and grid
void UIGame::render()
{
	checkFPS();
	printScore();

	if (gameMode == gameState.TIMETRIAL) {
		window->draw(timeText);
	}

	grid->RenderGridGame(BoardGame);

	dashboard->render();
	window->draw(timeText);
	window->draw(textScore);
	window->draw(textHighScore);
	
	if (WinLose == gameState.WIN) {
		window->draw(sprite[0]);
		window->draw(sprite[2]);
		window->draw(sprite[3]);

		textScore.setCharacterSize(70);
		textScore.setPosition(360 - pos, 630);


		window->draw(textScore);
		window->draw(text[0]);
		window->draw(text[1]);
	}
	else if (WinLose == gameState.LOSE) {
		window->draw(sprite[1]);
		window->draw(sprite[4]);
		window->draw(sprite[5]);
		window->draw(text[2]);
	}
	
}



