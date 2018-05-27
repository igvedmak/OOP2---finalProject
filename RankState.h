#pragma once
#include "GameState.h"
class RankState : public GameState
{
public:
	explicit RankState(const sf::Vector2f& coords, const sf::Texture& texture);
	RankState(const RankState&) = delete;//copy c-tor (lvalue)
	RankState& operator=(const RankState&) = delete; //assignment operator (lvalue)
	RankState(RankState&&) = default;//move copy c-tor (rvalue)
	RankState& operator=(RankState&&) = delete;//move assigment operator (rvalue)

	void displayState(GameManager& controller);
	void handleEvent(GameManager& controller);

private:
	static bool m_registerit;
};

