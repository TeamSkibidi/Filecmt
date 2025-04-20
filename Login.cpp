#include "../../Header/Graphic/Login.h"

// Loads main and input fonts for login screen labels and user input
void Login::initFont() {
	font.loadFromFile("Text\\LilitaOne-Regular.ttf");
	fontInput.loadFromFile("Text\\Fredoka-VariableFont_wdth,wght.ttf");
}

// Initializes sprites for UI elements: main frame, input boxes, buttons, and toggle icon
void Login::initAllSprites() {
	// Kích thước và vị trí khung
	

	// Load ảnh khung từ file và căn giữa
	init.initPngUpdate(imageMainSpriteTexture, imageMainSprite, "Image\\Login_image\\Goup.png", 0, 30.f, 500.f, 500.f, sf::Color::White);
	init.centerSpriteHorizontally(imageMainSprite, window);

	init.initPngUpdate(userNameBoxTexture, userNameBoxSprite, "Image\\Login_image\\khung.png", 0, startY, boxWidth, boxHeight, sf::Color::White);
	init.centerSpriteHorizontally(userNameBoxSprite, window);

	init.initPngUpdate(passwordBoxTexture, passwordBoxSprite, "Image\\Login_image\\khung.png", 0, userNameBoxSprite.getPosition().y + spaceY, boxWidth, boxHeight, sf::Color::White);
	init.centerSpriteHorizontally(passwordBoxSprite, window);

	init.initPngUpdate(confirmPasswordBoxTexture, confirmPasswordBoxSprite, "Image\\Login_image\\khung.png", 0, passwordBoxSprite.getPosition().y + spaceY, boxWidth, boxHeight, sf::Color::White);
	init.centerSpriteHorizontally(confirmPasswordBoxSprite, window);

	init.initPngUpdate(signInButtonTexture, signInButtonSprite, "Image\\Login_image\\Login.png", 0, passwordBoxSprite.getPosition().y + spaceY, 181.f, 65.f, sf::Color::White);
	init.centerSpriteHorizontally(signInButtonSprite, window);

	// Nút chuyển chế độ bên phải login
	init.initPngUpdate(switchModeButtonTexture, switchModeButtonSprite, "Image\\Login_image\\Login.png", 0, signInButtonSprite.getPosition().y + spaceY * 3 / 4, 181.f, 65, sf::Color::White);
	init.centerSpriteHorizontally(switchModeButtonSprite, window);

	// Nút ẩn/hiện password bên phải ô password
	init.initPngUpdate(eyeOpenTexture, togglePasswordSprite, "Image\\Login_image\\Close.png", 0, 0, 43.f, 31.f, sf::Color::White);
	init.alignSpriteRightOfSpriteWithCenterY(passwordBoxSprite, togglePasswordSprite, -50.f);
	eyeClosedTexture.loadFromFile("Image\\Login_image\\Open.png");
}

// Initializes all UI text: labels, button text, and user input display
void Login::initAllTexts() {
    init.initText1(usernameLabel, font, 28, 0, 0, sf::Color::Black, "Username");
    init.placeTextAboveSprite(usernameLabel, userNameBoxSprite, 15.f);

    init.initText1(passwordLabel, font, 28, 0, 0, sf::Color::Black, "Password");
    init.placeTextAboveSprite(passwordLabel, passwordBoxSprite, 15.f);

    init.initText1(confirmLabel, font, 28, 0, 0, sf::Color::Black, "Confirm Password");
    init.placeTextAboveSprite(confirmLabel, confirmPasswordBoxSprite, 15.f);

    // Text trong nút login/register
    init.initText1(loginText, font, 32, 0, 0, sf::Color::Black, isRegistering ? "Register" : "Login");
    init.centerTextInSprite(loginText, signInButtonSprite);

    // Text trong nút chuyển chế độ
    init.initText1(switchText, font, 24, 0, 0, sf::Color::Black, isRegistering ? "Login now" : "Register now");
    init.centerTextInSprite(switchText, switchModeButtonSprite);

	// Khởi tạo văn bản cho các ô nhập liệu
	init.initText1(userNameText, fontInput, 31, 0, 0, sf::Color::Black, "");  // Không có chữ ban đầu
	init.initText1(passWordText, fontInput, 31, 0, 0, sf::Color::Black, "");
	init.initText1(checkPassWordText, fontInput, 31, 0, 0, sf::Color::Black, "");

	// Khởi tạo văn bản cho trạng thái đăng ký (register status)
	init.initText1(registerStatusText, font, 20, 0, 0, sf::Color::Black, "");
	init.placeTextBelowSprite(registerStatusText, passwordBoxSprite, 1.f);

	// Căn trái văn bản trong các sprite (thực hiện cho các ô nhập liệu)
	init.alignTextLeftInSprite(userNameText, userNameBoxSprite);  // Căn trái "Username"
	init.alignTextLeftInSprite(passWordText, passwordBoxSprite);  // Căn trái "Password"
	init.alignTextLeftInSprite(checkPassWordText, confirmPasswordBoxSprite);  // Căn trái "Confirm Password"
	


}

