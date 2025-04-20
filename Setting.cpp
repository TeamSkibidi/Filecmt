#include "../../Header/Graphic/Setting.h"
#include <iostream>

// Initializes all setting screen images and sprites
void Setting::initAllImage() {
    // Khởi tạo các nút bằng hình ảnh
    init.initPng(texture[0], sprite[0], "Image\\Setting_image\\Back.png", 1, 1, 1, 1, sf::Color::White);
    init.initPng(texture[1], sprite[1], "Image\\Setting_image\\LogOut.png", 0, 610.0, 0.2, 0.2, sf::Color::White);
    init.initPng(texture[2], sprite[2], "Image\\Setting_image\\VolumeOn.png", 0, 360, 0.1, 0.1, sf::Color::Black);
    init.initPng(texture[3], sprite[3], "Image\\Setting_image\\Plus.png", 0, 480.0, 0.4, 0.4, sf::Color::White);
    init.initPng(texture[4], sprite[4], "Image\\Setting_image\\Minus.png", 0, 600.0, 0.25, 0.25, sf::Color::White);
    init.initPngUpdate(texture[5], sprite[5], "Image\\Setting_image\\BoardSetting.png", 0, 104.0, 0.8 * 768.0, 0.8 * 1024, sf::Color::White);
    init.initPng(texture[6], sprite[6], "Image\\Setting_image\\BackGroundSetting.png", 0, 0, 1.0, 0.8, sf::Color::White);
    init.initPng(texture[7], sprite[7], "Image\\Setting_image\\TrangTri1Setting.png", 0, 0, 0.2, 0.2, sf::Color::White);
    init.initPng(texture[8], sprite[8], "Image\\Setting_image\\TrangTri3Setting.png", 0, 790, 0.2, 0.2, sf::Color::White);


    init.centerSpriteHorizontally(sprite[1], window);
    init.centerSpriteHorizontally(sprite[2], window);
    init.centerSpriteHorizontally(sprite[3], window);
    init.centerSpriteHorizontally(sprite[4], window);
    init.centerSpriteHorizontally(sprite[5], window);
    init.centerSpriteHorizontally(sprite[6], window);
    init.centerSpriteHorizontally(sprite[7], window);
    init.centerSpriteHorizontally(sprite[8], window);
}

// Handles mouse click events for setting options
void Setting::handleClick(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        // Kiểm tra 5 nút (sprite[0] đến sprite[4])
        for (int i = 0; i < 5; i++) {
            sf::FloatRect bounds = sprite[i].getGlobalBounds();
            if (bounds.contains(mousePos)) {
                switch (i) {
                case 0:
                    // Nút MENU
                    preWindow = curWindow;
                    curWindow = gameState.MENU;
                    std::cout << "0\t";
                    break;
                case 1:
                    // Nút LOGOUT
                    preWindow = curWindow;
                    curWindow = gameState.LOGOUT;
                    std::cout << "1\t";
                    break;

                case 2:
                    // Xử lý khi có click chuột vào Volume
                    audio->toggleTurnOnAndOffMusic();

                    // Update picture then On/Off music
                    if (audio->isPLaying()) {
                        init.initPng(texture[2], sprite[2], "Setting_image\\VolumeOn.png", 0, 360.0, 0.1, 0.1, sf::Color::Black);
                        init.centerSpriteHorizontally(sprite[2], window);
                    }
                    else {
                        init.initPng(texture[2], sprite[2], "Setting_image\\VolumeOff.png", 0, 360.0, 0.1, 0.1, sf::Color::Black);
                        init.centerSpriteHorizontally(sprite[2], window);
                    }
                    std::cout << "2\t";
                    break;

                case 3: {
                    // Khi click vào ảnh tăng âm lượng thì gọi hàm này
                    // Tăng âm lượng lên 10 đơn vị, tối đa 100
                    float currentVol = audio->getVolume();
                    float newVol = std::min(currentVol + 10.f, 100.f);
                    audio->setVolume(newVol);
                    std::cout << "New Volume " << newVol << std::endl;
                    std::cout << "1\t";
                    break;
                }

                case 4: {
                    // Khi click và ảnh giảm âm lượng thì gọi hàm này
                    // Giảm âm lượng xuống 10 đơn vị, tối thiểu 0
                    float currentVol = audio->getVolume();
                    float newVol = std::max(currentVol - 10.f, 0.f);
                    audio->setVolume(newVol);
                    std::cout << "New Volume " << newVol << std::endl;
                    std::cout << "4\t";
                    break;
                }

                }
            }
        }
    }
}

// Constructor: initializes images and dependencies
Setting::Setting(sf::RenderWindow* window, Audio* audio, const string& cur, const string& pre)
    : window(window), audio(audio), curWindow(cur), preWindow(pre)
{
    initAllImage();
}

// Updates events: processes audio input and click events
void Setting::updateEvent(sf::Event event) {



        audio->handleInput(event); // Xử lý đầu vào khi bấm phím
        handleClick(event); // Xử lý khi click chuột
}

// Renders all setting UI components to the window
void Setting::render() {
    // Vẽ các nút và text tương ứng // Set màu cho nền cửa sổ
    // BackGround
    window->draw(sprite[6]);
    window->draw(sprite[5]);

    window->draw(sprite[0]); // Nút MENU
    window->draw(sprite[1]); // Nút LOGOUT
    window->draw(sprite[2]); // Nút Volume
    window->draw(sprite[3]); // Nút Volume Up
    window->draw(sprite[4]); // Nút Volume Down
    window->draw(sprite[7]);
    window->draw(sprite[8]);

}
