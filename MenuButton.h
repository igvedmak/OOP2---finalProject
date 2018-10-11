#pragma once
#include "source.h"
#include "Constants.h"


const int NUM_OF_BUTTON = 4;

class MenuButton
{
public:
	explicit MenuButton(const sf::Vector2f& coords, const sf::Texture& texture,const std::string& str)
		:m_texture(texture),m_name(str)
	{
		m_texture.setSmooth(true);
		m_sprite.setTexture(m_texture);
		m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.f, m_sprite.getLocalBounds().height / 2.f);
		m_sprite.setPosition(coords);

		m_text = sf::Text(m_name, Source::instance().getFont(), 30U);
		m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
		m_text.setPosition(coords.x - 150, coords.y - 5);
	}

	MenuButton(const MenuButton&) = delete;//copy c-tor (lvalue)
	MenuButton& operator=(const MenuButton&) = delete;//assigment operator (lvalue)
	MenuButton(MenuButton&&) = default;////move copy c-tor (rvalue)
	MenuButton& operator=(MenuButton&&) = delete;//move assigment operator (rvalue)
	virtual ~MenuButton() = default;
	
	const sf::Text& getText() const { return m_text; }
	const void updateTextColor(sf::Color color) { m_text.setFillColor(color); }
	const void UpdateTexure(sf::IntRect rect) { m_sprite.setTextureRect(rect); }
	virtual void draw(sf::RenderWindow & window) { window.draw(m_sprite); }

protected:
	sf::Text m_text;
	std::string m_name;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

class PlayButton
	: public MenuButton
{
public:
	explicit PlayButton(const sf::Vector2f& coords, const sf::Texture& m_texture, const std::string& str) 
		: MenuButton(coords,m_texture,str)
	{
	}
};

class ScoreButton
	: public MenuButton
{
public:
	explicit ScoreButton(const sf::Vector2f& coords, const sf::Texture& m_texture, const std::string& str) 
		: MenuButton(coords, m_texture,str)
	{
	}
};

class ExitButton
	: public MenuButton
{
public:
	explicit ExitButton(const sf::Vector2f& coords, const sf::Texture& m_texture, const std::string& str) 
		: MenuButton(coords, m_texture,str)
	{
	}
};

class InstructionButton
	: public MenuButton
{
public:
	explicit InstructionButton(const sf::Vector2f& coords, const sf::Texture& m_texture, const std::string& str) 
		: MenuButton(coords, m_texture, str)
	{
	}
};


const sf::Vector2i MUTE = sf::Vector2i{ 50,0 };
const sf::Vector2i UNMUTE = sf::Vector2i{ 0,0 }; 

class MuteButton :
	public MenuButton
{
public:
	explicit MuteButton(const sf::Vector2f& coords, const sf::Texture& m_texture)
		: MenuButton(coords, m_texture, Quotation), m_on(false){
		m_sprite.setTextureRect(sf::IntRect(UNMUTE.x, UNMUTE.y, 50, 50));
	}
	MuteButton(const MuteButton&) = delete;//copy c-tor (lvalue)
	MuteButton& operator=(const MenuButton&) = delete;//assigment operator (lvalue)
	MuteButton(MuteButton&&) = default;////move copy c-tor (rvalue)
	MuteButton& operator=(MuteButton&&) = delete;//move assigment operator (rvalue)

	void updateChoice()
	{
		m_on = (m_on == true ? false : true);
		if (m_on)
			m_sprite.setTextureRect(sf::IntRect(MUTE.x, MUTE.y, 50, 50));
		else
			m_sprite.setTextureRect(sf::IntRect(UNMUTE.x, UNMUTE.y, 50, 50));
	}
	bool getOnOff() const { return m_on; }

private:
	bool m_on;
};