// Converts a long long hash value to a fixed-length hexadecimal string
string Login::ll_to_hex(ull hash) {
	string hex_str = "";
	const string hex_strs = "123456789abcdef";
	while (hash > 0) {
		hex_str = hex_strs[hash % 16] + hex_str;
		hash /= 16;
	}

	while (hex_str.size() < 16) {
		hex_str = "0" + hex_str;
	}

	return hex_str;
}

// Generates a random salt string of fixed length for hashing
string Login::create_salt() {
	string charAll = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()";
	string salt;
	for (int i = 0; i < SIZE_SALT; i++) {
		salt += charAll[rand() % charAll.size()];
	}

	return salt;
}

// Produces a hex hash of username+salt using simple modulo arithmetic
//Ví dụ băm minhbiminh ra một chuỗi số "423413437" rồi chuyển sang mã HEX
string Login::hash_username(const string& username, const string& salt) {
	string data = username + salt;
	ull hash = 0;           //Tạo một biến để lưu dữ liệu sau khi hash
	for (char c : data) {     //Lấy từng kí tự ra và hash
		hash = (hash * 37 + c) % MAX_LONGLONG;
	}

	return ll_to_hex(hash);     //Chuyển đổi số sang dạng mã hex
}

// Primary hash function to map username to table index
int Login::hash_to_index(const string& username) {
	// Hàm băm chính username (băm ra một số trong khoảng SIZE_HASH_TABLE)
	ull hash = 0;
	for (char c : username) {     //Lấy từng kí tự ra và hash
		hash = (hash * 37 + c) % MAX_LONGLONG;
	}
	return hash % SIZE_HASH_TABLE;          //Lấy index để truy cập
}

// Secondary hash to compute step size for open addressing (ensuring odd step)
int Login::hash_to_step(const string& username) {
	// Hàm băm phụ nhằm tìm kiếm step đến ô khác nếu index hiện tại đã có
	// Hàm băm phụ này lun trả về số lẻ vì để tránh LẶP VÔ TẬN
	ull hash = 0;
	for (char c : username) {     //Lấy từng kí tự ra và hash
		hash = (hash * 37 + c) % MAX_LONGLONG;
	}

	int step = hash % (SIZE_HASH_TABLE - 1);
	if (step % 2 == 0) {
		step += 1;
	}

	return step;
}

// Hashes password+salt into a hex string
string Login::hash_password(const string& password, const string& salt) {
	string data = password + salt;
	ull hash = 0;
	for (char s : data) {
		hash = (hash * 37 + s) % SIZE_HASH_TABLE;
	}

	return ll_to_hex(hash);
}

// Save Information into file Binary 

// Writes a length-prefixed string to a binary file
void Login::save_string(ofstream& file, const string& str) {
	size_t length = str.size();
	file.write((char*)&length, sizeof(length));     //Ghi độ dài trước
	cout << "[DEBUG] Reading string length: " << length << endl;
	file.write(str.data(), length);
}


// Get Information from file Binary

// Reads a length-prefixed string from a binary file
string Login::load_string(ifstream& file) {
	size_t length;
	file.read((char*)&length, sizeof(length));


	string str(length, ' ');
	file.read(&str[0], length);

	return str;
}

// Saves all user records in hash table to a binary file
void Login::save_to_file(const string& fileName) {
	ofstream file(fileName, ios::binary);
	if (!file.is_open()) {
		cout << "Khong the mo file ghi" << endl;
		return;
	}

	for (const User& user : hashTableUser) {
		save_string(file, user.hashed_username);
		save_string(file, user.hashed_password);
		save_string(file, user.salt_username);
		save_string(file, user.salt_password);

		file.write((char*)&user.isActive, sizeof(user.isActive));
	}

	file.close();
	cout << "Luu du lieu thanh cong" << endl;
}

