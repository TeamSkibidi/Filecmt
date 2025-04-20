#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

class Init
{
public:
    // Initializes a rectangle shape with position, color, and size
    void initRectangle(sf::RectangleShape& rec, float x, float y, sf::Color color, float sizeWidth, float sizeHight);

    // Initializes text with font, string, size, position, and color
    void initText(sf::Text& newText, const sf::Font& font, const string& text, int size, float x, float y, sf::Color color);

    // Similar to initText but with slightly different parameter order
    void initText1(sf::Text& newText, const sf::Font& font, int size, float x, float y, sf::Color color, const string& text);

    // Loads a PNG image, applies it to a sprite, and sets position, size, and color
    void initPng(sf::Texture& textures, sf::Sprite& newSprite, const string& path, float x, float y, float sizeX, float sizeY, sf::Color color);

    // Updates and reinitializes a PNG image and sprite (useful for reloading)
    void initPngUpdate(sf::Texture& textures, sf::Sprite& newSprite, const string& path, float x, float y, float sizeX, float sizeY, sf::Color color);

    // Horizontally centers a sprite in the window
    void centerSpriteHorizontally(sf::Sprite& sprite, sf::RenderWindow* window);

    // Centers a text object inside a sprite
    void centerTextInSprite(sf::Text& text, const sf::Sprite& sprite);

    // Aligns one sprite to the right of another, keeping vertical center and spacing
    void alignSpriteRightOfSpriteWithCenterY(sf::Sprite& sprite1, sf::Sprite& sprite2, float space);

    // Places text above a sprite with specified padding
    void placeTextAboveSprite(sf::Text& text, sf::Sprite& sprite, float padding);

    // Aligns text to the left inside a sprite
    void alignTextLeftInSprite(sf::Text& text, sf::Sprite& sprite);

    // Places text below a sprite with padding
    void placeTextBelowSprite(sf::Text& text, sf::Sprite& sprite, float padding);

    // Centers text inside a rectangle shape
    void centerTextRec(sf::Text& text, const sf::RectangleShape& Rec);

};
