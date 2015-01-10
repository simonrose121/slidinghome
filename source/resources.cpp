#include "resources.h"
#include "Iw2D.h"

Resources::Resources()
{
	MainMenuBG = Iw2DCreateImage("textures/menu.png");
	PlayButton = Iw2DCreateImage("textures/play_button.png");
}

Resources::~Resources()
{
	delete MainMenuBG;
	delete PlayButton;
}

Resources* g_pResources = 0;