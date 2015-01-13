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

Game::Game()
{
	player = new Player();
}

Game::~Game()
{
	delete player;
}

void Game::Init(int grid_width, int grid_height)
{
	Scene::Init();

	graphicsScale = (float)IwGxGetScreenWidth() / GRAPHIC_DESIGN_WIDTH;

	CSprite* background = new CSprite();
	background->m_X = (float)IwGxGetScreenWidth() / 2;
	background->m_Y = (float)IwGxGetScreenHeight() / 2;
	background->SetImage(g_pResources->GetGameBG());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;
	background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
	background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
	AddChild(background);
}

void Game::Update(float deltaTime, float alphaMul) 
{
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);
}

void Game::Render()
{
	Scene::Render();
}

void Game::newGame()
{
	//create player
	player->init((float)IwGxGetScreenWidth() / 2,(float)IwGxGetScreenHeight() / 2, g_pResources->GetPlayer());
}