#pragma once
#include "GameState.h"
#include "GameManager.h"
#include "Source.h"
class IntroState :
	public GameState
{
public:
	explicit IntroState(const sf::Vector2f& coords, const sf::Texture& texture);
	IntroState(const IntroState&) = delete;//copy c-tor (lvalue)
	IntroState& operator=(const IntroState&) = delete; //assignment operator (lvalue)
	IntroState(IntroState&&) = default;//move copy c-tor (rvalue)
	IntroState& operator=(IntroState&&) = delete;//move assigment operator (rvalue)

	void displayState(GameManager& controller);
	void handleEvent(GameManager& controller);

private:
	sf::Text m_main, m_title, m_textInst, m_textInst2;
	static bool m_registerit;
};

