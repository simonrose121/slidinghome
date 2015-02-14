
#if !defined(__RESOURCES_H__)
#define __RESOURCES_H__

#include "Iw2D.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraph;

/**
* @class Resources
*
* @brief Resources class
*
* The that manages the lifetime of the following types of resources:
* - Images
* - Fonts
* - Atlases
*/
class Resources
{
public:
	// Constructor & Destructor
	Resources();
	~Resources();

	// Member functions
	CIw2DImage*	getMainMenuBG()	{ return mainMenuBG; }
	CIw2DImage*	getEndScreenBG()	{ return endScreenBG; }
	CIw2DImage*	getPauseMenuBG()	{ return pauseMenuBG; }
	CIw2DImage*	getGameBG() { return gameBG; }
	CIw2DImage*	getPlayButton() { return playButton; }
	CIw2DImage*	getExitButton() { return exitButton; }
	CIw2DImage*	getPauseButton() { return pauseButton; }
	CIw2DImage*	getPlayer() { return player; }
	CIw2DImage*	getPlayerLeft() { return playerLeft; }
	CIw2DImage* getPlayerRight() { return playerRight; }
	CIw2DImage* getPlayerUp() { return playerUp; }
	CIw2DImage* getPlayerDown() { return playerDown; }
	CIw2DImage*	getRock() { return rock; }
	CIw2DImage*	getBlank() { return blank; }
	CIw2DImage* getHome() { return home; }
	CIw2DFont* getFont() { return font; }
	CAtlas* getPlayerLeftAtlas() { return playerLeftAtlas; }
	CAtlas* getPlayerRightAtlas() { return playerRightAtlas; }
	CAtlas* getPlayerUpAtlas() { return playerUpAtlas; }
	CAtlas* getPlayerDownAtlas() { return playerDownAtlas; }

protected:
	// Member variables
	CIw2DImage*	mainMenuBG;
	CIw2DImage*	endScreenBG;
	CIw2DImage* pauseMenuBG;
	CIw2DImage*	gameBG;
	CIw2DImage*	playButton;
	CIw2DImage*	exitButton;
	CIw2DImage* pauseButton;
	CIw2DImage*	player;
	CIw2DImage*	playerLeft;
	CIw2DImage* playerRight;
	CIw2DImage* playerUp;
	CIw2DImage* playerDown;
	CIw2DImage*	rock;
	CIw2DImage*	blank;
	CIw2DImage*	home;
	CIw2DFont* font;

	// Atlases
	CAtlas*	playerLeftAtlas;
	CAtlas*	playerRightAtlas;
	CAtlas* playerUpAtlas;
	CAtlas* playerDownAtlas;
};

extern Resources* g_pResources;

#endif  // __RESOURCES_H__

