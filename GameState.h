#pragma once
#include <string>

using namespace std;

// Represents different states/screens in the game
struct GAMESTATE {
	string LOGIN     = "LOGIN";
	string MENU		 = "MENU";
	string RESUME    = "RESUME";
	string NEWGAME   = "NEWGAME";
	string CLASSIC   = "CLASSIC";
	string STANDAR	 = "STANDAR";
	string TIMETRIAL = "TIMETRIAL";
	string UIGAME    = "UIGAME";
	string RANK		 = "RANK";
	string HOWTOPLAY = "HOWTOPLAY";
	string SETTING   = "SETTING";
	string LOGOUT    = "LOGOUT";
	string QUIT      = "QUIT";
	string WIN		= "WIN";
	string LOSE		= "LOSE";

};
