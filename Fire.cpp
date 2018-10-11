#include "Fire.h"

bool Fire::m_registerit = SpawnManager<char, StaticObject>::registerit(FIRE_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<Fire>(pos, Source::instance().getFireTexture()); });

Fire::Fire(const sf::Vector2f& position, const sf::Texture &t)
	: Obstacle(position, t) {}