#include "resources.h"
#include "Iw2D.h"

Resources::Resources()
{
	mainMenuBG = Iw2DCreateImage("textures/menu.png");
	gameBG = Iw2DCreateImage("textures/background.png");
	playButton = Iw2DCreateImage("textures/play_button.png");
	player = Iw2DCreateImage("textures/character.png");
	rock = Iw2DCreateImage("textures/rock.png");
	blank = Iw2DCreateImage("textures/blank.png");
	// Load fonts
	font = Iw2DCreateFont("fonts/arial8.gxfont");
}

Resources::~Resources()
{
	delete mainMenuBG;
	delete playButton;
	delete player;
	delete gameBG;
	delete rock;
	delete blank;
	delete font;
}

Resources* g_pResources = 0;