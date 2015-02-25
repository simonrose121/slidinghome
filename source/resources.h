
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
	CIw2DImage* getMainMenuBGHC(){ return mainMenuBGHC; }
	CIw2DImage*	getEndScreenBG()	{ return endScreenBG; }
	CIw2DImage*	getPauseMenuBG()	{ return pauseMenuBG; }
	CIw2DImage*	getGameBG() { return gameBG; }
	CIw2DImage* getGameBGHC() { return gameBGHC; }
	CIw2DImage*	getPlayButton() { return playButton; }
	CIw2DImage* getPlayButtonHC(){ return playButtonHC; }
	CIw2DImage*	getExitButton() { return exitButton; }
	CIw2DImage*	getPauseButton() { return pauseButton; }
	CIw2DImage* getSettingsButton() { return settingsButton; }
	CIw2DImage* getSettingsButtonHC() { return settingsButtonHC; }
	CIw2DImage* getStar() { return star; }
	CIw2DImage* getHoloStar() { return holoStar; }
	CIw2DImage*	getPlayer() { return player; }
	CIw2DImage*	getPlayerLeft() { return playerLeft; }
	CIw2DImage* getPlayerRight() { return playerRight; }
	CIw2DImage* getPlayerUp() { return playerUp; }
	CIw2DImage* getPlayerDown() { return playerDown; }
	CIw2DImage*	getRock() { return rock; }
	CIw2DImage*	getLevelButton() { return levelButton; }
	CIw2DImage*	getBlank() { return blank; }
	CIw2DImage* getHome() { return home; }
	CIw2DImage* getUpButton() { return upButton; }
	CIw2DImage* getRightButton() { return rightButton; }
	CIw2DImage* getDownButton() { return downButton; }
	CIw2DImage* getLeftButton() { return leftButton; }
	CIw2DImage* getOnScreenSettingButton() { return onScreenSettingButton; }
	CIw2DImage* getOnScreenSettingButtonSelected() { return onScreenSettingButtonSelected; }
	CIw2DImage* getHighContrastSettingButton() { return highContrastButton; }
	CIw2DImage* getHighContrastSettingButtonSelected() { return highContrastButtonSelected; }
	CIw2DImage* getBackButton() { return backButton; }

	CIw2DFont*  getFont() { return font; }

	CAtlas* getPlayerLeftAtlas() { return playerLeftAtlas; }
	CAtlas* getPlayerRightAtlas() { return playerRightAtlas; }
	CAtlas* getPlayerUpAtlas() { return playerUpAtlas; }
	CAtlas* getPlayerDownAtlas() { return playerDownAtlas; }

protected:
	// Member variables
	CIw2DImage*	mainMenuBG;
	CIw2DImage* mainMenuBGHC;
	CIw2DImage*	endScreenBG;
	CIw2DImage* pauseMenuBG;
	CIw2DImage*	gameBG;
	CIw2DImage* gameBGHC;
	CIw2DImage*	playButton;
	CIw2DImage* playButtonHC;
	CIw2DImage*	exitButton;
	CIw2DImage* pauseButton;
	CIw2DImage* settingsButton;
	CIw2DImage* settingsButtonHC;
	CIw2DImage* star;
	CIw2DImage* holoStar;
	CIw2DImage*	player;
	CIw2DImage*	playerLeft;
	CIw2DImage* playerRight;
	CIw2DImage* playerUp;
	CIw2DImage* playerDown;
	CIw2DImage*	rock;
	CIw2DImage* levelButton;
	CIw2DImage*	blank;
	CIw2DImage*	home;
	CIw2DImage* upButton;
	CIw2DImage* rightButton;
	CIw2DImage* downButton;
	CIw2DImage* leftButton;
	CIw2DImage* onScreenSettingButton;
	CIw2DImage* onScreenSettingButtonSelected;
	CIw2DImage* highContrastButton;
	CIw2DImage* highContrastButtonSelected;
	CIw2DImage* backButton;

	// Fonts
	CIw2DFont* font;

	// Atlases
	CAtlas*	playerLeftAtlas;
	CAtlas*	playerRightAtlas;
	CAtlas* playerUpAtlas;
	CAtlas* playerDownAtlas;
};

extern Resources* g_pResources;

#endif  // __RESOURCES_H__

