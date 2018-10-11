#pragma once
#include "Shots.h"
class SpecialSword : public Shots
{
public:
	explicit SpecialSword(const sf::Vector2f& position, const sf::Texture &t);
	SpecialSword(const SpecialSword&) = delete;//copy c-tor (lvalue)
	SpecialSword& operator=(const SpecialSword&) = delete; //assignment operator (lvalue)
	SpecialSword(SpecialSword&&) = default;//move copy c-tor (rvalue)
	SpecialSword& operator=(SpecialSword&&) = delete;//move assigment operator (rvalue)
private:
	SPECIALSWORD typesword;
};

