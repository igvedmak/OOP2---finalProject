#include "Tile.h"

// Base class Constructor for all tiles which will do intRect from the same sheet
Tile::Tile(sf::Vector2f place)
	:StaticObject(place){
	m_texture = (Source::instance().getTexture("statics"));
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(place.x * STATIC_SIZE, place.y * STATIC_SIZE);
}

// Function which check collision of sfml : intersect of this class object eith obj she get 
bool Tile::isCollide(Object & obj){
	return m_sprite.getGlobalBounds().intersects(obj.getSprite().getGlobalBounds());
}


// set tile texture according to level number
void Tile::setBG(int level){
	m_sprite.setTextureRect(sf::IntRect((level - 1) * STATIC_SIZE, 0 * STATIC_SIZE, STATIC_SIZE, STATIC_SIZE));
}