#pragma once
#include "GameState.h"
class PlayState : public GameState
{
public:
	explicit PlayState(const sf::Vector2f& coords, const sf::Texture& texture);
	PlayState(const PlayState&) = delete;//copy c-tor (lvalue)
	PlayState& operator=(const PlayState&) = delete; //assignment operator (lvalue)
	PlayState(PlayState&&) = default;//move copy c-tor (rvalue)
	PlayState& operator=(PlayState&&) = delete;//move assigment operator (rvalue)

	~PlayState();
	void displayState(GameManager& controller);
	void handleEvent(GameManager& controller);
private:
	static bool m_registerit;
};

