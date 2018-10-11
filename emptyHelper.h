#pragma once
#include "StaticObject.h"
class emptyHelper
	:public StaticObject
{
public:
	explicit emptyHelper(const sf::Vector2f& position, const sf::Texture &t);
	emptyHelper(const emptyHelper&) = delete;//copy c-tor (lvalue)
	emptyHelper& operator=(const emptyHelper&) = delete; //assignment operator (lvalue)
	emptyHelper(emptyHelper&&) = default;//move copy c-tor (rvalue)
	emptyHelper& operator=(emptyHelper&&) = delete;//move assigment operator (rvalue)

private:
	static bool m_registerit;
};