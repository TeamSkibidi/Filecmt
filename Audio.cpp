#include "../../Header/Graphic/Audio.h"
#include <iostream>


// Loads background music from file; returns false on error
bool Audio::loadBackground(const std::string& filename) {
    if (!backgroundMusic.openFromFile(filename)) {
        std::cerr << "Error loading background music from " << filename << std::endl;
        return false;
    }
    return true;
}

// Constructor initializes music state and starts playback
Audio::Audio() : isMusicPlaying(false) {
	// Khởi tạo giá trị false <=> chưa bật nhạc
	if (!loadBackground("Image\\BackGround\\background.ogg")) {
		std::cerr << "Failed to load background music." << std::endl;
	}
	setLoop(true); 
	playBackground(); 
}

// Returns true if music is currently playing
bool Audio::isPLaying() {
    return isMusicPlaying;
}

// Starts background music playback and updates state
void Audio::playBackground() {
    backgroundMusic.play();
    isMusicPlaying = true;
}

// Stops background music playback and updates state
void Audio::stopBackground() {
    backgroundMusic.stop();
    isMusicPlaying = false;
}

// Toggles background music on or off
void Audio::toggleTurnOnAndOffMusic() {
    if (isMusicPlaying == true) {
        stopBackground();
    }
    else {
        playBackground();
    }
}

// Handles input events; toggles music when V is pressed
void Audio::handleInput(sf::Event event) {
    // Trả về true khi nhấn phím V và ngược lại
    // Kiểm mỗi lần bấm có phải phím V hay không
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::V) {
        toggleTurnOnAndOffMusic(); // Bật/Tắt nhạc
    }
}

// Sets looping for background music
void Audio::setLoop(bool loop) {
    backgroundMusic.setLoop(loop);
}

// Retrieves current music volume
float Audio::getVolume() const {
    return backgroundMusic.getVolume();
}

// Sets music volume to given level
void Audio::setVolume(float volume) {
    backgroundMusic.setVolume(volume);
}
