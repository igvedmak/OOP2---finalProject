#pragma once
#include "Obstacle.h"
class Fire : public Obstacle
{
public:
	explicit Fire(const sf::Vector2f& position, const sf::Texture &t);
	Fire(const Fire&) = delete;//copy c-tor (lvalue)
	Fire& operator=(const Fire&) = delete; //assignment operator (lvalue)
	Fire(Fire&&) = default;//move copy c-tor (rvalue)
	Fire& operator=(Fire&&) = delete;//move assigment operator (rvalue)

private:
	static bool m_registerit;
};

