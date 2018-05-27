#include "Pickup.h"
// Base class Constructor for all pickups which will do intRect from the same sheet
Pickup::Pickup(sf::Vector2f place)
	:StaticObject(place)
{
	m_texture = (Source::instance().getTexture("pickup"));
	m_sprite.setTexture(m_texture);
}