// Loads user records from binary file into hash table, initializing if missing
void Login::load_from_file(const string& fileName) {
	ifstream file(fileName, ios::binary);
	if (!file.is_open()) {
		ofstream file_out(fileName, ios::binary);
		for (int i = 0; i < SIZE_HASH_TABLE; i++) {
			User emptyUser = {};
			save_string(file_out, "");
			save_string(file_out, "");
			save_string(file_out, "");
			save_string(file_out, "");
			file_out.write((char*)&emptyUser.isActive, sizeof(bool));
		}
		file_out.close();
		return;
	}

	int index = 0;
	while (index < SIZE_HASH_TABLE) {
		User user;
		
		user.hashed_username = load_string(file);
		user.hashed_password = load_string(file);
		user.salt_username = load_string(file);
		user.salt_password = load_string(file);
		file.read((char*)&user.isActive, sizeof(user.isActive));
		hashTableUser[index++] = user;
		/*cout << "[DEBUG] Read user " << index << ": " << user.hashed_username << endl;*/

	}

	file.close();
	cout << "Tai du lieu thanh cong" << endl;
}

// Registers a new account: validates, checks collisions, hashes credentials, saves
bool Login::register_account(const string& username, const string& password, const string& password_check) {
	load_from_file("users.dat");

	

	if (username.empty()) {
		registerStatusText.setString("Username cannot be empty");
		inputUserName.clear();
		userNameText.setString("");
		return false;
	}
	else if (password.empty()) {
		registerStatusText.setString("Password cannot be empty");
		inputPassWorld.clear();
		passWordText.setString("");
		return false;
	}
	else if (password_check.empty()) {
		registerStatusText.setString("Confirm password cannot be empty");
		inputCheck_PassWorld.clear();
		checkPassWordText.setString("");
		return false;
	}
	else if (username.size() > MAX_SIZE_USERNAME) {
		registerStatusText.setString("Username must be less than 20 characters");
		inputUserName.clear();
		userNameText.setString("");
		return false;
	}
	else if (password.size() > MAX_SIZE_PASSWORD) {
		registerStatusText.setString("Password must be less than 20 characters");
		inputPassWorld.clear();
		passWordText.setString("");
		return false;
	}

	if (password != password_check) {
		registerStatusText.setString("Confirm password does not match");
		// Reset lại chỉ trường confirm password
		inputCheck_PassWorld.clear();
		checkPassWordText.setString("");
		return false;
	}

	
	int index = hash_to_index(username);
	int step = hash_to_step(username);

	int i = 0;      //Có chỉ số i để bội lần step dịch ô không trùng
	bool accountExists = false;

	while (i < SIZE_HASH_TABLE && hashTableUser[(index + i * step) % SIZE_HASH_TABLE].isActive == true) {
		int checkIndex = (index + i * step) % SIZE_HASH_TABLE;
		User& user = hashTableUser[checkIndex];

		string temp_userName = hash_username(username, user.salt_username);
		if (user.hashed_username == temp_userName) {
			accountExists = true;
			break;
		}

		++i;
	}

	if (i == SIZE_HASH_TABLE) {
		registerStatusText.setString("Server is full, can't register more");
		return false;
	}

	if (accountExists) {
		registerStatusText.setString("Account already exists");
		// Reset lại tất cả các trường nhập liệu để người dùng nhập lại
		inputUserName.clear();
		inputPassWorld.clear();
		inputCheck_PassWorld.clear();
		userNameText.setString("");
		passWordText.setString("");
		checkPassWordText.setString("");
		return false;
	}

	//Khi xuống được tới đây tức là ĐÃ tìm được Ô TRỐNG và KHÔNG TỒN TẠI tài khoản trùng
	int indexOfEmpty = (index + i * step) % SIZE_HASH_TABLE;
	string username_salt = create_salt();
	string password_salt = create_salt();
	string hashed_username = hash_username(username, username_salt);
	string hashed_password = hash_password(password, password_salt);

	hashTableUser[indexOfEmpty] = { hashed_username, hashed_password, username_salt, password_salt, true };
	registerStatusText.setString("Account created successfully");
	save_to_file("users.dat");


	// Reset các trường nhập liệu và chuyển về màn hình đăng nhập
	inputUserName.clear();
	inputPassWorld.clear();
	inputCheck_PassWorld.clear();
	userNameText.setString("");
	passWordText.setString("");
	checkPassWordText.setString("");
	isRegistering = true;


}

