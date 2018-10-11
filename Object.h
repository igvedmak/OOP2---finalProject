#pragma once
#include "SpawnManager.h"
#include "Source.h"

class PlayState;

class Object
{
public:
	explicit Object(const sf::Vector2f& coords, const sf::Texture& m_texture);
	Object(const Object&) = delete;//copy c-tor (lvalue)
	Object& operator=(const Object&) = delete; //assignment operator (lvalue)
	Object(Object&&) = default;//move copy c-tor (rvalue)
	Object& operator=(Object&&) = delete;//move assigment operator (rvalue)

	virtual void draw(sf::RenderWindow & window) { window.draw(m_sprite); }
	// for collide & entity
	float getLeft() const;
	float getRight() const;
	float getLeftE() const;
	float getRightE() const;
	float getTop() const;
	float getBottom() const;
	float getBottomE() const;
	// for collide
	sf::Vector2f getCenter() const;
	sf::Sprite getSprite() const { return m_sprite; }
	const sf::Vector2f& getPos() const { return m_sprite.getPosition(); }
	sf::FloatRect getBoundingBox() const { return m_sprite.getGlobalBounds(); }
	void setPos(sf::Vector2f newPos) { m_sprite.setPosition(newPos); }
	void setTransperent() { m_sprite.setColor(sf::Color::Transparent); }
	virtual ~Object() = default; //for Polymorphism
protected:
	const sf::Texture * m_texture;
	TextureManager m_text;
	sf::Sprite m_sprite;
};