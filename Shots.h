#pragma once
#include "DynamicObject.h"
class Shots : public DynamicObject
{
public:
	explicit Shots(const sf::Vector2f& position, const sf::Texture &t);
	Shots(const Shots&) = delete;//copy c-tor (lvalue)
	Shots& operator=(const Shots&) = delete; //assignment operator (lvalue)
	Shots(Shots&&) = default;//move copy c-tor (rvalue)
	Shots& operator=(Shots&&) = delete;//move assigment operator (rvalue)
};

