/*
* (C) 2001-2012 Marmalade. All Rights Reserved.
*
* This document is protected by copyright, and contains information
* proprietary to Marmalade.
*
* This file consists of source code released by Marmalade under
* the terms of the accompanying End User License Agreement (EULA).
* Please do not use this program/source code before you have read the
* EULA and have agreed to be bound by its terms.
*/

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
	//backgrounds
	CIw2DImage*		MainMenuBG;
	CIw2DImage*		GameBG;
	CIw2DImage*		PlayButton;

	CIw2DImage*		Player;

public:
	//Image pointers
	CIw2DImage*		GetMainMenuBG()		{ return MainMenuBG; }
	CIw2DImage*		GetGameBG()			{ return GameBG;  }
	CIw2DImage*		GetPlayButton()		{ return PlayButton; }

	CIw2DImage*		GetPlayer()			{ return Player; }

public:
	Resources();
	~Resources();
};

extern Resources* g_pResources;

#endif  // __RESOURCES_H__

