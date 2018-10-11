#include "Object.h"

//c-tor, set the texture, the position 
Object::Object(const sf::Vector2f& coords, const sf::Texture& t)
	:m_texture(&t)
{
	m_sprite.setTexture(*m_texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.f, m_sprite.getLocalBounds().height / 2.f);
	m_sprite.setPosition(coords);
}
//----------------------------------------------------------------------------------------------
// the function return float number- the left x coordinate of the sprite object
float Object::getLeft() const{
	return m_sprite.getPosition().x - m_sprite.getGlobalBounds().width / 2;
}
//----------------------------------------------------------------------------------------------
// the function return float number- the right x coordinate of the sprite object
float Object::getRight() const{
	return m_sprite.getPosition().x + m_sprite.getGlobalBounds().width / 2;
}

//----------------------------------------------------------------------------------------------
// the function return float number- the left x coordinate of the sprite object
float Object::getLeftE() const{
	return m_sprite.getPosition().x - m_sprite.getGlobalBounds().width;
}
//----------------------------------------------------------------------------------------------
// the function return float number- the right x coordinate of the sprite object
float Object::getRightE() const{
	return m_sprite.getPosition().x + m_sprite.getGlobalBounds().width;
}
//----------------------------------------------------------------------------------------------
// the function return float number- the top y coordinate of the sprite object
float Object::getTop() const{
	return m_sprite.getPosition().y - m_sprite.getGlobalBounds().height / 2;
}
//----------------------------------------------------------------------------------------------
// the function return float number- the bottom y coordinate of the sprite object
float Object::getBottom() const{
	return m_sprite.getPosition().y + m_sprite.getGlobalBounds().height / 2;
}
// the function return float number- the bottom y coordinate of the sprite object
float Object::getBottomE() const {
	return m_sprite.getPosition().y + m_sprite.getGlobalBounds().height / 4;
}

sf::Vector2f Object::getCenter() const{
	return { getBoundingBox().left + getBoundingBox().width / 2, getBoundingBox().top + getBoundingBox().height / 2 };
}

