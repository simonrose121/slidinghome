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
	playerLeft = Iw2DCreateImage("textures/left.png");
	playerRight = Iw2DCreateImage("textures/right.png");
	playerUp = Iw2DCreateImage("textures/up.png");
	playerDown = Iw2DCreateImage("textures/down.png");
	rock = Iw2DCreateImage("textures/rock.png");
	blank = Iw2DCreateImage("textures/blank.png");
	home = Iw2DCreateImage("textures/igloo.png");
	// Load fonts
	font = Iw2DCreateFont("fonts/arial8.gxfont");
	int frame_w = (int)(playerLeft->GetWidth() / 3);
	int frame_h = (int)(playerLeft->GetHeight());
	playerLeftAtlas = new CAtlas(frame_w, frame_h, 3, playerLeft);
	playerRightAtlas = new CAtlas(frame_w, frame_h, 3, playerRight);
	playerUpAtlas = new CAtlas(frame_w, frame_h, 3, playerUp);
	playerDownAtlas = new CAtlas(frame_w, frame_h, 3, playerDown);
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
	delete playerLeft;
	delete playerRight;
	delete playerUp;
	delete playerDown;
	delete gameBG;
	delete rock;
	delete blank;
	delete home;
	delete font;

	delete playerLeftAtlas;
	delete playerRightAtlas;
	delete playerUpAtlas;
	delete playerDownAtlas;
}

Resources* g_pResources = 0;