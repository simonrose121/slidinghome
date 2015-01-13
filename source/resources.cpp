#include "resources.h"
#include "Iw2D.h"

Resources::Resources()
{
	MainMenuBG = Iw2DCreateImage("textures/menu.png");
	PlayButton = Iw2DCreateImage("textures/play_button.png");
	Player = Iw2DCreateImage("textures/character.png");
	GameBG = Iw2DCreateImage("textures/background.png");
}

Resources::~Resources()
{
	delete MainMenuBG;
	delete PlayButton;
	delete Player;
	delete GameBG;
}

Resources* g_pResources = 0;