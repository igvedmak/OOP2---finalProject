#include "StaticObject.h"
class WallTile: public StaticObject
{
public:
	explicit WallTile(const sf::Vector2f& position, const sf::Texture &t);
	WallTile(const WallTile&) = delete;//copy c-tor (lvalue)
	WallTile& operator=(const WallTile&) = delete; //assignment operator (lvalue)
	WallTile(WallTile&&) = default;//move copy c-tor (rvalue)
	WallTile& operator=(WallTile&&) = delete;//move assigment operator (rvalue)
private:
	static bool m_registerit;
	static bool m_registerit1;
	static bool m_registerit2;
	static bool m_registerit3;
	static bool m_registerit4;
	static bool m_registerit5;
};
