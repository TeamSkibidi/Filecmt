#include "../../Header/Logic/Init.h"
#include <iostream>

using namespace std;

// Initializes a RectangleShape with specified size, color, and position
void Init::initRectangle(sf::RectangleShape& rec, float x, float y, sf::Color color, float sizeWidth, float sizeHight)
{
	rec.setSize(sf::Vector2f(sizeWidth, sizeHight));
	rec.setFillColor(color);
	rec.setPosition(x, y);
}

// Initializes a Text object with font, size, color, position, and string content
void Init::initText1(sf::Text& newText, const sf::Font& font, int size, float x, float y, sf::Color color, const string& text)
{
	newText.setFont(font);
	newText.setString(text);
	newText.setCharacterSize(size);
	newText.setFillColor(color);
	newText.setPosition(x, y);
}


// Overload: Initializes a Text object with given parameters
void Init::initText(sf::Text& newText,const sf::Font &font, const string &text, int size, float x, float y, sf::Color color)
{
	newText.setFont(font);
	newText.setString(text);
	newText.setCharacterSize(size);
	newText.setFillColor(color);
	newText.setPosition(x, y);
}

// Loads a texture from file, sets it to a Sprite, scales, positions, and colors it
void Init::initPng(sf::Texture &textures, sf::Sprite &newSprite, const string& path, float x, float y, float sizeX, float sizeY, sf::Color color)
{
	if (!textures.loadFromFile(path)) {
		cout << "Error loading file png " << path << endl;
		return;
	}
	textures.setSmooth(true);
	newSprite.setTexture(textures);
	newSprite.setScale(sizeX, sizeY);
	newSprite.setPosition(x, y);
	newSprite.setColor(color);
}

// Reloads and updates a texture, adjusts sprite scale to desired size, positions, and colors it
void Init::initPngUpdate(sf::Texture& textures, sf::Sprite& newSprite, const string& path, float x, float y, float sizeX, float sizeY, sf::Color color)
{
	if (!textures.loadFromFile(path)) {
		cout << "Error loading file png " << path << endl;
		return;
	}
	textures.setSmooth(true);
	newSprite.setTexture(textures);
	sf::Vector2u textureSize = textures.getSize();
	if (textureSize.x > 0 && textureSize.y > 0) {
		float scaleX = sizeX / static_cast<float>(textureSize.x);
		float scaleY = sizeY / static_cast<float>(textureSize.y);
		newSprite.setScale(scaleX, scaleY);
	}
	newSprite.setPosition(x, y);
	newSprite.setColor(color);
}

// Centers a Sprite horizontally within the RenderWindow, preserving its Y position
void Init::centerSpriteHorizontally(sf::Sprite& sprite, sf::RenderWindow* window)
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	float windowWidth = static_cast<float>(window->getSize().x);

	// Giữ nguyên Y, chỉ cập nhật X
	float newX = (windowWidth - bounds.width) / 2.f;
	sprite.setPosition(newX, sprite.getPosition().y);

}

// Centers a Text object inside a Sprite based on the Sprite's global bounds
void Init::centerTextInSprite(sf::Text& text, const sf::Sprite& sprite) {
	// Lấy kích thước thật của text
	sf::FloatRect textBounds = text.getLocalBounds();

	// Set origin về giữa chữ
	text.setOrigin(
		textBounds.left + textBounds.width / 2.f,
		textBounds.top + textBounds.height / 2.f
	);

	// Lấy bounds thật của sprite sau khi scale
	sf::FloatRect spriteBounds = sprite.getGlobalBounds();

	// Căn giữa text vào giữa sprite
	text.setPosition(
		spriteBounds.left + spriteBounds.width / 2.f,
		spriteBounds.top + spriteBounds.height / 2.f
	);
}

// Aligns sprite2 to the right of sprite1 with specified horizontal space, centered vertically
void Init::alignSpriteRightOfSpriteWithCenterY(sf::Sprite& sprite1, sf::Sprite& sprite2, float space) {
	// Lấy vị trí và kích thước của sprite1
	sf::FloatRect sprite1Bounds = sprite1.getGlobalBounds();

	// Lấy vị trí Y tâm của sprite1
	float sprite1CenterY = sprite1.getPosition().y + sprite1Bounds.height / 2.f;

	// Tính toán vị trí của sprite2 sao cho nó nằm bên phải sprite1 với khoảng cách space
	float newX = sprite1Bounds.left + sprite1Bounds.width + space;

	// Đặt sprite2 sao cho tâm Y của nó căn bằng tâm Y của sprite1
	float newY = sprite1CenterY - sprite2.getGlobalBounds().height / 2.f;

	// Đặt lại vị trí của sprite2
	sprite2.setPosition(newX, newY);
}

// Places Text directly above a Sprite with specified padding
void Init::placeTextAboveSprite(sf::Text& text, sf::Sprite& sprite, float padding) {
	// Lấy vị trí của sprite
	sf::FloatRect spriteBounds = sprite.getGlobalBounds();

	// Đặt vị trí text ngay trên sprite, không căn giữa
	float newX = sprite.getPosition().x;  // Đặt theo x của sprite (không căn giữa)
	float newY = sprite.getPosition().y - text.getLocalBounds().height - padding; // Đặt text lên trên sprite

	// Đặt lại vị trí cho text
	text.setPosition(newX, newY);
}

// Function to left-align input text in a sprite
void Init::alignTextLeftInSprite(sf::Text& text, sf::Sprite& sprite) {
	// Lấy kích thước của sprite và text
	sf::FloatRect spriteBounds = sprite.getGlobalBounds();
	sf::FloatRect textBounds = text.getLocalBounds();

	// Đặt text bắt đầu từ bên trái của sprite
	text.setOrigin(textBounds.left, textBounds.top);
	text.setPosition(sprite.getPosition().x + 15.f, sprite.getPosition().y + 10.f);
}

// Places Text below a Sprite with specified padding
void Init::placeTextBelowSprite(sf::Text& text, sf::Sprite& sprite, float padding) {
	// Lấy vùng bao của sprite
	sf::FloatRect spriteBounds = sprite.getGlobalBounds();

	// Tính vị trí mới cho text
	float newX = sprite.getPosition().x;  // Không căn giữa, đặt sát trái sprite
	float newY = sprite.getPosition().y + spriteBounds.height + padding;

	// Đặt vị trí cho text
	text.setPosition(newX, newY);
}

// Centers Text within a RectangleShape based on the rectangle's global bounds
void Init::centerTextRec(sf::Text& text, const sf::RectangleShape& Rec)
{
	// Lấy kích thước thật của text
	sf::FloatRect textBounds = text.getLocalBounds();

	// Set origin về giữa chữ
	text.setOrigin(
		textBounds.left + textBounds.width / 2.f,
		textBounds.top + textBounds.height / 2.f
	);

	// Lấy bounds thật của sprite sau khi scale
	sf::FloatRect spriteBounds = Rec.getGlobalBounds();

	// Căn giữa text vào giữa sprite
	text.setPosition(
		spriteBounds.left + spriteBounds.width / 2.f,
		spriteBounds.top + spriteBounds.height / 2.f
	);
}
