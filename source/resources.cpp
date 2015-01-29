#include "resources.h"
#include "Iw2D.h"

Resources::Resources()
{
	MainMenuBG = Iw2DCreateImage("textures/menu.png");
	GameBG = Iw2DCreateImage("textures/background.png");

	PlayButton = Iw2DCreateImage("textures/play_button.png");
	Player = Iw2DCreateImage("textures/character.png");
	Rock = Iw2DCreateImage("textures/rock.png");
	Blank = Iw2DCreateImage("textures/blank.png");
	PlayButton = Iw2DCreateImage("textures/play_button.png");
	// Load fonts
	Font = Iw2DCreateFont("fonts/arial8.gxfont");
}

Resources::~Resources()
{
	delete MainMenuBG;
	delete PlayButton;
	delete Player;
	delete GameBG;
	delete Rock;
	delete Blank;
	delete PlayButton;
	delete Font;
}

Resources* g_pResources = 0;