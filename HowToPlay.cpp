#include "../../Header/Graphic/HowToPlay.h"
#include <iostream>


// Initializes all tutorial images: board, decorations, and back button
void HowToPlay::initAllImage() {
    init.initPng(texture[0], sprite[0], "Image\\HowToPlay_image\\BoardHowToPlay.png", 0, 0, 0.965, 1.0, sf::Color::White);
    init.initPng(texture[1], sprite[1], "Image\\HowToPlay_image\\TrangTri1.png", 0, 720, 0.5, 0.5, sf::Color::White);
    init.initPng(texture[2], sprite[2], "Image\\HowToPlay_image\\TrangTri2.png", 0, 50, 0.5, 0.5, sf::Color::White);
    init.initPng(texture[3], sprite[3], "Image\\HowToPlay_image\\Back.png", 15, 20, 1, 1, sf::Color::White);

    init.centerSpriteHorizontally(sprite[0], window);
    init.centerSpriteHorizontally(sprite[1], window);
    init.centerSpriteHorizontally(sprite[2], window);

}

// Processes mouse clicks on the back button to return to menu
void HowToPlay::handleEvent(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        sf::FloatRect bounds = sprite[3].getGlobalBounds();
        if (bounds.contains(mousePos)) {
            preWindow = curWindow;
            curWindow = gameState.MENU;
            return;
        }
    }
}

// Sets up the instructional text with formatting, color, and position
void HowToPlay::setupText() {
    text.setFont(font);
    text.setString("\n\n\n\n"
        "\n\n"
        "    Use the arrow keys to move all the tiles in one direction (left, right, up, down) \n"
        " \t\t\t\t\t\t When two tiles with the same number collide \n"
        " \t\t\t\t\t\t They merge into one ( 2 + 2 = 4 or 4 + 4 = 8,... )\n"
        " \t\t\t\t\t\t After each move, a new tile (usually 2 or 4) appears \n\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t END OF THE GAME: \n\n"
        " \t\t\t\t\t\t\t\t\t Win: If you create the 2048 tile\n"
        " \t\t\t\t\t Lose: If there are no empty spaces and no possible merges \n\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t TIPS: \n\n"
        " \t\t\t\t\t\t Try to keep your largest number in one corner \n"
        " \t\t\t\t\t\t Stick to one main direction, avoid random moves \n"
        " \t\t\t\t\t\t Merge smaller tiles before the board gets crowded \n");

    text.setCharacterSize(23);
    text.setFillColor(sf::Color::Black);
    text.setPosition(50, 120);
}

// Constructor loads font, initializes images and text for tutorial screen
HowToPlay::HowToPlay(sf::RenderWindow* window, const string& cur, const string& pre) : window(window), curWindow(cur), preWindow(pre), isShowing(true)
{
    if (!font.loadFromFile("Text\\Dosis-VariableFont_wght.ttf")) {
        std::cout << "Failed to load font!" << std::endl;
    }
    initAllImage();
    setupText();
}

// Delegates SFML events to handler
void HowToPlay::updateEvent(sf::Event event)
{
    handleEvent(event);

}

// Renders tutorial background, decorations, button, and instructional text
void HowToPlay::render() {

       window->draw(sprite[0]);
        window->draw(sprite[1]);
        window->draw(sprite[2]);
        window->draw(sprite[3]);
        window->draw(text);
        cout << "in thanh cong";
    }


