#pragma once
#include "Obstacle.h"
class BreakableTile : public Obstacle
{
public:
	explicit BreakableTile(const sf::Vector2f& position, const sf::Texture &t);
	BreakableTile(const BreakableTile&) = delete;//copy c-tor (lvalue)
	BreakableTile& operator=(const BreakableTile&) = delete; //assignment operator (lvalue)
	BreakableTile(BreakableTile&&) = default;//move copy c-tor (rvalue)
	BreakableTile& operator=(BreakableTile&&) = delete;//move assigment operator (rvalue)

private:
	static bool m_registerit;
};

