#include "player.h"

Player::~Player()
{

}

void Player::moveLeft(int distance)
{
	//Game* game = (Game*)g_pSceneManager->Find("game");

	float new_X = m_Y - (distance * 64);

	/*game->GetTweener().Tween(0.5f,
		FLOAT, new_X, m_Y,
		FLOAT, m_X, m_Y,
		EASING, Ease::sineInOut,
		END);*/
}
