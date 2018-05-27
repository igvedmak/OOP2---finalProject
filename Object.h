#pragma once
#include "Constants.h"
#include "Source.h"
// Abstract Class
class Object
{
public:
	Object(sf::Vector2f place) {}
	sf::Sprite getSprite() const { return m_sprite; }
	virtual ~Object() {};

protected:
	// this two members will define at each object
	sf::Sprite m_sprite;
	sf::Texture m_texture;
};

