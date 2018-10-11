#include "Wall.h"

bool Wall::m_registerit = SpawnManager<char, StaticObject>::registerit(WALL_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<Wall>(pos, Source::instance().getWallTexture()); });
bool Wall::m_registerit1 = SpawnManager<char, StaticObject>::registerit(WALL5_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<Wall>(pos, Source::instance().getWall5Texture()); });
bool Wall::m_registerit2 = SpawnManager<char, StaticObject>::registerit(WALL6_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<Wall>(pos, Source::instance().getWall6Texture()); });
bool Wall::m_registerit3 = SpawnManager<char, StaticObject>::registerit(LAMP_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<Wall>(pos, Source::instance().getLapTexture()); });
bool Wall::m_registerit4 = SpawnManager<char, StaticObject>::registerit(WALL9_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<Wall>(pos, Source::instance().getWall9Texture()); });

Wall::Wall(const sf::Vector2f& position, const sf::Texture &t) : 
	StaticObject(position, t) {}

