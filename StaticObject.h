#pragma once
#include "Object.h"

class StaticObject : public Object
{
public:
	explicit StaticObject(const sf::Vector2f& position, const sf::Texture &t);
	StaticObject(const StaticObject&) = delete;//copy c-tor (lvalue)
	StaticObject& operator=(const StaticObject&) = delete; //assignment operator (lvalue)
	StaticObject(StaticObject&&) = default;//move copy c-tor (rvalue)
	StaticObject& operator=(StaticObject&&) = delete;//move assigment operator (rvalue)
};

