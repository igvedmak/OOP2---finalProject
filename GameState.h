#pragma once
#include "Constants.h"
#include "GameManager.h"
#include "Source.h"
class GameManager;
class GameState
{
public:
	explicit GameState(const sf::Vector2f& coords, const sf::Texture& texture)
		:m_texture(texture)
	{
		m_texture.setSmooth(true);
		m_sprite.setTexture(m_texture);
		m_sprite.setPosition(coords);
	}
	GameState(const GameState&) = delete;//copy c-tor (lvalue)
	GameState& operator=(const GameState&) = delete;//assigment operator (lvalue)
	GameState(GameState&&) = default;//move copy c-tor (rvalue)
	GameState& operator=(GameState&&) = delete;//move assigment operator (rvalue)
	virtual ~GameState() = default;

	virtual void displayState(GameManager& controller) = 0;
	virtual void updateStage(GameManager& controller) {}
	virtual void handleEvent(GameManager& controller) = 0;
	void draw(sf::RenderWindow& window) const { window.draw(m_sprite); }
protected:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