// Attempts login by matching hashed credentials
bool Login::loginUser(const string& username, const string& password) {
	load_from_file("users.dat");
	

	if (username.empty() || password.empty()) {
		registerStatusText.setString("Do not leave any cells blank");
		return false;
	}

	int index = hash_to_index(username);
	int step = hash_to_step(username);
	int i = 0;

	while (i < SIZE_HASH_TABLE && hashTableUser[(index + i * step) % SIZE_HASH_TABLE].isActive == true) {
		int checkIndex = (index + i * step) % SIZE_HASH_TABLE;
		User& user = hashTableUser[checkIndex];

		if (user.hashed_username == hash_username(username, hashTableUser[checkIndex].salt_username)) {
			if (user.hashed_password == hash_password(password, hashTableUser[checkIndex].salt_password)) {
				return true;
			}
			else {
				registerStatusText.setString("Incorrect password, please re-enter");
				inputPassWorld.clear();
				passWordText.setString("");
				return false;
			}
		}

		++i;
	}

	registerStatusText.setString("Don't have an account yet");
	// Có thể reset lại username nếu muốn
	inputUserName.clear();
	userNameText.setString("");
	inputPassWorld.clear();
	passWordText.setString("");

	return false;
}

// Changes password for existing user, rehashing and saving
bool Login::change_password(const string& username, const string& old_password, const string& new_password) {
	int index = hash_to_index(username);
	int step = hash_to_step(username);

	int i = 0;

	while (i < SIZE_HASH_TABLE && hashTableUser[(index + i * step) % SIZE_HASH_TABLE].isActive == true) {
		int checkIndex = (index + i * step) % SIZE_HASH_TABLE;
		User& user = hashTableUser[checkIndex];

		if (user.hashed_username == hash_username(username, hashTableUser[checkIndex].salt_username)) {
			if (user.hashed_password == hash_password(old_password, hashTableUser[checkIndex].salt_password)) {
				user.salt_password = create_salt();
				user.hashed_password = hash_password(new_password, user.salt_password);
				save_to_file("users.dat");
				return true;
			}
			else {
				return false;
			}
		}
		++i;
	}
	return false;
}

// Constructor sets up window, modes, initializes data structures, fonts, sprites, text
Login::Login(sf::RenderWindow* window, const string& cur, const string& pre) 
	: window(window), curWindow(cur), preWindow(pre),
	hashTableUser(SIZE_HASH_TABLE, { "", "", "", "", false }) {
	initFont();
	initAllSprites();
	initAllTexts();
}

