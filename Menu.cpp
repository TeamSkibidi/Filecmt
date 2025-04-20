#include "../../Header/Graphic/Menu.h"
#include <iostream>
#include "../../Header/Logic/Init.h"

// Initialize font used in the menu
void Menu::initFont() {
	if (!this->font.loadFromFile("Text\\LilitaOne-Regular.ttf")) {
		std::cout << "Cannot load font!" << std::endl;
	}
}

// Initialize all the menu text buttons
void Menu::initAllText()
{
	init.initText(buttonTexts[0], font, "RESUME", 50, 295.f, 400.f, sf::Color(140, 47, 0));
	init.initText(buttonTexts[1], font, "NEW GAME", 53, 260.f, 530.f, sf::Color(140, 47, 0));
	init.initText(buttonTexts[2], font, "TUTORIAL", 53, 270.f, 657.f, sf::Color(140, 47, 0));
	init.initText(buttonTexts[3], font, "QUIT", 53, 320.f, 785.f, sf::Color(140, 47, 0));
	
}

// Initialize all the images used in the menu (background, frames, icons)
void Menu::initALlImage()
{
	init.initPng(texture[0], spirite[0], "Image\\Menu_image\\Khung.png", 230.f, 390.f, 1.0f, 1.0f, sf::Color::White);
	init.initPng(texture[1], spirite[1], "Image\\Menu_image\\Khung.png", 230.f, 520.f, 1.0f, 1.0f, sf::Color(255, 255, 255));
	init.initPng(texture[2], spirite[2], "Image\\Menu_image\\Khung.png", 230.f, 647.f, 1.0f, 1.0f, sf::Color(255, 255, 255));
	init.initPng(texture[3], spirite[3], "Image\\Menu_image\\Khung.png", 230.f, 775.f, 1.0f, 1.0f, sf::Color(255, 255, 255));
	init.initPng(texture[6], spirite[6], "Image\\Menu_image\\MENU.png", 200.f, 1.f, 0.55f, 0.55f, sf::Color(255, 255, 255));
	init.initPng(texture[7], spirite[7], "Image\\BackGround\\background.png", 1.f, 1.f, 0.8f, 0.8f, sf::Color(255, 255, 255));
	init.initPng(texture[5], spirite[5], "Image\\Menu_image\\Cup.png", 680.f, 5.f, 1.f, 1.f, sf::Color(255, 255, 255));
	init.initPng(texture[4], spirite[4], "Image\\Menu_image\\Setting.png", 5.f, 5.f, 0.9f, 0.9f, sf::Color::Black);
}

// Constructor: initialize menu with current and previous window states
Menu::Menu(sf::RenderWindow* window,const  string& cur,const string& pre) : curWindow(cur), preWindow(pre)
{
	this->window = window;
	for (int i = 0; i < 4; i++) {
		isHovering[i] = false;
		hoverTimer[i] = 0.0f;
	}
	this->initFont();
	this->initALlImage();
	this->initAllText();
	

}

// Handle mouse click events on menu buttons
void Menu::updateEvent(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		sf::Vector2f mousePos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
		std::cout << "phungu";
		for (int i = 0; i < 6; i++)
		{
			sf::FloatRect bounds = spirite[i].getGlobalBounds();
			if (bounds.contains(mousePos)) {
				switch (i)
				{
				case 0:
					preWindow = curWindow;
					curWindow = gameState.RESUME;
					cout << "Resume";
					break;
				case 1:
					preWindow = curWindow;
					curWindow = gameState.NEWGAME;
					break;
				case 2:
					preWindow = curWindow;
					curWindow = gameState.HOWTOPLAY;
					break;
				case 3:
					preWindow = curWindow;
					curWindow = gameState.QUIT;
					window->close();
					break;
				case 4:
					preWindow = curWindow;
					curWindow = gameState.SETTING;
					break;
				case 5:
					preWindow = curWindow;
					curWindow = gameState.RANK;
					break;
				}
			}
		}
		std::cout << "Current Window: " << curWindow << std::endl;
		std::cout << "Previous Window: " << preWindow << std::endl;
	}
}

// Update hover animation when mouse is over buttons
void Menu::updateHover(sf::Vector2f mousePos, float deltaTime) {
	for (int i = 0; i < 4; i++) {
		sf::FloatRect bounds = spirite[i].getGlobalBounds();
		bool wasHovering = isHovering[i];
		isHovering[i] = bounds.contains(mousePos);

		if (isHovering[i]) {
			hoverTimer[i] += deltaTime;
			if (hoverTimer[i] > hoverScaleDuration) {
				hoverTimer[i] = hoverScaleDuration;
			}
			float scale = 1.0f + 0.1f * (hoverTimer[i] / hoverScaleDuration);
			spirite[i].setScale(scale, scale);
			buttonTexts[i].setScale(scale, scale);

		}
		else {
			hoverTimer[i] -= deltaTime;
			if (hoverTimer[i] < 0.0f) {
				hoverTimer[i] = 0.0f;
			}
			float scale = 1.0f + 0.1f * (hoverTimer[i] / hoverScaleDuration); 
			spirite[i].setScale(scale, scale);
			buttonTexts[i].setScale(scale, scale);
		}
	}
}

// Render all menu components to the window
void Menu::render()
{
	this->window->draw(spirite[7]);
	for (int i = 0; i < 7; i++)
	{
		this->window->draw(spirite[i]);
		if (i < 4)
			this->window->draw(buttonTexts[i]);	
	}

}


