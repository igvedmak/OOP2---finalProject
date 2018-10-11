#pragma once
#include "Constants.h"
#include <map>
#include "Source.h"
#include "DynamicObject.h"
#include "Tile.h"
#include "emptyHelper.h"
#include "Object.h"
#include "Spkies.h"
#include "Ladder.h"
#include "Wall.h"
#include "WallTile.h"
#include "Coins.h"
#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

namespace CollisionManager {
	bool PixelPerfectTest(const sf::Sprite& Object1, const sf::Sprite& Object2, sf::Uint8 AlphaLimit = 0);
	bool CreateTextureAndBitmask(sf::Texture &LoadInto, const std::string & Filename);
	bool CircleTest(const sf::Sprite& Object1, const sf::Sprite& Object2);
	bool BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2);

	typedef void(*HitFunctionPtr)(std::shared_ptr<Object>, std::shared_ptr<Object>, PlayState&);
	typedef std::map<std::pair<std::string, std::string>, HitFunctionPtr> HitMap;
	
	template<typename T1, typename T2>
	void SetFunc(HitMap& map, HitFunctionPtr func);

	static HitMap initializeCollisionMap();
	HitFunctionPtr lookup(const std::string& class1, const std::string& class2);
	void processCollision(std::shared_ptr<Object> obj1Ptr, std::shared_ptr<Object> obj2Ptr, PlayState & board);
}

template<typename T1, typename T2>
void CollisionManager::SetFunc(CollisionManager::HitMap& map, CollisionManager::HitFunctionPtr func)
{
	auto t1 = typeid(T1).name();
	auto t2 = typeid(T2).name();
	map[std::make_pair(t1, t2)] = func;
}

#endif	/*COLLISIONMANAGER_H */