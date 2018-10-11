#pragma once
#include "StaticObject.h"
#include "Constants.h"
#include "DynamicObject.h"
#include "CollisionManager.h"

class Wall : public StaticObject
{
public:
	explicit Wall(const sf::Vector2f& position, const sf::Texture &t); // c-tor
	Wall(const Wall&) = delete;//copy c-tor (lvalue)
	Wall& operator=(const Wall&) = delete; //assignment operator (lvalue)
	Wall(Wall&&) = default;//move copy c-tor (rvalue)
	Wall& operator=(Wall&&) = delete;//move assigment operator (rvalue)
private:
	static bool m_registerit;
	static bool m_registerit1;
	static bool m_registerit2;
	static bool m_registerit3;
	static bool m_registerit4;
};

