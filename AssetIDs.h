#pragma once

namespace sf
{
	class Texture;
	class Font;
}

namespace Textures
{ 
	enum ID
	{
		SFMLLogo,
		Blocks,
		Background
	};
}

namespace Fonts
{
	enum ID
	{
		Main
	};
};

template <typename Asset, typename Identifier>
class AssetManager;

typedef AssetManager<sf::Texture, Textures::ID> Texture;
typedef AssetManager<sf::Font, Fonts::ID> FontManager;
