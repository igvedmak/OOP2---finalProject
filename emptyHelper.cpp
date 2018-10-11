#include "emptyHelper.h"

bool emptyHelper::m_registerit = SpawnManager<char, StaticObject>::registerit(EMPRYHELP_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<emptyHelper>(pos, Source::instance().getEmptyTexture()); });


emptyHelper::emptyHelper(const sf::Vector2f& position, const sf::Texture &t) 
	: StaticObject(position, t){}
