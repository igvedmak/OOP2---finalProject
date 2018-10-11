#include "StatusBar.h"

//c-tor
StatusBar::StatusBar(const sf::Vector2f& coords, const sf::Texture& texture)
	:m_texture(texture)
{
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(coords);
	// texture for lvl
	m_lvlText = sf::Text(levelStatus, Source::instance().getFont(), 35U);
	m_lvlText.setOutlineColor(sf::Color::Black);
	m_lvlText.setOutlineThickness(3);
	m_lvlText.setPosition(STATE_WIDTH/11, STATE_HEIGTH - 100);
	// texture for score
	m_score = sf::Text(scoreStatus, Source::instance().getFont(), 35U);
	m_score.setOutlineColor(sf::Color::Black);
	m_score.setOutlineThickness(3);
	m_score.setPosition(m_lvlText.getPosition().x + 400, m_lvlText.getPosition().y);
	// texture for life %
	m_lifePre = sf::Text(lifePreStatus, Source::instance().getFont(), 35U);
	m_lifePre.setOutlineColor(sf::Color::Black);
	m_lifePre.setOutlineThickness(3);
	m_lifePre.setPosition(m_score.getPosition().x + 450, m_score.getPosition().y);
	// texture for life
	m_life = sf::Text(lifeStatus, Source::instance().getFont(), 35U);
	m_life.setOutlineColor(sf::Color::Black);
	m_life.setOutlineThickness(3);
	m_life.setPosition(m_lifePre.getPosition().x + 450, m_score.getPosition().y);
}

//d-tor
StatusBar::~StatusBar(){}
//----------------------------------------------------------------------------------------------
//updates current player's score
const void StatusBar::UpdateScore(int score)
{
	std::string to_print(scoreStatus2 + std::to_string(score));
	m_score.setString(to_print);
}
//----------------------------------------------------------------------------------------------
//updates current player's life
const void StatusBar::UpdateLife(int life)
{
	std::string to_print = lifeStatus2 + std::to_string(life);
	m_life.setString(to_print);
}
//----------------------------------------------------------------------------------------------
//updates current level
const void StatusBar::UpdateLevel()
{
	std::string to_print = levelStatus2 + std::to_string(Source::instance().getCurrLvl() + 1);
	m_lvlText.setString(to_print);
}

//updates % life
const void StatusBar::UpdatePreLife(int life)
{
	std::string to_print = lifePreStatus2 + std::to_string(life);
	m_lifePre.setString(to_print);
}
