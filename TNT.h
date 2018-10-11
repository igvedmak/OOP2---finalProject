#pragma once
#include "Shots.h"
class TNT : public Shots
{
public:
	explicit TNT(const sf::Vector2f& position, const sf::Texture &t);
	TNT(const TNT&) = delete;//copy c-tor (lvalue)
	TNT& operator=(const TNT&) = delete; //assignment operator (lvalue)
	TNT(TNT&&) = default;//move copy c-tor (rvalue)
	TNT& operator=(TNT&&) = delete;//move assigment operator (rvalue)
};

