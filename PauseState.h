#pragma once
#include "GameState.h"
class PauseState : public GameState
{
public:
	explicit PauseState(const sf::Vector2f& coords, const sf::Texture& texture);
	PauseState(const PauseState&) = delete;//copy c-tor (lvalue)
	PauseState& operator=(const PauseState&) = delete;//assigment operator (lvalue)
	PauseState(PauseState&&) = default;////move copy c-tor (rvalue)
	PauseState& operator=(PauseState&&) = delete;//move assigment operator (rvalue)

	void displayState(GameManager& controller);
	void handleEvent(GameManager& controller);
private:
	static bool m_registerit;
	sf::Text m_title;
};

