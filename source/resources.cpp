#include "resources.h"
#include "Iw2D.h"

Resources::Resources()
{
	// Load images
	mainMenuBG = Iw2DCreateImage("textures/New_Main_Menu.png");
	mainMenuBGHC = Iw2DCreateImage("textures/HC_Menu.png");
	endScreenBG = Iw2DCreateImage("textures/End_Screen.png");
	pauseMenuBG = Iw2DCreateImage("textures/New_Pause_Menu.png");
	pauseMenuBGHC = Iw2DCreateImage("textures/HC_Pause_Menu.png");
	gameBG = Iw2DCreateImage("textures/level_background.png");
	gameBGHC = Iw2DCreateImage("textures/HC_level_background.png");

	playButton = Iw2DCreateImage("textures/play_button.png");
	playButtonHC = Iw2DCreateImage("textures/HC_play_button.png");
	exitButton = Iw2DCreateImage("textures/End_Game_Button.png");
	pauseButton = Iw2DCreateImage("textures/pause.png");
	resetButton = Iw2DCreateImage("textures/reset.png");
	settingsButton = Iw2DCreateImage("textures/Settings_Button.png");
	settingsButtonHC = Iw2DCreateImage("textures/HC_Settings_Button.png");
	backButton = Iw2DCreateImage("textures/back_button2.png");

	star = Iw2DCreateImage("textures/star_complete.png");
	holoStar = Iw2DCreateImage("textures/star_uncomplete.png");

	player = Iw2DCreateImage("textures/character.png");
	playerLeft = Iw2DCreateImage("textures/left.png");
	playerRight = Iw2DCreateImage("textures/right.png");
	playerUp = Iw2DCreateImage("textures/up.png");
	playerDown = Iw2DCreateImage("textures/down.png");
	rock = Iw2DCreateImage("textures/rock.png");
	blank = Iw2DCreateImage("textures/blank.png");
	home = Iw2DCreateImage("textures/igloo.png");
	snowpatch = Iw2DCreateImage("textures/snowpatch.png");
	iceRock = Iw2DCreateImage("textures/Ice_Rock.png");
	shrubSnow = Iw2DCreateImage("textures/Shrub_Snow.png");
	rockUpdated = Iw2DCreateImage("textures/Rock_Updated.png");
	switchUp = Iw2DCreateImage("textures/switch_up.png");
	switchDown = Iw2DCreateImage("textures/switch_down.png");

	level1 = Iw2DCreateImage("textures/level1.png");
	level2 = Iw2DCreateImage("textures/level2.png");
	level3 = Iw2DCreateImage("textures/level3.png");
	level4 = Iw2DCreateImage("textures/level4.png");
	level5 = Iw2DCreateImage("textures/level5.png");
	level6 = Iw2DCreateImage("textures/level6.png");
	level7 = Iw2DCreateImage("textures/level7.png");
	level8 = Iw2DCreateImage("textures/level8.png");
	level9 = Iw2DCreateImage("textures/level9.png");
	level10 = Iw2DCreateImage("textures/level10.png");
	level11 = Iw2DCreateImage("textures/level11.png");
	level12 = Iw2DCreateImage("textures/level12.png");

	upButton = Iw2DCreateImage("textures/up-button.png");
	rightButton = Iw2DCreateImage("textures/right-button.png");
	downButton = Iw2DCreateImage("textures/down-button.png");
	leftButton = Iw2DCreateImage("textures/left-button.png");

	onScreenSettingButton = Iw2DCreateImage("textures/onscreen_settings.png");
	onScreenSettingButtonSelected = Iw2DCreateImage("textures/onscreen_settings_selected.png");
	highContrastButton = Iw2DCreateImage("textures/highcontrast_settings.png");
	highContrastButtonSelected = Iw2DCreateImage("textures/highcontrast_settings_selected.png");
	vibrationButton = Iw2DCreateImage("textures/vibration_settings.png");
	vibrationButtonSelected = Iw2DCreateImage("textures/vibration_settings_selected.png");

	soundButton = Iw2DCreateImage("textures/Sound_Button.png");
	musicButton = Iw2DCreateImage("textures/Music_Button.png");
	soundButtonOff = Iw2DCreateImage("textures/Sound_Button_X.png");
	musicButtonOff = Iw2DCreateImage("textures/Music_Button_X.png");

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
	delete gameBG;
	delete gameBGHC;
	delete pauseMenuBG;
	delete pauseMenuBGHC;

	delete playButton;
	delete playButtonHC;
	delete exitButton;
	delete pauseButton;
	delete resetButton;
	delete settingsButton;
	delete settingsButtonHC;
	delete backButton;

	delete star;
	delete holoStar;

	delete player;
	delete playerLeft;
	delete playerRight;
	delete playerUp;
	delete playerDown;
	delete rock;
	delete blank;
	delete home;
	delete snowpatch;
	delete iceRock;
	delete shrubSnow;
	delete rockUpdated;
	delete switchUp;
	delete switchDown;

	delete level1;
	delete level2;
	delete level3;
	delete level4;
	delete level5;
	delete level6;
	delete level7;
	delete level8;
	delete level9;
	delete level10;
	delete level11;
	delete level12;

	delete upButton;
	delete rightButton;
	delete downButton;
	delete leftButton;

	delete onScreenSettingButton;
	delete onScreenSettingButtonSelected;
	delete highContrastButton;
	delete highContrastButtonSelected;
	delete vibrationButton;
	delete vibrationButtonSelected;

	delete soundButton;
	delete musicButton;
	delete soundButtonOff;
	delete musicButtonOff;

	// Cleanup atlases
	delete playerLeftAtlas;
	delete playerRightAtlas;
	delete playerUpAtlas;
	delete playerDownAtlas;
}

Resources* g_pResources = 0;