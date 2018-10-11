#pragma once

namespace sf
{
	class Texture;
	class Font;
	class Music;
}

namespace Textures
{ 
	enum ID
	{
		Background,
		Button,
		Score,
		Instro,
		Pause,
		Mute,
		End,
		lvl1object,
		Bar,
		BGLVL1,
		Player,
		EnemySmart,
		EnemyDumb,
		Tile,
		Tile1,
		Tile2,
		Tile3,
		Wall,
		Fire,
		Spkie,
		Spkie1,
		Spkie2,
		Spkie3,
		Spkie4,
		Spkie5,
		Ladder,
		Ladder2,
		Heal,
		redcrown,
		wall1,
		wall2,
		wall3,
		wall4,
		wall5,
		wall6,
		wall7,
		wall8,
		wall9,
		Empty,
		Lamp,
		SmallTile,
		Coin
	};
}

namespace Fonts
{
	enum ID
	{
		Main
	};
};

namespace Musics
{
	enum ID
	{
		Background,
		SwitchBuffer,
		MusicLvl1,
		swordSwich,
		uppercut,
		foodwait,
		Shot,
		Click,
		Walk,
		Pickup,
		CoinPick,
		HealPick,
		Death,
		EnemyDeath,
		EnemyHit
	};
};

template <typename Asset, typename Identifier>
class AssetManager;

typedef AssetManager<sf::Texture, Textures::ID> TextureManager;
typedef AssetManager<sf::Font, Fonts::ID> FontManager;
typedef AssetManager<sf::Music, Musics::ID> MusicManager;
