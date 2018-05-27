#include "Spkies.h"

// Constructor which use base class constructor and do intRect to the relvant texture
Spkies::Spkies(sf::Vector2f place)
	: Obstacle(place)
{
	//m_sprite.setTextureRect(sf::IntRect(BREAKABLE_X * STATIC_SIZE, BREAKABLE_Y * STATIC_SIZE, STATIC_SIZE, STATIC_SIZE));
	//m_sprite.setPosition(place.x * STATIC_SIZE, place.y * STATIC_SIZE);
}

// Function which check collision of sfml : intersect of this class object eith obj she get 
bool Spkies::isCollide(Object & obj){
	return m_sprite.getGlobalBounds().intersects(obj.getSprite().getGlobalBounds());
}
