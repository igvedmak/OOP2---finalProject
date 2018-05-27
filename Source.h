#pragma once
#include "Constants.h"

class Source
{
public:
	static Source& instance();//creates only one instance
	const sf::Font& getFont() const { return m_font; }
	virtual ~Source();
	sf::Texture getTexture(std::string str) const;
	const sf::Texture & getSplashTexture() const { return m_textureMenu; }
	const sf::Texture & getScoreTexture() const { return m_scoreTexture; }
	const sf::Texture & getEndTexture() const { return m_endTexture; }
	const sf::Texture & getButtonTexture() const { return m_textButton; }
	const sf::Texture & getLvlTexture() const { return m_levelBack[m_currentLevel]; }
	const sf::Texture & getPauseTexture() const { return m_pauseTexture; }
	const sf::Texture & getMuteTexture() const { return m_muteButtom; }
	sf::Music & getMenuMusic() { return m_menusound; };
	sf::Music & getMenuSwitch() { return m_menuswitch; };
	sf::Music & getStageMusic() { return m_gamesound; };
private:
	explicit Source();
	Source(const Source&) = delete;//copy c-tor (lvalue)
	Source& operator=(const Source&) = delete; //assignment operator (lvalue)
	Source(Source&&) = delete;//move copy c-tor (rvalue)
	Source& operator=(Source&&) = delete;//move assigment operator (rvalue)
	unsigned m_currentLevel;                     //current level number
	std::vector<sf::Texture> m_levelBack; // vector of levels
	sf::Texture m_endTexture; // texture for end button
	sf::Texture m_textureMenu;// texture for menu button
	sf::Texture m_scoreTexture;// texture for score button
	sf::Texture m_pauseTexture;// texture for pause button
	sf::Texture m_textButton;// texture for the button
	sf::Texture m_muteButtom; //texture for mute button
	sf::Font m_font;                             // fonts for show texts
	std::map < std::string, sf::Texture > m_textureMap;     // for search string texture as key
	sf::Music m_menusound; // backsound of the menu
	sf::Music m_menuswitch; // sound of switch buttons
	sf::Music m_gamesound; // music game
};

