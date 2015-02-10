
#if !defined(__RESOURCES_H__)
#define __RESOURCES_H__

#define MAX_GEM_TYPES   5

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
	CIw2DImage*	getGameBG() { return gameBG; }
	CIw2DImage*	getPlayButton() { return playButton; }
	CIw2DImage*	getExitButton() { return exitButton; }
	CIw2DImage*	getPlayer() { return player; }
	CIw2DImage*	getRock() { return rock; }
	CIw2DImage*	getBlank() { return blank; }
	CIw2DImage* getHome() { return home; }
	CIw2DFont*  getFont() { return font; }

protected:
	// Member variables
	CIw2DImage*	mainMenuBG;
	CIw2DImage*	endScreenBG;
	CIw2DImage*	gameBG;
	CIw2DImage*	playButton;
	CIw2DImage*	exitButton;
	CIw2DImage*	player;
	CIw2DImage*	rock;
	CIw2DImage*	blank;
	CIw2DImage*	home;
	CIw2DFont*  font;

};

extern Resources* g_pResources;

#endif  // __RESOURCES_H__

