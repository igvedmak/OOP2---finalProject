#include "Obstacle.h"

// Base class Constructor for all obstacles which will do intRect from the same sheet
Obstacle::Obstacle(sf::Vector2f place)
	:StaticObject(place)
{
	m_texture = (Source::instance().getTexture("obstacle"));
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(place.x * STATIC_SIZE, place.y * STATIC_SIZE);
}