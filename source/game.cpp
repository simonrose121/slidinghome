#include "IwGx.h"
#include "IwHashString.h"

#include "game.h"
#include "main.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "pauseMenu.h"

#define GRID_OFFSET_X		41
#define GRID_OFFSET_Y		37

Game::~Game()
{
	
}

void Game::Init(int grid_width, int grid_height)
{
	graphicsScale = (float)IwGxGetScreenWidth() / GRAPHIC_DESIGN_WIDTH;
}
