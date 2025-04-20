#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

class Audio {
private:
    sf::Music backgroundMusic; // Use to play background music
    bool isMusicPlaying;       // Check the current status of the music
public:
    // Constructor: initialize music playing state to false
    Audio();

    // Return whether background music is currently playing
    bool isPLaying();

    // Load background music file (e.g., "background.ogg")
    bool loadBackground(const std::string& filename);

    // Start playing the loaded background music
    void playBackground();

    // Stop the background music if it is playing
    void stopBackground();

    // Toggle background music on or off
    void toggleTurnOnAndOffMusic(); // Chuyển đổi giữa bật và tắt nhạc

    // Process input events for audio control (e.g., keypress to mute/unmute)
    void handleInput(sf::Event event);

    // Set looping behavior for background music
    void setLoop(bool loop); // Đặt chế độ loop (phát lặp)

    // Get the current volume level (0.0 to 100.0)
    float getVolume() const;

    // Set the volume level (0.0 to 100.0)
    void setVolume(float volume);
};
