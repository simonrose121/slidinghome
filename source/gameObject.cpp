#include "gameObject.h"
#include "game.h"
#include "resources.h"
#include "main.h"

GameObject::~GameObject()
{

}


void GameObject::init(float x, float y, CIw2DImage* image)
{
	m_X = x;
	m_Y = y;
	SetImage(image);
}

