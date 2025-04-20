#include "../../Header/Graphic/Rank.h"
#include <sstream>
#include <iostream>

using namespace std;

// Loads font for use in text
void Rank::initFont()
{
    // Tải font để sử dụng trong text
    if (!font.loadFromFile("Text\\LilitaOne-Regular.ttf")) {
        std::cout << "Failed to load font!" << std::endl;
    }
}

// Initializes all sprites for rank screen
void Rank::initAllSprite()
{
    init.initPng(back, Back, "Image\\Rank_image\\Back.png", 1, 1, 1.f, 1.f, sf::Color::White);
    init.initPngUpdate(boardTexture, boardSprite, "Image\\Rank_image\\board1.png", 0, 100.f, 600.f, 900.f, sf::Color::White);
    init.centerSpriteHorizontally(boardSprite, window);

    init.initPngUpdate(sizeTexture, sizeSprite, "Image\\Rank_image\\size.png", 0, boardSprite.getPosition().y - 50.f, 200.f, 100.f, sf::Color::White);
    init.centerSpriteHorizontally(sizeSprite, window);

    

    init.initPngUpdate(leftTexture, leftSprite, "Image\\Rank_image\\left.png", 0, 0, 80.f, 80.f, sf::Color::White);
    init.alignSpriteRightOfSpriteWithCenterY(boardSprite, leftSprite, -(boardSprite.getGlobalBounds().width +( leftSprite.getGlobalBounds().width / 2)));

    init.initPngUpdate(rightTexture, rightSprite, "Image\\Rank_image\\right.png", 0, 0, 80.f, 80.f, sf::Color::White);
    init.alignSpriteRightOfSpriteWithCenterY(boardSprite, rightSprite, -rightSprite.getGlobalBounds().width / 2);


}

// Initializes header texts (#, Player, Score, Mode)
void Rank::initAllText()
{
    init.initText1(rankText, font, 34, boardSprite.getPosition().x + 60.f, boardSprite.getPosition().y + 75.f, sf::Color(81, 45, 24), "#");
    init.initText1(playerText, font, 34, rankText.getPosition().x + 175.f, rankText.getPosition().y, sf::Color(81, 45, 24), "Player");
    init.initText1(scoreText, font, 34, playerText.getPosition().x + 230.f, playerText.getPosition().y, sf::Color(81, 45, 24), "Score");
    init.initText1(modeText, font, 34, 0.f, 0.f, sf::Color::White, boardModes[curBoardIndex]);
    init.centerTextInSprite(modeText, sizeSprite);
}

// Creates a new text object centered at given X coordinate
sf::Text Rank::createNewTextIsCenterOfText(const std::string& str, float centerX, float y) {
    sf::Text text;
  
    init.initText1(text, font, 30, centerX, y, sf::Color(81, 45, 24), str);


    // Gióng giữa theo trục X
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.f, 0.f);
    text.setPosition(centerX, y); // Đặt lại vị trí vì origin đã thay đổi

    return text;
}

// Measures width of a string using current font and size
float Rank::getTextWidth(const std::string& str)
{
    sf::Text tempText;
    tempText.setFont(font);
    tempText.setCharacterSize(30); // Phải giống với createRowText
    tempText.setString(str);
    return tempText.getLocalBounds().width;
}

// Populates the rank list with top players and colors
void Rank::initRankList()
{
    rankListText.clear();

    vector<PlayerNode*> topPlayers;

    leaderBoardManager->getLeaderBoard(curBoardIndex).getTopplayer(topPlayers, 10);

    float startY = rankText.getPosition().y + 65.f;
    int rank = 1;

    for (PlayerNode* player : topPlayers) {
        float y = startY + (rank - 1) * 71.f;


        float rankX = rankText.getPosition().x + rankText.getGlobalBounds().width / 2.f;
        float nameX = playerText.getPosition().x + playerText.getGlobalBounds().width / 2.f;
        float scoreX = scoreText.getPosition().x + scoreText.getGlobalBounds().width / 2.f;

        // Tạo text dòng
        sf::Text tempRankText = createNewTextIsCenterOfText(to_string(rank), rankX, y);
        sf::Text tempPlayerText = createNewTextIsCenterOfText(player->name, nameX, y);
        sf::Text tempScoreText = createNewTextIsCenterOfText(to_string(player->score), scoreX, y);

        sf::Color tempColor;
        if (rank == 1) {
            tempColor = sf::Color(81, 45, 24);
        }
        else if (rank == 2) {
            tempColor = sf::Color(184, 108, 64);
        }
        else if (rank == 3) {
            tempColor = sf::Color(255, 165, 112);
        }
        else {
            tempColor = sf::Color(106, 102, 99);
        }

        tempRankText.setFillColor(tempColor);
        tempPlayerText.setFillColor(tempColor);
        tempScoreText.setFillColor(tempColor);

        rankListText.push_back(tempRankText);
        rankListText.push_back(tempPlayerText);
        rankListText.push_back(tempScoreText);

        rank++;

    }

}

// Handles mouse events to navigate boards and return
void Rank::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

            if (leftSprite.getGlobalBounds().contains(mousePos)) {
                if (curBoardIndex > 0) {
                    curBoardIndex--;
                    modeText.setString(boardModes[curBoardIndex]);
                    initRankList();
                    init.centerTextInSprite(modeText, sizeSprite);
                }
            }
            else if (rightSprite.getGlobalBounds().contains(mousePos)) {
                if (curBoardIndex < (int)boardModes.size() - 1) {
                    curBoardIndex++;
                    modeText.setString(boardModes[curBoardIndex]);
                    initRankList();
                    init.centerTextInSprite(modeText, sizeSprite);

                }
            }
            else if (Back.getGlobalBounds().contains(mousePos)) {
                preWindow = curWindow;
                curWindow = "MENU";
            }
        }
    }
}

// Constructor: sets up window, leaderBoardManager, and initializes components
Rank::Rank(sf::RenderWindow* window, LeaderBoardManager* &lbm, const string& cur, const string& pre)
    : window(window), leaderBoardManager(lbm) , curWindow(cur), preWindow(pre)
{
    curBoardIndex = 0;
    initFont();
    boardModes = {
    "Time Trial", "No Undo/Redo", "3x3", "4x4", "5x5", "6x6", "7x7", "8x8", "9x9", "10x10"
    };
    cout << lbm << endl;
    cout << leaderBoardManager << endl;
	lbm = leaderBoardManager;
    // Thiết lập kiểu chữ
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    initAllSprite();
    initAllText();
    initRankList();

}

// Updates events by delegating to handler
void Rank::updateEvent(const sf::Event& event) {
    handleEvent(event);
}

// Renders board, navigation, headers, and list texts
void Rank::render()
{
    this->window->draw(boardSprite);
    this->window->draw(sizeSprite);
    this->window->draw(Back);
    if (curBoardIndex > 0) {
        this->window->draw(leftSprite);
    }
    if (curBoardIndex < 9) {
        this->window->draw(rightSprite);

    }
    this->window->draw(rankText);
    this->window->draw(playerText);
    this->window->draw(scoreText);
    this->window->draw(modeText);

    for (sf::Text t : rankListText) {
        this->window->draw(t);
    }
}



