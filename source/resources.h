
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
protected:
	CIw2DImage*		MainMenuBG;
	CIw2DImage*		GameBG;
	CIw2DImage*		PlayButton;

	CIw2DImage*		Player;
	CIw2DImage*		Rock;
	CIw2DFont*      Font;

public:
	CIw2DImage*		GetMainMenuBG()		{ return MainMenuBG; }
	CIw2DImage*		GetGameBG()			{ return GameBG; }

	CIw2DImage*		GetPlayer()			{ return Player; }
	CIw2DImage*		GetRock()			{ return Rock; }
	CIw2DImage*		GetPlayButton()		{ return PlayButton; }
	CIw2DFont*      getFont()           { return Font; }

public:
	Resources();
	~Resources();
};

extern Resources* g_pResources;

#endif  // __RESOURCES_H__