// Handles SFML events: clicks, keypresses, text input
void Login::updateEvent(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonReleased) {
		sf::Vector2f mousePos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

		if (userNameBoxSprite.getGlobalBounds().contains(mousePos)) {
			userNameActive = true;
			passWordActive = false;
			checkPassWordActive = false;
		}
		else if (togglePasswordSprite.getGlobalBounds().contains(mousePos)) {
			// Cập nhật hình ảnh icon
			togglePasswordSprite.setTexture(isPasswordShown ? eyeOpenTexture : eyeClosedTexture);


			init.alignSpriteRightOfSpriteWithCenterY(passwordBoxSprite, togglePasswordSprite, -50.f);

			isPasswordShown = !isPasswordShown;
			passWordText.setString(isPasswordShown ? inputPassWorld : std::string(inputPassWorld.size(), '*'));
			checkPassWordText.setString(isPasswordShown ? inputCheck_PassWorld : std::string(inputCheck_PassWorld.size(), '*'));


		}
		else if (passwordBoxSprite.getGlobalBounds().contains(mousePos)) {
			userNameActive = false;
			passWordActive = true;
			checkPassWordActive = false;
		}
		else if (confirmPasswordBoxSprite.getGlobalBounds().contains(mousePos) && isRegistering) {
			userNameActive = false;
			passWordActive = false;
			checkPassWordActive = true;
		}
		else if (signInButtonSprite.getGlobalBounds().contains(mousePos)) {
			if (isRegistering) {
				if (register_account(inputUserName, inputPassWorld, inputCheck_PassWorld)) {
					// Nếu thành công → chuyển qua login
					isRegistering = false;
					registerStatusText.setString("Account created successfully! Please log in.");


					signInButtonSprite.setPosition(signInButtonSprite.getPosition().x, passwordBoxSprite.getPosition().y + spaceY);
					switchModeButtonSprite.setPosition(switchModeButtonSprite.getPosition().x, signInButtonSprite.getPosition().y + spaceY * 3 / 4);
					init.placeTextBelowSprite(registerStatusText, passwordBoxSprite, 1.f);

					switchText.setString("To Register");
					loginText.setString("Sign in");
					init.centerTextInSprite(loginText, signInButtonSprite);
					init.centerTextInSprite(switchText, switchModeButtonSprite);
				}
			}
			else {
				if (loginUser(inputUserName, inputPassWorld)) {
					preWindow = curWindow;
					curWindow = gameState.MENU;
				}
			}
		}
		else if (switchModeButtonSprite.getGlobalBounds().contains(mousePos)) {
			isRegistering = !isRegistering;
			registerStatusText.setString("");
			inputUserName.clear();
			inputPassWorld.clear();
			inputCheck_PassWorld.clear();
			userNameText.setString("");
			passWordText.setString("");
			checkPassWordText.setString("");

			// Cập nhật nhãn các nút
			switchText.setString(isRegistering ? "To Login" : "To Register");
			loginText.setString(isRegistering ? "Register" : "Sign in");

			signInButtonSprite.setPosition(signInButtonSprite.getPosition().x, isRegistering ? confirmPasswordBoxSprite.getPosition().y + spaceY : passwordBoxSprite.getPosition().y + spaceY);
			switchModeButtonSprite.setPosition(switchModeButtonSprite.getPosition().x, signInButtonSprite.getPosition().y + spaceY * 3 / 4);
			init.placeTextBelowSprite(registerStatusText, isRegistering ? confirmPasswordBoxSprite : passwordBoxSprite, 1.f);

			// Căn giữa lại text trong nút
			init.centerTextInSprite(loginText, signInButtonSprite);
			init.centerTextInSprite(switchText, switchModeButtonSprite);
		}
		
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
		if (isRegistering) {
			register_account(inputUserName, inputPassWorld, inputCheck_PassWorld);

		}
		else {
			if (loginUser(inputUserName, inputPassWorld)) {
				preWindow = curWindow;
				curWindow = gameState.MENU;	
			}
		}
	}

	if (event.type == sf::Event::TextEntered) {
		if (event.text.unicode == 8) {
			if (userNameActive && !inputUserName.empty())
				inputUserName.pop_back();
			if (passWordActive && !inputPassWorld.empty())
				inputPassWorld.pop_back();
			if (checkPassWordActive && !inputCheck_PassWorld.empty())
				inputCheck_PassWorld.pop_back();
		}
		else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
			if (userNameActive && inputUserName.size() < MAX_SIZE_USERNAME)
				inputUserName += static_cast<char>(event.text.unicode);
			if (passWordActive && inputPassWorld.size() < MAX_SIZE_PASSWORD)
				inputPassWorld += static_cast<char>(event.text.unicode);
			if (checkPassWordActive && inputCheck_PassWorld.size() < MAX_SIZE_PASSWORD)
				inputCheck_PassWorld += static_cast<char>(event.text.unicode);
		}

		// Cập nhật hiển thị text
		userNameText.setString(inputUserName);
		passWordText.setString(isPasswordShown ? inputPassWorld : std::string(inputPassWorld.size(), '*'));
		checkPassWordText.setString(isPasswordShown ? inputCheck_PassWorld : std::string(inputCheck_PassWorld.size(), '*'));
	}
}

// Renders all login screen components: boxes, buttons, labels, input, status
void Login::render()
{
	// Vẽ các ô nhập liệu
	this->window->draw(imageMainSprite);
	this->window->draw(userNameBoxSprite);
	this->window->draw(passwordBoxSprite);
	if (isRegistering)
		this->window->draw(confirmPasswordBoxSprite);

	// Vẽ các nút
	this->window->draw(signInButtonSprite);
	this->window->draw(switchModeButtonSprite);
	this->window->draw(togglePasswordSprite);

	// Vẽ nhãn các ô
	this->window->draw(usernameLabel);
	this->window->draw(passwordLabel);
	if (isRegistering)
		this->window->draw(confirmLabel);

	// Vẽ nội dung người dùng nhập
	this->window->draw(userNameText);
	this->window->draw(passWordText);
	if (isRegistering)
		this->window->draw(checkPassWordText);

	// Vẽ nội dung trên các nút
	this->window->draw(loginText);
	this->window->draw(switchText);

	// Vẽ thông báo trạng thái
	this->window->draw(registerStatusText);
}

