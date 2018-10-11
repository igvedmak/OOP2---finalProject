#include "HealthPotion.h"
#include "Pickup.h"

bool HealthPotion::m_registerit = SpawnManager<char, Pickup>::registerit(HEAL_C, [](const sf::Vector2f& pos) -> std::unique_ptr<Pickup> { return std::make_unique<HealthPotion>(pos, Source::instance().getHealTexture()); });

HealthPotion::HealthPotion(const sf::Vector2f& position, const sf::Texture &t) 
	: Potion(position, t){}