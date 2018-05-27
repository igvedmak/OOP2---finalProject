#include "Token.h"


// Constructor which use base class constructor and do intRect to the relvant texture
Token::Token(sf::Vector2f place)
	:Treasure(place)
{
	//m_sprite.setTextureRect(sf::IntRect(DEATH_COL * STATIC_SIZE, 0, STATIC_SIZE, STATIC_SIZE));
	m_sprite.setPosition(place.x * STATIC_SIZE, place.y * STATIC_SIZE);
}

// Function which check collision of sfml : intersect of this class object eith obj she get 
bool Token::isCollide(Object & obj)
{
	return m_sprite.getGlobalBounds().intersects(obj.getSprite().getGlobalBounds());
}
