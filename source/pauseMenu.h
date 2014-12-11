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

#if !defined(__PAUSEMENU_H__)
#define __PAUSEMENU_H__

#include "scene.h"

class PauseMenu : public Scene
{
protected:
    // UI components
    CSprite*    continueGameButton;
    CSprite*    newGameButton;
public:
    CSprite*    getContinueGameButton()     { return continueGameButton; }
    CSprite*    getNewGameButton()          { return newGameButton; }

public:
    PauseMenu() {}
    ~PauseMenu();

    // initialise the menu
    void            Init();

    // Update the menu
    void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

    // Render the menu
    void            Render();

};

#endif  // __PAUSEMENU_H__


