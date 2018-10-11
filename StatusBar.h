#pragma once
#include <array>
#include "Source.h"
#include "Constants.h"

class StatusBar
{
public:
	explicit StatusBar(const sf::Vector2f& coords, const sf::Texture& m_texture);
	StatusBar(const StatusBar&) = delete;//copy c-tor (lvalue)
	StatusBar& operator=(const StatusBar&) = delete;//assigment operator (lvalue)
	StatusBar(StatusBar&&) = default;//move copy c-tor (rvalue)
	StatusBar& operator=(StatusBar&&) = delete;//move assigment operator (rvalue)
	~StatusBar();
	// updating the data of the status bar
	const void UpdateScore(int score);
	const void UpdateLevel();
	const void UpdatePreLife(int life);
	const void UpdateLife(int life);
	void draw(sf::RenderWindow & window) { window.draw(m_sprite); }
	// for the status bar
	const sf::Text& getScoreText() const { return m_score; };
	const sf::Text& getLifeText() const { return m_life; };
	const sf::Text& getLifePreText() const { return m_lifePre; };
	const sf::Text& getLevelText() const { return m_lvlText; };

private:
	sf::Text m_score;                  // score per level text
	sf::Text m_lvlText;// number of level text
	sf::Text m_life;		// number of lifes		
	sf::Text m_lifePre;		// % of lifes
	sf::Sprite m_sprite;
	sf::Texture m_texture;
};
