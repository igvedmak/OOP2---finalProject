#pragma once
#include "Constants.h"

//factory design pattern using ownership semantics
template <typename T1, typename T2>
class SpawnManager
{
public:
	static bool registerit(const T1& type, std::unique_ptr<T2>(*f)(const sf::Vector2f & pos));
	static std::unique_ptr<T2> create(const T1& type, const sf::Vector2f& pos);

private:
	static std::map<T1, std::unique_ptr<T2>(*)(const sf::Vector2f& pos)>& m_map()
	{
		static std::map<T1, std::unique_ptr<T2>(*)(const sf::Vector2f& pos)> mapInstance;
		return mapInstance;
	}
};

template<typename T1, typename T2>
inline bool SpawnManager<T1, T2>::registerit(const T1 & type, std::unique_ptr<T2>(*f)(const sf::Vector2f & pos))
{
	m_map().emplace(type, f);
	return true;
}

template<typename T1, typename T2>
inline std::unique_ptr<T2> SpawnManager<T1, T2>::create(const T1& type, const sf::Vector2f& pos)
{
	auto it = m_map().find(type);
	if (it == m_map().end())
		return nullptr;
	return it->second(pos);
}