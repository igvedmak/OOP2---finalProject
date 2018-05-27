#pragma once
#include "GameState.h"
class EndState : 
	public GameState
{
public:
	explicit EndState(const sf::Vector2f& coords, const sf::Texture& texture);
	EndState(const EndState&) = delete;//copy c-tor (lvalue)
	EndState& operator=(const EndState&) = delete; //assignment operator (lvalue)
	EndState(EndState&&) = default;//move copy c-tor (rvalue)
	EndState& operator=(EndState&&) = delete;//move assigment operator (rvalue)

	void displayState(GameManager& controller);
	void handleEvent(GameManager& controller);
private:
	static bool m_registerit;
};

