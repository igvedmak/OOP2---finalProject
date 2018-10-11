#pragma once
#include "Constants.h"
#include "AssetManager.h"
#include "AssetIDs.h"

class Source
{
public:
	static Source& instance();//creates only one instance
	const sf::Font& getFont() const { return m_fonts.get(Fonts::ID::Main); }
	virtual ~Source();
	sf::Texture getTexture(std::string str) const;
	const sf::Texture & getTileTexture() const { return m_textures.get(Textures::ID::Tile); }
	const sf::Texture & getTile1Texture() const { return m_textures.get(Textures::ID::Tile1); }
	const sf::Texture & getTile2Texture() const { return m_textures.get(Textures::ID::Tile2); }
	const sf::Texture & getTile3Texture() const { return m_textures.get(Textures::ID::Tile3); }
	const sf::Texture & getSmallTileTexture() const { return m_textures.get(Textures::ID::SmallTile); }
	const sf::Texture & getlvl1Texture() const { return  m_textures.get(Textures::ID::lvl1object);}
	const sf::Texture & getSplashTexture() const { return m_textures.get(Textures::ID::Background); }
	const sf::Texture & getScoreTexture() const { return m_textures.get(Textures::ID::Score); }
	const sf::Texture & getEndTexture() const { return m_endTexture; }
	const sf::Texture & getEnemySmartTexture() const { return m_textures.get(Textures::ID::EnemySmart); }
	const sf::Texture & getEnemyDumbTexture() const { return m_textures.get(Textures::ID::EnemyDumb); }
	const sf::Texture & getButtonTexture() const { return m_textures.get(Textures::ID::Button); }
	const sf::Texture & getIntroTexture() const { return m_textures.get(Textures::ID::Instro); }
	const sf::Texture & getHealTexture() const { return m_textures.get(Textures::ID::Heal); }
	const sf::Texture & getCoinTexture() const { return m_textures.get(Textures::ID::Coin); }
	const sf::Texture & getRedCrownTexture() const { return m_textures.get(Textures::ID::redcrown); }
	const sf::Texture & getLvlTexture() const { return m_levelBack[m_currentLevel]; }
	const sf::Texture & getPauseTexture() const { return m_pauseTexture; }
	const sf::Texture & getMuteTexture() const { return m_textures.get(Textures::ID::Mute); }
	const sf::Texture & getPlayerTexture() const { return  m_textures.get(Textures::ID::Player); }
	const sf::Texture & getWallTexture() const { return  m_textures.get(Textures::ID::Wall); }
	const sf::Texture & getFireTexture() const { return m_textures.get(Textures::ID::Fire); }
	const sf::Texture & getSpkiesTexture() const { return m_textures.get(Textures::ID::Spkie); }
	const sf::Texture & getSpkies1Texture() const { return m_textures.get(Textures::ID::Spkie1); }
	const sf::Texture & getSpkies2Texture() const { return m_textures.get(Textures::ID::Spkie2); }
	const sf::Texture & getSpkies3Texture() const { return m_textures.get(Textures::ID::Spkie3); }
	const sf::Texture & getSpkies4Texture() const { return m_textures.get(Textures::ID::Spkie4); }
	const sf::Texture & getSpkies5Texture() const { return m_textures.get(Textures::ID::Spkie5); }
	const sf::Texture & getLadderTexture() const { return m_textures.get(Textures::ID::Ladder); }
	const sf::Texture & getLadder2Texture() const { return m_textures.get(Textures::ID::Ladder2); }
	const sf::Texture & getWall1Texture() const { return m_textures.get(Textures::ID::wall1); }
	const sf::Texture & getWall2Texture() const { return m_textures.get(Textures::ID::wall2); }
	const sf::Texture & getWall3Texture() const { return m_textures.get(Textures::ID::wall3); }
	const sf::Texture & getWall4Texture() const { return m_textures.get(Textures::ID::wall4); }
	const sf::Texture & getWall5Texture() const { return m_textures.get(Textures::ID::wall5); }
	const sf::Texture & getWall6Texture() const { return m_textures.get(Textures::ID::wall6); }
	const sf::Texture & getWall7Texture() const { return m_textures.get(Textures::ID::wall7); }
	const sf::Texture & getWall8Texture() const { return m_textures.get(Textures::ID::wall8); }
	const sf::Texture & getWall9Texture() const { return m_textures.get(Textures::ID::wall9); }
	const sf::Texture & getEmptyTexture() const { return m_textures.get(Textures::ID::Empty); }
	const sf::Texture & getLapTexture() const { return m_textures.get(Textures::ID::Lamp); }
	
	const std::multimap<unsigned, std::string, std::greater<unsigned>>& getPlayerScores() const { return m_playerScores; }
	sf::Music & getMenuMusic() { return m_musics.get(Musics::ID::Background); }
	sf::Music & getMenuSwitch() { return m_musics.get(Musics::ID::SwitchBuffer); }
	sf::Music & getStageMusicLvl1() { return m_musics.get(Musics::ID::MusicLvl1);}
	sf::Music & getswishSound() { return m_musics.get(Musics::ID::swordSwich); }
	sf::Music & getuppercutSound() { return m_musics.get(Musics::ID::uppercut); }
	sf::Music & getShotSound() { return m_musics.get(Musics::ID::Shot); }
	sf::Music & getfoodwaitSound() { return m_musics.get(Musics::ID::foodwait); }
	sf::Music & getClickSound() { return m_musics.get(Musics::ID::Click); }
	sf::Music & getWalkSound() { return m_musics.get(Musics::ID::Walk); }
	sf::Music & getPickUpSound() { return m_musics.get(Musics::ID::Pickup); }
	sf::Music & getCoinPickSound() { return m_musics.get(Musics::ID::CoinPick); }
	sf::Music & getHealPickSound() { return m_musics.get(Musics::ID::HealPick); }
	sf::Music & getDeathSound() { return m_musics.get(Musics::ID::Death); }
	sf::Music & getEnemyDeathSound() { return m_musics.get(Musics::ID::EnemyDeath); }
	sf::Music & getEnemyHitSound() { return m_musics.get(Musics::ID::EnemyHit); }

	const std::vector<std::string>& getLvlMat() const { return m_levels[m_currentLevel]; }
	void initCurrentLevel() { m_currentLevel = 0; }
	const bool endOfLevels() const { return m_currentLevel >= MAX_LEVELS; }
	void loadScoreTable(std::fstream &scoresFile);
	const int getCurrLvl() const { return m_currentLevel; }
	const sf::Texture & getBarTexture() const { return m_textures.get(Textures::ID::Bar);}

private:
	TextureManager m_textures; // vector of textures
	FontManager m_fonts; // vector of fonts
	MusicManager m_musics; // vector of musics

	explicit Source();
	Source(const Source&) = delete;//copy c-tor (lvalue)
	Source& operator=(const Source&) = delete; //assignment operator (lvalue)
	Source(Source&&) = delete;//move copy c-tor (rvalue)
	Source& operator=(Source&&) = delete;//move assigment operator (rvalue)

	std::vector<sf::Texture> m_levelBack; // vector of texture levels
	std::vector<std::vector<std::string>> m_levels; // map for all levels
	sf::Texture m_endTexture; // texture for end button
	sf::Texture m_pauseTexture;// texture for pause button
	sf::Texture m_lvl1BG; // texture for level 1 background
	std::map <std::string, sf::Texture> m_textureMap;   // for search string texture as key
	sf::Music m_gamesound; // music game
	std::multimap<unsigned, std::string, std::greater<unsigned>> m_playerScores; // players scores

	unsigned m_currentLevel; //current level
};

