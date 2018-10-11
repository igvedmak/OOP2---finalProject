#pragma once
#include "Shots.h"
class Bullets : public Shots
{
	explicit Bullets(const sf::Vector2f& position, const sf::Texture &t);
	Bullets(const Bullets&) = delete;//copy c-tor (lvalue)
	Bullets& operator=(const Bullets&) = delete; //assignment operator (lvalue)
	Bullets(Bullets&&) = default;//move copy c-tor (rvalue)
	Bullets& operator=(Bullets&&) = delete;//move assigment operator (rvalue)
};

