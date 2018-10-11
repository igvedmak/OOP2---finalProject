#pragma once
#include "StaticObject.h"
class Ladder: public StaticObject
{
public:
	explicit Ladder(const sf::Vector2f& position, const sf::Texture &t);
	Ladder(const Ladder&) = delete;//copy c-tor (lvalue)
	Ladder& operator=(const Ladder&) = delete; //assignment operator (lvalue)
	Ladder(Ladder&&) = default;//move copy c-tor (rvalue)
	Ladder& operator=(Ladder&&) = delete;//move assigment operator (rvalue)

private:
	static bool m_registerit;
	static bool m_registerit1;

};
