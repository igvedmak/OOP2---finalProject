#pragma once
#include "StaticObject.h"
#include "Constants.h"
#include "DynamicObject.h"

class Tile : public StaticObject
{
public:
	explicit Tile(const sf::Vector2f& position, const sf::Texture &t);
	Tile(const Tile&) = delete;//copy c-tor (lvalue)
	Tile& operator=(const Tile&) = delete; //assignment operator (lvalue)
	Tile(Tile&&) = default;//move copy c-tor (rvalue)
	Tile& operator=(Tile&&) = delete;//move assigment operator (rvalue)
private:
	static bool m_registerit;
	static bool m_registerit1;
	static bool m_registerit2;
	static bool m_registerit3;
	static bool m_registerit4;
};