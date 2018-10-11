#pragma once
#include "StaticObject.h"
#include "Constants.h"

class Obstacle :
	public StaticObject
{
public:
	explicit Obstacle(const sf::Vector2f& position, const sf::Texture &t);
	Obstacle(const Obstacle&) = delete;//copy c-tor (lvalue)
	Obstacle& operator=(const Obstacle&) = delete; //assignment operator (lvalue)
	Obstacle(Obstacle&&) = default;//move copy c-tor (rvalue)
	Obstacle& operator=(Obstacle&&) = delete;//move assigment operator (rvalue)
};