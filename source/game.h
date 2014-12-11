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

#if !defined(__GAME_H__)
#define __GAME_H__

#include "scene.h"

class Game : public Scene
{
protected:
    int                 currentRoundScore;              // Current round score

    // UI components
    CLabel*             scoreLabel;
    CSprite*            pauseSprite;
    CSprite*            gemSprite;

private:
    void            initUI();
public:
    Game() {}
    ~Game();

    // initialise the game
    void            Init();

    // Update the game
    void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

    // Render the game
    void            Render();

    void            switchToScene(const char* scene_name);
    void            addToRoundScore(int score);
    void            pauseGame();
    void            resumeGame();
    void            newGame();

};


#endif  // __GAME_H__


