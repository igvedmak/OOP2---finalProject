#include "DynamicObject.h"
// Base class Constructor for all menu buttons which will do intRect from the same sheet
DynamicObject::DynamicObject(sf::Vector2f place)
	:Object(place){
	m_texture = (Source::instance().getTexture("objects"));
	m_sprite.setTexture(m_texture);
}
