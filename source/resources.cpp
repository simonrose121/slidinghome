#include "resources.h"
#include "Iw2D.h"

Resources::Resources()
{
	mainMenuBG = Iw2DCreateImage("textures/menu.png");
	endScreenBG = Iw2DCreateImage("textures/End_Screen.png");
	pauseMenuBG = Iw2DCreateImage("textures/Pause_Menu.png");
	gameBG = Iw2DCreateImage("textures/background.png");
	playButton = Iw2DCreateImage("textures/play_button.png");
	exitButton = Iw2DCreateImage("textures/Exit_Button.png");
	pauseButton = Iw2DCreateImage("textures/pause.png");
	player = Iw2DCreateImage("textures/character.png");
	rock = Iw2DCreateImage("textures/rock.png");
	blank = Iw2DCreateImage("textures/blank.png");
	home = Iw2DCreateImage("textures/igloo.png");
	// Load fonts
	font = Iw2DCreateFont("fonts/arial8.gxfont");
}

Resources::~Resources()
{
	delete mainMenuBG;
	delete endScreenBG;
	delete pauseMenuBG;
	delete playButton;
	delete exitButton;
	delete pauseButton;
	delete player;
	delete gameBG;
	delete rock;
	delete blank;
	delete home;
	delete font;
}

Resources* g_pResources = 0;