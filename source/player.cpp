#include "player.h"

Player::~Player()
{

}

void Player::init(float x, float y, CIw2DImage* image)
{
	m_X = x;
	m_Y = y;
	SetImage(image);
}

