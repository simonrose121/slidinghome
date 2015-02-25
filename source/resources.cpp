#include "resources.h"
#include "Iw2D.h"

Resources::Resources()
{
	// Load images
	mainMenuBG = Iw2DCreateImage("textures/menu.png");
	mainMenuBGHC = Iw2DCreateImage("textures/HC_Menu.png");
	endScreenBG = Iw2DCreateImage("textures/End_Screen.png");
	pauseMenuBG = Iw2DCreateImage("textures/Pause_Menu.png");
	gameBG = Iw2DCreateImage("textures/background.png");
	gameBGHC = Iw2DCreateImage("textures/HC_Background_1st_Level.png");
	playButton = Iw2DCreateImage("textures/play_button.png");
	playButtonHC = Iw2DCreateImage("textures/HC_play_button.png");
	exitButton = Iw2DCreateImage("textures/Exit_Button.png");
	pauseButton = Iw2DCreateImage("textures/pause.png");
	settingsButton = Iw2DCreateImage("textures/Settings_Button.png");
	settingsButtonHC = Iw2DCreateImage("textures/HC_Settings_Button.png");
	star = Iw2DCreateImage("textures/star_complete.png");
	holoStar = Iw2DCreateImage("textures/star_uncomplete.png");
	player = Iw2DCreateImage("textures/character.png");
	playerLeft = Iw2DCreateImage("textures/left.png");
	playerRight = Iw2DCreateImage("textures/right.png");
	playerUp = Iw2DCreateImage("textures/up.png");
	playerDown = Iw2DCreateImage("textures/down.png");
	rock = Iw2DCreateImage("textures/rock.png");
	levelButton = Iw2DCreateImage("textures/Level_button.png");
	blank = Iw2DCreateImage("textures/blank.png");
	home = Iw2DCreateImage("textures/igloo.png");
	upButton = Iw2DCreateImage("textures/up-arrow.png");
	rightButton = Iw2DCreateImage("textures/right-arrow.png");
	downButton = Iw2DCreateImage("textures/down-arrow.png");
	leftButton = Iw2DCreateImage("textures/left-arrow.png");
	onScreenSettingButton = Iw2DCreateImage("textures/onscreen_settings.png");
	onScreenSettingButtonSelected = Iw2DCreateImage("textures/onscreen_settings_selected.png");
	highContrastButton = Iw2DCreateImage("textures/highcontrast_settings.png");
	highContrastButtonSelected = Iw2DCreateImage("textures/highcontrast_settings_selected.png");
	backButton = Iw2DCreateImage("textures/back_button2.png");
	// Load fonts
	font = Iw2DCreateFont("fonts/arial8.gxfont");

	// Load atlases
	int frame_w = (int)(playerLeft->GetWidth() / 3);
	int frame_h = (int)(playerLeft->GetHeight());
	playerLeftAtlas = new CAtlas(frame_w, frame_h, 3, playerLeft);
	playerRightAtlas = new CAtlas(frame_w, frame_h, 3, playerRight);
	playerUpAtlas = new CAtlas(frame_w, frame_h, 3, playerUp);
	playerDownAtlas = new CAtlas(frame_w, frame_h, 3, playerDown);
}

Resources::~Resources()
{
	// Cleanup images
	delete mainMenuBG;
	delete mainMenuBGHC;
	delete endScreenBG;
	delete pauseMenuBG;
	delete playButton;
	delete playButtonHC;
	delete exitButton;
	delete pauseButton;
	delete settingsButton;
	delete settingsButtonHC;
	delete star;
	delete holoStar;
	delete player;
	delete playerLeft;
	delete playerRight;
	delete playerUp;
	delete playerDown;
	delete gameBG;
	delete gameBGHC;
	delete rock;
	delete levelButton;
	delete blank;
	delete home;
	delete upButton;
	delete rightButton;
	delete downButton;
	delete leftButton;
	delete onScreenSettingButton;
	delete onScreenSettingButtonSelected;
	delete highContrastButton;
	delete highContrastButtonSelected;
	delete backButton;

	// Cleanup fonts
	delete font;

	// Cleanup atlases
	delete playerLeftAtlas;
	delete playerRightAtlas;
	delete playerUpAtlas;
	delete playerDownAtlas;
}

Resources* g_pResources = 0;