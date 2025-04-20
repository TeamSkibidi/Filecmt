#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "../../Header/Logic/Init.h"
#include "../../Header/State Game/GameState.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>

#define ull unsigned long long




using namespace std;
class Login {
private:
    struct User {
        string hashed_username;     // Username after hashing to hex
        string hashed_password;     // Password after hashing to hex
        string salt_username;       // Random salt for username
        string salt_password;       // Random salt for password
        bool isActive;              // Indicates if this slot is used
    };

    const int SIZE_HASH_TABLE = 100;
    const int MAX_LONGLONG = 1000000007;
    const int SIZE_SALT = 16;
    const int MAX_SIZE_USERNAME = 15;
    const int MAX_SIZE_PASSWORD = 13;
    const float boxWidth = 400.f;
    const float boxHeight = 65.f;
    const float startY = 550.f;
    const float spaceY = 100.f;

    sf::RenderWindow* window;
    sf::Event event;
    sf::Font font;
    sf::Font fontInput;
    GAMESTATE gameState;

    Init init;
    string curWindow;
    string preWindow;
    vector<User> hashTableUser;

    // Sprites for UI elements
    sf::Sprite imageMainSprite;
    sf::Sprite userNameBoxSprite;
    sf::Sprite passwordBoxSprite;
    sf::Sprite confirmPasswordBoxSprite;
    sf::Sprite signInButtonSprite;
    sf::Sprite switchModeButtonSprite;    // Toggle between Login/Register
    sf::Sprite togglePasswordSprite;      // Show/hide password
    sf::Sprite statusBoxSprite;           // Display status messages

    // Textures for UI elements
    sf::Texture imageMainSpriteTexture;
    sf::Texture userNameBoxTexture;
    sf::Texture passwordBoxTexture;
    sf::Texture confirmPasswordBoxTexture;
    sf::Texture signInButtonTexture;
    sf::Texture switchModeButtonTexture;
    sf::Texture eyeOpenTexture;
    sf::Texture eyeClosedTexture;
    sf::Texture statusBoxTexture;

    // Text elements for labels and input display
    sf::Text usernameLabel;               // "Username" label
    sf::Text passwordLabel;               // "Password" label
    sf::Text confirmLabel;                // "Confirm Password" label
    sf::Text loginText;                   // "Login"/"Register" button text
    sf::Text switchText;                  // Toggle button text
    sf::Text userNameText;                // Display entered username
    sf::Text passWordText;                // Display entered password
    sf::Text checkPassWordText;           // Display password confirmation
    sf::Text registerStatusText;          // Show registration status

    // Variables storing user input
    string inputUserName;
    string inputPassWorld;
    string inputCheck_PassWorld;

    // Flags for input focus
    bool userNameActive = false;
    bool passWordActive = false;
    bool checkPassWordActive = false;

    bool isPasswordShown = false;         // Password visibility flag
    bool isRegistering = false;           // Register mode flag

    // Initialize font resources
    void initFont();

    // Initialize all text objects
    void initAllTexts();

    // Initialize all sprite objects
    void initAllSprites();

    // Convert unsigned long long to hexadecimal string
    string ll_to_hex(ull hash);

    // Generate a random salt string
    string create_salt();

    // Hash username with salt and return hex string
    string hash_username(const string& username, const string& salt);

    // Compute hash table index from username
    int hash_to_index(const string& username);

    // Compute probing step for collision resolution
    int hash_to_step(const string& username);

    // Hash password with salt and return hex string
    string hash_password(const string& password, const string& salt);

    // Write a string and its length into a file
    void save_string(ofstream& file, const string& str);

    // Read a string with its length from a file
    string load_string(ifstream& file);

    // Register a new user account if valid
    bool register_account(const string& username, const string& password, const string& password_check);

    // Verify credentials and log in user
    bool loginUser(const string& username, const string& password);

    // Change existing user password
    bool change_password(const string& username, const string& old_password, const string& new_password);

    // Save user data hash table to file
    void save_to_file(const string& fileName);

    // Load user data hash table from file
    void load_from_file(const string& fileName);

public:
    // Constructor: set up window and initial game mode
    Login(sf::RenderWindow* window, const string& cur, const string& pre);

    // Handle input events (keyboard, mouse)
    void updateEvent(sf::Event event);

    // Draw the login/register interface
    void render();

    // Get current game mode identifier
    const string& getCurModeGame() const { return curWindow; }

    // Get previous game mode identifier
    const string& getPreModeGame() const { return preWindow; }

    // Retrieve the entered username
    const string& getUserName() const { return inputUserName; }
};

